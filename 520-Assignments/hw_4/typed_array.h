#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;
    ElementType pop();
    ElementType pop_front();

    // Setters
    void set(int index, ElementType value);
    void push(const ElementType value);
    void push_front(const ElementType value);

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray<ElementType>& other) {
    TypedArray<ElementType> newArray;
    newArray.capacity = this->capacity + other.capacity;
    newArray.buffer = new ElementType[newArray.capacity];
    newArray.origin = this->origin;
    newArray.end = this->end;
    for (int idx = 0; idx < this->size(); idx++) {
        newArray.buffer[newArray.index_to_offset(idx)] = this->buffer[index_to_offset(idx)];
    }
    for (int idx = 0; idx < other.size(); idx++, ++newArray.end) {
        newArray.buffer[newArray.index_to_offset(idx + this->size())] = other.buffer[index_to_offset(idx)];
    }
    return newArray;
}

template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::reverse() {
    int beginning = this->origin;
    int ending = this->end;
    while(beginning < ending) {
        ElementType temp = this->buffer[this->index_to_offset(beginning)];
        this->buffer[this->index_to_offset(beginning)] = this->buffer[this->index_to_offset(ending)];
        this->buffer[this->index_to_offset(ending)] = temp;
        beginning++;
        ending--;
    }
    return *this;
}

template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType>& other) const {
    return this->concat(other);
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

template <typename ElementType>
ElementType TypedArray<ElementType>::pop() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    ElementType value = buffer[size() - 1];
    end--;
    return value;
}

template <typename ElementType>
ElementType TypedArray<ElementType>::pop_front() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    ElementType value = buffer[origin];
    origin++;
    return value;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

template <typename ElementType>
void TypedArray<ElementType>::push(const ElementType value) {
    while ( out_of_buffer(size() + 1 ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(size())] = value;
    end++;
}

template <typename ElementType>
void TypedArray<ElementType>::push_front(const ElementType value) {
    while ( out_of_buffer(size() + 1 ) ) {
        extend_buffer();
    }
    for (int idx = size(); idx > 0; idx--) {
        buffer[index_to_offset(idx + 1)] = buffer[index_to_offset(idx)]; 
    }
    buffer[origin] = value;
    end++;
}

// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}




#endif
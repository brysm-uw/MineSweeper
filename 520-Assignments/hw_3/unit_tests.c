#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

extern int num_arrays;
extern DynamicArray** arraysAllocated;
#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

    TEST(DynamicArray, Range) {
        DynamicArray * da = DynamicArray_new();
        da = DynamicArray_range(0,1,0.1);
        double tolerance = 1e-9; // Define a small tolerance for floating-point comparisons
        for (int idx = 0; idx < DynamicArray_size(da); idx++) {
            ASSERT_NEAR(DynamicArray_get(da, idx), idx * 0.1, tolerance);
        }
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, Concat) {
        DynamicArray* a = DynamicArray_range(0, 1, 0.1);
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray* c = DynamicArray_concat(a, b);
        
        for (int idx = 0; idx < DynamicArray_size(a); idx++) {
            printf("%f\n", DynamicArray_get(c, idx));
            ASSERT_EQ(DynamicArray_get(c, idx), DynamicArray_get(a, idx));
        }
    
        for (int idx = DynamicArray_size(a), i = 0; idx < DynamicArray_size(a) + DynamicArray_size(b); idx++) {
            ASSERT_EQ(DynamicArray_get(c, idx), DynamicArray_get(b, i));
            i++;
        }
    
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
    }

    TEST(DynamicArray, Max) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_max(b), 1.9, tolerance);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, Min) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_min(b), 1.1, tolerance);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, Mean) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_mean(b), 1.5, tolerance);
        DynamicArray_destroy(b);
    }
    
    TEST(DynamicArray, Median) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_mean(b), 1.5, tolerance);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, sum) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_sum(b), 13.5, tolerance);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, last) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_last(b), 1.9, tolerance);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, first) {
        DynamicArray* b = DynamicArray_range(1.1, 2, 0.1);
        double tolerance = 1e-9;
        ASSERT_NEAR(DynamicArray_first(b), 1.1, tolerance);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, Copy) {
        DynamicArray* a = DynamicArray_range(0, 1, 0.1);
        DynamicArray* b = DynamicArray_new();
        b = DynamicArray_copy(a);
        double tolerance = 1e-9;
        for (int idx = 0; idx < DynamicArray_size(a); idx++) {
            ASSERT_NEAR(DynamicArray_get(a, idx), DynamicArray_get(b, idx), tolerance);
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, Take) {

        DynamicArray* a = DynamicArray_range(0, 1, 0.1);
        DynamicArray* b = DynamicArray_new();
        b = DynamicArray_take(a, 3);
        double tolerance = 1e-9;
        for (int idx = 0; idx < 3; idx++) {
            ASSERT_NEAR(DynamicArray_get(a, idx), DynamicArray_get(b, idx), tolerance);
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, TakeTwo) {
        DynamicArray* a = DynamicArray_range(0, 1, 0.1);
        DynamicArray* b = DynamicArray_take(a, -3);
        double tolerance = 1e-9;
        
        // Validate that b has the correct last 3 elements of a
        for (int idx = DynamicArray_size(a) - 3, i = 0; idx < DynamicArray_size(a); idx++, i++) {
            ASSERT_NEAR(DynamicArray_get(a, idx), DynamicArray_get(b, i), tolerance);
        }
        
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }
    
    TEST(DynamicArray, numArrays) {
        DynamicArray_destroy_all();

        DynamicArray* a = DynamicArray_new();
        DynamicArray* b = DynamicArray_new();
        
        ASSERT_EQ(num_arrays, 2);

        
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, isValid) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b);
        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 3);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(a), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        free(a);
        free(b);
        free(c);
    }

}
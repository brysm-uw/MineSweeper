#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    

    TEST(TypedArray,pop) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        EXPECT_DOUBLE_EQ(m.pop(), 6);
        ASSERT_EQ(m.size(), 2);
    }
    
    TEST(TypedArray,pop_front) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        EXPECT_DOUBLE_EQ(m.pop_front(), 1);
        ASSERT_EQ(m.size(), 2);
    }

    TEST(TypedArray,push) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        m.push(7);
        ASSERT_EQ(m.buffer[3], 7);
    }

    TEST(TypedArray,push_front) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        m.push_front(7);
        ASSERT_EQ(m.buffer[0], 7);
    }

    TEST(TypedArray,concat) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        TypedArray<TypedArray<double>> n;
        m.set(0,9);
        m.set(1,12);
        m.set(2,15);
        TypedArray<TypedArray<double>> o;
        o = m.concat(n);
        TypedArray<TypedArray<double>> p;
        p.set(0,1);
        p.set(1,3);
        p.set(2,6);
        p.set(3,9);
        p.set(4,12);
        p.set(5,15);
        ASSERT_EQ(o, p);
    }

    TEST(TypedArray,reverse) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        TypedArray<TypedArray<double>>n;
        n.set(0,6);
        n.set(1,3);
        n.set(2,1);
        ASSERT_EQ(m.reverse(), n);
    }

    TEST(TypedArray,concat) {
        TypedArray<TypedArray<double>> m;
        m.set(0,1);
        m.set(1,3);
        m.set(2,6);
        TypedArray<TypedArray<double>> n;
        m.set(0,9);
        m.set(1,12);
        m.set(2,15);
        TypedArray<TypedArray<double>> o;
        o = m + n;
        TypedArray<TypedArray<double>> p;
        p.set(0,1);
        p.set(1,3);
        p.set(2,6);
        p.set(3,9);
        p.set(4,12);
        p.set(5,15);
        ASSERT_EQ(o, p);
    }

    TEST(Complex, real) {
        Complex a = Complex(1,2);
        ASSERT_EQ(a.real(), 1);
    }

    TEST(Complex, imaginary) {
        Complex a = Complex(1,2);
        ASSERT_EQ(a.imaginary(), 2);
    }

    TEST(Complex, conjugate) {
        Complex a = Complex(1,2);
        ASSERT_EQ(a.conjugate(), Complex(1,-2));
    }

    TEST(Complex, add) {
        Complex a = Complex(1,2);
        Complex b = Complex(3,4);
        ASSERT_EQ(a + b, Complex(4,6));
    }

    TEST(Complex, mutiply) {
        Complex a = Complex(1,2);
        Complex b = Complex(3,4);
        ASSERT_EQ(a * b, Complex(-5, 10));
    }

    TEST(Complex, equate) {
        Complex a = Complex(1,2);
        Complex b = Complex(1,2);
        Complex c = Complex(3,4);
        ASSERT_EQ(a == b, true);
        ASSERT_EQ(a == c, false);
    }
}
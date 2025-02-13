#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"
#include "complex.h"

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
        TypedArray<double> m;
        m.push(1);
        m.push(3);
        m.push(6);
        EXPECT_DOUBLE_EQ(m.pop(), 6);
        ASSERT_EQ(m.size(), 2);
    }
    
    TEST(TypedArray,pop_front) {
        TypedArray<double> m;
        m.push(1);
        m.push(3);
        m.push(6);
        EXPECT_DOUBLE_EQ(m.pop_front(), 1);
        ASSERT_EQ(m.size(), 2);
    }

    TEST(TypedArray,push) {
        TypedArray<double> m;
        m.push(1);
        m.push(3);
        m.push(6);
        m.push(7);
        ASSERT_EQ(m.safe_get(3), 7);
    }

    TEST(TypedArray,push_front) {
        TypedArray<double> m;
        m.push(1);
        m.push(3);
        m.push(6);
        m.push_front(7);
        ASSERT_EQ(m.safe_get(0), 7);
    }

    TEST(TypedArray,concat) {
        TypedArray<double> m;
        m.push(1);
        m.push(3);
        m.push(6);
        TypedArray<double> n;
        n.push(9);
        n.push(12);
        n.push(15);
        TypedArray<double> o;
        o = m.concat(n);
        TypedArray<double> p;
        p.push(1);
        p.push(3);
        p.push(6);
        p.push(9);
        p.push(12);
        p.push(15);
        for (int idx = 0; idx < 5; idx++) {
            ASSERT_EQ(p.safe_get(idx), o.safe_get(idx));
        }
    }

    TEST(TypedArray, reverse) {
        TypedArray<double> m;
        m.set(0,1);
        m.push(3);
        m.push(6);
        
        TypedArray<double> n = m;
        n.reverse();
        
        for (int idx = 0; idx < m.size(); idx++) {
            ASSERT_EQ(m.safe_get(idx), n.safe_get(m.size() - 1 - idx));
        }
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
        ASSERT_EQ(a, b);
        ASSERT_FALSE(a == c);
    }
}
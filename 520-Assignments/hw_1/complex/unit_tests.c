#include "complex.h"
#include "gtest/gtest.h"
#include <math.h>
namespace {

    TEST(Complex, Basics) {
        Complex a = (Complex) { 2, 3 },
                b = (Complex) { 4, 5 };
        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,8);
        EXPECT_EQ(multiply(a,b).real,-7);
        EXPECT_EQ(multiply(a,b).im,22);
        EXPECT_EQ(negate(a).real,-2);
        EXPECT_EQ(negate(a).im, -3);
        EXPECT_EQ(magnitude(a),sqrt(13));
    }

}
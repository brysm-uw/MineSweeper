#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"
#include "utilities.h"
#include <fstream>
#include <algorithm>

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
    TEST(Occurence_map, example1) {
        const std::string filePath = "test_input.txt";
        std::ofstream testFile(filePath);
        testFile << "This is a sentence. Don't think of wier_d strings as words. Really, 123 is a nice number." << std::endl;
        testFile.close();

        // Expected output
        std::map<std::string, int> expected = {
            {"this", 1}, {"is", 2}, {"a", 2}, {"sentence", 1}, {"don't", 1}, {"think", 1},
            {"of", 1}, {"strings", 1}, {"as", 1}, {"words", 1}, {"really", 1}, {"123", 1},
            {"nice", 1}, {"number", 1}
        };

        // Actual output
        std::map<std::string, int> actual = occurence_map(filePath);
        std::remove(filePath.c_str());
        EXPECTED_EQ(expected, actual);
    }
    
    TEST(Occurence_map, example3) {
        const std::string filePath = "test_input.txt";
        std::ofstream testFile(filePath);
        testFile << "George Mallory's famous quote: \"My mind is in a state of constant rebellion.\"" << std::endl;
        testFile.close();

        // Expected output
        std::map<std::string, int> expected = {
            {"george", 1}, {"mallory's", 1}, {"famous", 1}, {"quote", 1},
            {"my", 1}, {"mind", 1}, {"is", 1}, {"in", 1}, {"a", 1},
            {"state", 1}, {"of", 1}, {"constant", 1}, {"rebellion", 1}
        };

        // Actual output
        std::map<std::string, int> actual = occurence_map(filePath);
        std::remove(filePath.c_str());
        EXPECTED_EQ(expected, actual);
    }

}
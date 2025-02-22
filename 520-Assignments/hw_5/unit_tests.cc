#include "utilities.h"
#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include <map>
#include <fstream>
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

    TEST(SortByMagnitude, test1) {
        std::vector<double> actual = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
        std::vector<double> expected = {0,1,1,2,2,3,3,4,4,5,5};
        sort_by_magnitude(actual);
        EXPECT_EQ(expected, actual);
    }
    
    TEST(ReadMatrixCSV, validTest) {
        std::ofstream validFile("valid.csv");
        validFile << "1.0, 2.0, 3.0\n4.0, 5.0, 6.0\n7.0, 8.0, 9.0\n";
        validFile.close();

        // Create inner TypedArray<double> instances
        TypedArray<double> row1;
        row1.set(0,1.0);
        row1.set(1,2.0);
        row1.set(2,3.0);

        TypedArray<double> row2;
        row2.set(0,4.0);
        row2.set(1,5.0);
        row2.set(2,6.0);

        TypedArray<double> row3;
        row3.set(0,7.0);
        row3.set(1,8.0);
        row3.set(2,9.0);
        
        TypedArray<TypedArray<double>> expected;
        expected.set(0,row1);
        expected.set(1,row2);
        expected.set(2,row3);
        
        TypedArray<TypedArray<double>> actual = read_matrix_csv("valid.csv");
        ASSERT_EQ(actual.size(), expected.size());
        for (size_t i = 0; i < actual.size(); i++) {
            ASSERT_EQ(actual.get(i).size(), expected.get(i).size());
            for (size_t j = 0; j < actual.size(); j++) {
                ASSERT_DOUBLE_EQ(actual.get(i).get(j), expected.get(i).get(j));
            }
        }
        
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
        std::map<std::string, int> actual = occurrence_map(filePath);
        std::remove(filePath.c_str());
        ASSERT_EQ(expected, actual);
    }

    TEST(Occurence_map, example2) {
        const std::string filePath = "test_input.txt";
        std::ofstream testFile(filePath);
        testFile << "\'I should use double quotes\'" << std::endl;
        testFile.close();

        // Expected output
        std::map<std::string, int> expected = {
            {"'i", 1}, {"should", 1}, {"use", 1}, {"double", 1}, {"quotes'", 1}
        };

        // Actual output
        std::map<std::string, int> actual = occurrence_map(filePath);
        std::remove(filePath.c_str());
        ASSERT_EQ(expected, actual);
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
        std::map<std::string, int> actual = occurrence_map(filePath);
        std::remove(filePath.c_str());
        ASSERT_EQ(expected, actual);
    }

    TEST(Occurence_map, example4) {
        const std::string filePath = "test_input.txt";
        std::ofstream testFile(filePath);
        testFile << "10XGenomics (a biotech company) is quoted as saying \"blah blah blah.\"" << std::endl;
        testFile.close();

        // Expected output
        std::map<std::string, int> expected = {
            {"10xgenomics", 1}, {"a", 1}, {"biotech", 1}, {"company", 1}, {"is", 1}, {"quoted", 1}, {"as", 1}, {"saying", 1}, {"blah", 3}
        };

        // Actual output
        std::map<std::string, int> actual = occurrence_map(filePath);
        std::remove(filePath.c_str());
        ASSERT_EQ(expected, actual);
    }

    TEST(Occurence_map, example5) {
        const std::string filePath = "test_input.txt";
        std::ofstream testFile(filePath);
        testFile << "the)s are no%y6 wo!e4" << std::endl;
        testFile.close();

        // Expected output
        std::map<std::string, int> expected = {
            {"are", 1}
        };

        // Actual output
        std::map<std::string, int> actual = occurrence_map(filePath);
        std::remove(filePath.c_str());
        ASSERT_EQ(expected, actual);
    }
}
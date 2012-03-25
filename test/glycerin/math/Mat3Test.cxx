/*
 * Mat3Test.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/common.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/math/Mat3.hpp"
using namespace std;
namespace Glycerin {

/*
 * Constants
 */
const double TOLERANCE = 1e-9;


/**
 * Unit test for Mat3.
 */
class Mat3Test : public CppUnit::TestFixture {
private:
    Mat3 m1, m2, m3;
public:

    /**
     * Prepares the fixture before running each test case.
     */
    void setUp() {

        double arr[3][3];
        arr[0][0] = 1; arr[1][0] = 6; arr[2][0] = 5;
        arr[0][1] = 7; arr[1][1] = 2; arr[2][1] = 8;
        arr[0][2] = 4; arr[1][2] = 9; arr[2][2] = 3;

        m1 = Mat3::fromArrayInColumnMajor(arr);
        m2 = Mat3(1.0);
        m3 = Mat3(1.0);
    }

    /**
     * Ensures the sign chart used for calculating a matrix of cofactors was set up correctly.
     */
    void testCreateSignChart() {
        CPPUNIT_ASSERT_EQUAL(+1, Mat3::SIGN_CHART(0,0));
        CPPUNIT_ASSERT_EQUAL(-1, Mat3::SIGN_CHART(0,1));
        CPPUNIT_ASSERT_EQUAL(+1, Mat3::SIGN_CHART(0,2));
        CPPUNIT_ASSERT_EQUAL(-1, Mat3::SIGN_CHART(1,0));
        CPPUNIT_ASSERT_EQUAL(+1, Mat3::SIGN_CHART(1,1));
        CPPUNIT_ASSERT_EQUAL(-1, Mat3::SIGN_CHART(1,2));
        CPPUNIT_ASSERT_EQUAL(+1, Mat3::SIGN_CHART(2,0));
        CPPUNIT_ASSERT_EQUAL(-1, Mat3::SIGN_CHART(2,1));
        CPPUNIT_ASSERT_EQUAL(+1, Mat3::SIGN_CHART(2,2));
    }

    /**
     * Ensures the chart used for calculating a matrix of minors was set up correctly.
     */
    void testCreateMinorChart() {

        typedef Mat3::index_t index_t;
        const index_t *idx;

        // Index 0,0
        idx = Mat3::MINOR_CHART(0,0);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[3]);

        // Index 0,1
        idx = Mat3::MINOR_CHART(0,1);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[3]);

        // Index 0,2
        idx = Mat3::MINOR_CHART(0,2);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[3]);

        // Index 1,0
        idx = Mat3::MINOR_CHART(1,0);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[3]);

        // Index 1,1
        idx = Mat3::MINOR_CHART(1,1);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[3]);

        // Index 1,2
        idx = Mat3::MINOR_CHART(1,2);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[3]);

        // Index 2,0
        idx = Mat3::MINOR_CHART(2,0);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[3]);

        // Index 2,1
        idx = Mat3::MINOR_CHART(2,1);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[3]);

        // Index 2,2
        idx = Mat3::MINOR_CHART(2,2);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[3]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a one-dimensional double array.
     */
    void testFromArrayInColumnMajorDoubleArray() {

        // Make an array in column-major order
        double arr[9];
        arr[0] = 1; arr[3] = 2; arr[6] = 3;
        arr[1] = 4; arr[4] = 5; arr[7] = 6;
        arr[2] = 7; arr[5] = 8; arr[8] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a one-dimensional float array.
     */
    void testFromArrayInColumnMajorFloatArray() {

        // Make an array in column-major order
        float arr[9];
        arr[0] = 1; arr[3] = 2; arr[6] = 3;
        arr[1] = 4; arr[4] = 5; arr[7] = 6;
        arr[2] = 7; arr[5] = 8; arr[8] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a two-dimensional double array.
     */
    void testFromArrayInColumnMajorDoubleArrayArray() {

        // Make an array
        double arr[3][3];
        arr[0][0] = 1; arr[1][0] = 2; arr[2][0] = 3;
        arr[0][1] = 4; arr[1][1] = 5; arr[2][1] = 6;
        arr[0][2] = 7; arr[1][2] = 8; arr[2][2] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a two-dimensional float array.
     */
    void testFromArrayInColumnMajorFloatArrayArray() {

        // Make an array
        float arr[3][3];
        arr[0][0] = 1; arr[1][0] = 2; arr[2][0] = 3;
        arr[0][1] = 4; arr[1][1] = 5; arr[2][1] = 6;
        arr[0][2] = 7; arr[1][2] = 8; arr[2][2] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a one-dimensional double array.
     */
    void testFromArrayInRowMajorDoubleArray() {

        // Make an array in row major
        double arr[9];
        arr[0] = 1; arr[1] = 2; arr[2] = 3;
        arr[3] = 4; arr[4] = 5; arr[5] = 6;
        arr[6] = 7; arr[7] = 8; arr[8] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a one-dimensional float array.
     */
    void testFromArrayInRowMajorFloatArray() {

        // Make an array in row major
        float arr[9];
        arr[0] = 1; arr[1] = 2; arr[2] = 3;
        arr[3] = 4; arr[4] = 5; arr[5] = 6;
        arr[6] = 7; arr[7] = 8; arr[8] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a two-dimensional double array.
     */
    void testFromArrayInRowMajorDoubleArrayArray() {

        // Make an array in row major
        double arr[3][3];
        arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
        arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;
        arr[2][0] = 7; arr[2][1] = 8; arr[2][2] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a two-dimensional float array.
     */
    void testFromArrayInRowMajorFloatArrayArray() {

        // Make an array in row major
        float arr[3][3];
        arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
        arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;
        arr[2][0] = 7; arr[2][1] = 8; arr[2][2] = 9;

        // Make a matrix from the array
        Mat3 m = Mat3::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL(1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL(2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL(3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL(4.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL(5.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL(6.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL(7.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(8.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(9.0, m[2][2]);
    }

    /**
     * Ensures the inverse function works correctly.
     */
    void testInverse() {

        m2 = inverse(m1);
        m3 = m1 * m2;

        for (int i = 0; i < Mat3::ORDER; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m3[i][i], TOLERANCE);
        }

        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = i + 1; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3[j][i], TOLERANCE);
            }
        }

        for (int i = 1; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < i; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3[j][i], TOLERANCE);
            }
        }
    }

    /**
     * Ensures creating a matrix from a one dimensional array works correctly.
     */
    void testSetArray() {

        double arr[9] = {
                1.0, 4.0, 7.0,
                2.0, 5.0, 8.0,
                3.0, 6.0, 9.0 };
        m2 = Mat3::fromArrayInColumnMajor(arr);

        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(arr[j * Mat3::ORDER + i], m2[j][i], TOLERANCE);
            }
        }
    }

    /**
     * Ensures toString returns the correct string.
     */
    void testToString() {

        // Make a matrix
        Mat3 mat;
        mat[0][0] = 1; mat[1][0] = 2; mat[2][0] = 3;
        mat[0][1] = 4; mat[1][1] = 5; mat[2][1] = 6;
        mat[0][2] = 7; mat[1][2] = 8; mat[2][2] = 9;

        // Make expected and actual strings, and compare
        const string expect = "[[1, 4, 7], [2, 5, 8], [3, 6, 9]]";
        const string result = mat.toString();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures transposing a matrix works correctly.
     */
    void testTranspose() {
        m2 = transpose(m1);
        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(m1[j][i], m2[i][j], TOLERANCE);
            }
        }
    }

    /**
     * Ensures multiplying by a matrix works correctly.
     */
    void testMultiplyMatrix() {

        m3 = m1 * m2;

        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(m1[j][i], m3[j][i], TOLERANCE);
            }
        }
    }

    /**
     * Ensures multiplying a vector by a matrix works correctly.
     */
    void testMultiplyVector() {

        double arr[3][3];
        arr[0][0] = 1; arr[1][0] = 7; arr[2][0] = 4;
        arr[0][1] = 6; arr[1][1] = 2; arr[2][1] = 9;
        arr[0][2] = 5; arr[1][2] = 8; arr[2][2] = 3;

        Vec3 u(8.0, 3.0, 5.0);
        Vec3 v = m1 * u;

        // v.x = (1 * 8) + (6 * 3) + (5 * 5)
        // v.y = (7 * 8) + (2 * 3) + (8 * 5)
        // v.z = (4 * 8) + (9 * 3) + (3 * 5)

        // v.x = 8 + 18 + 25
        // v.y = 56 + 6 + 40
        // v.z = 32 + 27 + 15

        // v.x = 51
        // v.y = 102
        // v.z = 74

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 51.0, v.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(102.0, v.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 74.0, v.z, TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(Mat3Test);
    CPPUNIT_TEST(testCreateSignChart);
    CPPUNIT_TEST(testCreateMinorChart);
    CPPUNIT_TEST(testFromArrayInColumnMajorDoubleArray);
    CPPUNIT_TEST(testFromArrayInColumnMajorFloatArray);
    CPPUNIT_TEST(testFromArrayInColumnMajorDoubleArrayArray);
    CPPUNIT_TEST(testFromArrayInColumnMajorFloatArrayArray);
    CPPUNIT_TEST(testFromArrayInRowMajorDoubleArray);
    CPPUNIT_TEST(testFromArrayInRowMajorFloatArray);
    CPPUNIT_TEST(testFromArrayInRowMajorDoubleArrayArray);
    CPPUNIT_TEST(testFromArrayInRowMajorFloatArrayArray);
    CPPUNIT_TEST(testInverse);
    CPPUNIT_TEST(testSetArray);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testTranspose);
    CPPUNIT_TEST(testMultiplyVector);
    CPPUNIT_TEST(testMultiplyMatrix);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char *argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::Mat3Test::suite());
    runner.run();
    return 0;
}

std::ostream& operator<<(std::ostream& stream, const std::pair<int,int> &pair) {
    stream << "[";
    stream << pair.first;
    stream << ", ";
    stream << pair.second;
    stream << "]";
    return stream;
}

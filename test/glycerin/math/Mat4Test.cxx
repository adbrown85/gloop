/*
 * Mat4Test.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/common.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/math/Mat4.hpp"
using namespace std;
namespace Glycerin {

/*
 * Constants
 */
const double TOLERANCE = 1e-9;


/**
 * Unit test for Mat4.
 */
class Mat4Test : public CppUnit::TestFixture {
private:
    Mat4 m1, m2, m3;
public:

    /**
     * Prepares the fixture before running each test case.
     */
    void setUp() {

        double arr[4][4];
        arr[0][0] = 4; arr[1][0] = 4; arr[2][0] = 8; arr[3][0] = 7;
        arr[0][1] = 3; arr[1][1] = 2; arr[2][1] = 4; arr[3][1] = 6;
        arr[0][2] = 1; arr[1][2] = 6; arr[2][2] = 4; arr[3][2] = 5;
        arr[0][3] = 1; arr[1][3] = 2; arr[2][3] = 3; arr[3][3] = 4;

        m1 = Mat4::fromArrayInColumnMajor(arr);
        m2 = Mat4(1.0);
        m3 = Mat4(1.0);
    }

    /**
     * Ensures the sign chart used for calculating a matrix of cofactors was set up correctly.
     */
    void testCreateSignChart() {
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(0,0));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(0,1));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(0,2));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(0,3));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(1,0));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(1,1));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(1,2));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(1,3));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(2,0));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(2,1));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(2,2));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(2,3));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(3,0));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(3,1));
        CPPUNIT_ASSERT_EQUAL(-1, Mat4::SIGN_CHART(3,2));
        CPPUNIT_ASSERT_EQUAL(+1, Mat4::SIGN_CHART(3,3));
    }

    /**
     * Ensures the chart used for calculating a matrix of minors was set up correctly.
     */
    void testCreateMinorChart() {

        typedef Mat4::index_t index_t;
        const index_t *idx;

        // Index 0,0
        idx = Mat4::MINOR_CHART(0,0);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 0,1
        idx = Mat4::MINOR_CHART(0,1);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 0,2
        idx = Mat4::MINOR_CHART(0,2);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 0,3
        idx = Mat4::MINOR_CHART(0,3);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[8]);

        // Index 1,0
        idx = Mat4::MINOR_CHART(1,0);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 1,1
        idx = Mat4::MINOR_CHART(1,1);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 1,2
        idx = Mat4::MINOR_CHART(1,2);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 1,3
        idx = Mat4::MINOR_CHART(1,3);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[8]);

        // Index 2,0
        idx = Mat4::MINOR_CHART(2,0);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 2,1
        idx = Mat4::MINOR_CHART(2,1);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 2,2
        idx = Mat4::MINOR_CHART(2,2);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,3), idx[8]);

        // Index 2,3
        idx = Mat4::MINOR_CHART(2,3);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(3,2), idx[8]);

        // Index 3,0
        idx = Mat4::MINOR_CHART(3,0);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[8]);

        // Index 3,1
        idx = Mat4::MINOR_CHART(3,1);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[8]);

        // Index 3,2
        idx = Mat4::MINOR_CHART(3,2);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,3), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,3), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,3), idx[8]);

        // Index 3,3
        idx = Mat4::MINOR_CHART(3,3);
        CPPUNIT_ASSERT_EQUAL(index_t(0,0), idx[0]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,1), idx[1]);
        CPPUNIT_ASSERT_EQUAL(index_t(0,2), idx[2]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,0), idx[3]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,1), idx[4]);
        CPPUNIT_ASSERT_EQUAL(index_t(1,2), idx[5]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,0), idx[6]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,1), idx[7]);
        CPPUNIT_ASSERT_EQUAL(index_t(2,2), idx[8]);
    }

    /**
     * Ensures the constructor taking a 3x3 matrix works correctly.
     */
    void testConstructorMat3() {

        // Make a 3x3 matrix
        Mat3 m3;
        m3[0][0] = 1; m3[1][0] = 2; m3[2][0] = 3;
        m3[0][1] = 4; m3[1][1] = 5; m3[2][1] = 6;
        m3[0][2] = 7; m3[1][2] = 8; m3[2][2] = 9;

        // Make a 4x4 matrix from it
        const Mat4 m4(m3);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, m4[0][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2, m4[1][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3, m4[2][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m4[3][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4, m4[0][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(5, m4[1][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(6, m4[2][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m4[3][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(7, m4[0][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(8, m4[1][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(9, m4[2][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m4[3][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m4[0][3], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m4[1][3], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m4[2][3], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, m4[3][3], TOLERANCE);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a one-dimensional double array.
     */
    void testFromArrayInColumnMajorDoubleArray() {

        // Make an array in column-major order
        double arr[16];
        arr[ 0] =  1; arr[ 4] =  2; arr[ 8] =  3; arr[12] =  4;
        arr[ 1] =  5; arr[ 5] =  6; arr[ 9] =  7; arr[13] =  8;
        arr[ 2] =  9; arr[ 6] = 10; arr[10] = 11; arr[14] = 12;
        arr[ 3] = 13; arr[ 7] = 14; arr[11] = 15; arr[15] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a one-dimensional float array.
     */
    void testFromArrayInColumnMajorFloatArray() {

        // Make an array in column-major order
        float arr[16];
        arr[ 0] =  1; arr[ 4] =  2; arr[ 8] =  3; arr[12] =  4;
        arr[ 1] =  5; arr[ 5] =  6; arr[ 9] =  7; arr[13] =  8;
        arr[ 2] =  9; arr[ 6] = 10; arr[10] = 11; arr[14] = 12;
        arr[ 3] = 13; arr[ 7] = 14; arr[11] = 15; arr[15] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a two-dimensional double array.
     */
    void testFromArrayInColumnMajorDoubleArrayArray() {

        // Make an array in column-major order
        double arr[4][4];
        arr[0][0] =  1; arr[1][0] =  2; arr[2][0] =  3; arr[3][0] =  4;
        arr[0][1] =  5; arr[1][1] =  6; arr[2][1] =  7; arr[3][1] =  8;
        arr[0][2] =  9; arr[1][2] = 10; arr[2][2] = 11; arr[3][2] = 12;
        arr[0][3] = 13; arr[1][3] = 14; arr[2][3] = 15; arr[3][3] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInColumnMajor works with a two-dimensional float array.
     */
    void testFromArrayInColumnMajorFloatArrayArray() {

        // Make an array in column-major order
        float arr[4][4];
        arr[0][0] =  1; arr[1][0] =  2; arr[2][0] =  3; arr[3][0] =  4;
        arr[0][1] =  5; arr[1][1] =  6; arr[2][1] =  7; arr[3][1] =  8;
        arr[0][2] =  9; arr[1][2] = 10; arr[2][2] = 11; arr[3][2] = 12;
        arr[0][3] = 13; arr[1][3] = 14; arr[2][3] = 15; arr[3][3] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a one-dimensional double array.
     */
    void testFromArrayInRowMajorDoubleArray() {

        // Make an array in row-major order
        double arr[16];
        arr[ 0] =  1; arr[ 1] =  2; arr[ 2] =  3; arr[ 3] =  4;
        arr[ 4] =  5; arr[ 5] =  6; arr[ 6] =  7; arr[ 7] =  8;
        arr[ 8] =  9; arr[ 9] = 10; arr[10] = 11; arr[11] = 12;
        arr[12] = 13; arr[13] = 14; arr[14] = 15; arr[15] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a one-dimensional float array.
     */
    void testFromArrayInRowMajorFloatArray() {

        // Make an array in row-major order
        float arr[16];
        arr[ 0] =  1; arr[ 1] =  2; arr[ 2] =  3; arr[ 3] =  4;
        arr[ 4] =  5; arr[ 5] =  6; arr[ 6] =  7; arr[ 7] =  8;
        arr[ 8] =  9; arr[ 9] = 10; arr[10] = 11; arr[11] = 12;
        arr[12] = 13; arr[13] = 14; arr[14] = 15; arr[15] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a two-dimensional double array.
     */
    void testFromArrayInRowMajorDoubleArrayArray() {

        // Make an array in row-major order
        double arr[4][4];
        arr[0][0] =  1; arr[0][1] =  2; arr[0][2] =  3; arr[0][3] =  4;
        arr[1][0] =  5; arr[1][1] =  6; arr[1][2] =  7; arr[1][3] =  8;
        arr[2][0] =  9; arr[2][1] = 10; arr[2][2] = 11; arr[2][3] = 12;
        arr[3][0] = 13; arr[3][1] = 14; arr[3][2] = 15; arr[3][3] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromArrayInRowMajor works with a two-dimensional float array.
     */
    void testFromArrayInRowMajorFloatArrayArray() {

        // Make an array in row-major order
        float arr[4][4];
        arr[0][0] =  1; arr[0][1] =  2; arr[0][2] =  3; arr[0][3] =  4;
        arr[1][0] =  5; arr[1][1] =  6; arr[1][2] =  7; arr[1][3] =  8;
        arr[2][0] =  9; arr[2][1] = 10; arr[2][2] = 11; arr[2][3] = 12;
        arr[3][0] = 13; arr[3][1] = 14; arr[3][2] = 15; arr[3][3] = 16;

        // Make a matrix from the array
        Mat4 m = Mat4::fromArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, m[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, m[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, m[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, m[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, m[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, m[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, m[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, m[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, m[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, m[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, m[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, m[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, m[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, m[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, m[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, m[3][3]);
    }

    /**
     * Ensures fromColumns works correctly.
     */
    void testFromColumns() {

        // Define columns
        const Vec4 c1(1, 5, 9, 13);
        const Vec4 c2(2, 6, 10, 14);
        const Vec4 c3(3, 7, 11, 15);
        const Vec4 c4(4, 8, 12, 16);

        // Make a matrix from the columns
        const Mat4 mat = Mat4::fromColumns(c1, c2, c3, c4);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, mat[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, mat[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, mat[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, mat[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, mat[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, mat[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, mat[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, mat[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, mat[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, mat[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, mat[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, mat[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, mat[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, mat[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, mat[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, mat[3][3]);
    }

    /**
     * Ensures fromRows works correctly.
     */
    void testFromRows() {

        // Define rows
        const Vec4 r1(1, 2, 3, 4);
        const Vec4 r2(5, 6, 7, 8);
        const Vec4 r3(9, 10, 11, 12);
        const Vec4 r4(13, 14, 15, 16);

        // Make a matrix from the rows
        const Mat4 mat = Mat4::fromRows(r1, r2, r3, r4);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, mat[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, mat[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, mat[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, mat[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, mat[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, mat[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, mat[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, mat[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, mat[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, mat[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, mat[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, mat[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, mat[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, mat[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, mat[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, mat[3][3]);
    }

    /**
     * Ensures the inverse function works correctly.
     */
    void testInverse() {

        m2 = inverse(m1);
        m3 = m1 * m2;

        for (int i = 0; i < 4; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m3[i][i], TOLERANCE);
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3[j][i], TOLERANCE);
            }
        }

        for (int i = 1; i < 4; ++i) {
            for (int j = 0; j < i; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3[j][i], TOLERANCE);
            }
        }

    }

    /**
     * Ensures creating a matrix from a one dimensional array works correctly.
     */
    void testSetArray() {

        double arr[16] = {
            1.0,  2.0,  3.0,  4.0,
            5.0,  6.0,  7.0,  8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0};
        m2 = Mat4::fromArrayInColumnMajor(arr);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                CPPUNIT_ASSERT_EQUAL(arr[j * 4 + i], m2[j][i]);
            }
        }
    }

    /**
     * Ensures toArrayInColumnMajor works with a one-dimensional double array.
     */
    void testToArrayInColumnMajorDoubleArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        double arr[16];
        mat.toArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, arr[ 0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, arr[ 1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, arr[ 2]);
        CPPUNIT_ASSERT_EQUAL(13.0, arr[ 3]);
        CPPUNIT_ASSERT_EQUAL( 2.0, arr[ 4]);
        CPPUNIT_ASSERT_EQUAL( 6.0, arr[ 5]);
        CPPUNIT_ASSERT_EQUAL(10.0, arr[ 6]);
        CPPUNIT_ASSERT_EQUAL(14.0, arr[ 7]);
        CPPUNIT_ASSERT_EQUAL( 3.0, arr[ 8]);
        CPPUNIT_ASSERT_EQUAL( 7.0, arr[ 9]);
        CPPUNIT_ASSERT_EQUAL(11.0, arr[10]);
        CPPUNIT_ASSERT_EQUAL(15.0, arr[11]);
        CPPUNIT_ASSERT_EQUAL( 4.0, arr[12]);
        CPPUNIT_ASSERT_EQUAL( 8.0, arr[13]);
        CPPUNIT_ASSERT_EQUAL(12.0, arr[14]);
        CPPUNIT_ASSERT_EQUAL(16.0, arr[15]);
    }

    /**
     * Ensures toArrayInColumnMajor works with a one-dimensional float array.
     */
    void testToArrayInColumnMajorFloatArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        float arr[16];
        mat.toArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0f, arr[ 0]);
        CPPUNIT_ASSERT_EQUAL( 5.0f, arr[ 1]);
        CPPUNIT_ASSERT_EQUAL( 9.0f, arr[ 2]);
        CPPUNIT_ASSERT_EQUAL(13.0f, arr[ 3]);
        CPPUNIT_ASSERT_EQUAL( 2.0f, arr[ 4]);
        CPPUNIT_ASSERT_EQUAL( 6.0f, arr[ 5]);
        CPPUNIT_ASSERT_EQUAL(10.0f, arr[ 6]);
        CPPUNIT_ASSERT_EQUAL(14.0f, arr[ 7]);
        CPPUNIT_ASSERT_EQUAL( 3.0f, arr[ 8]);
        CPPUNIT_ASSERT_EQUAL( 7.0f, arr[ 9]);
        CPPUNIT_ASSERT_EQUAL(11.0f, arr[10]);
        CPPUNIT_ASSERT_EQUAL(15.0f, arr[11]);
        CPPUNIT_ASSERT_EQUAL( 4.0f, arr[12]);
        CPPUNIT_ASSERT_EQUAL( 8.0f, arr[13]);
        CPPUNIT_ASSERT_EQUAL(12.0f, arr[14]);
        CPPUNIT_ASSERT_EQUAL(16.0f, arr[15]);
    }

    /**
     * Ensures toArrayInColumnMajor works with a two-dimensional double array.
     */
    void testToArrayInColumnMajorDoubleArrayArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        double arr[4][4];
        mat.toArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, arr[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, arr[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0, arr[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0, arr[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0, arr[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0, arr[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, arr[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0, arr[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0, arr[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0, arr[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0, arr[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, arr[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0, arr[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0, arr[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0, arr[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0, arr[3][3]);
    }

    /**
     * Ensures toArrayInColumnMajor works with a two-dimensional float array.
     */
    void testToArrayInColumnMajorFloatArrayArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        float arr[4][4];
        mat.toArrayInColumnMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0f, arr[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0f, arr[1][0]);
        CPPUNIT_ASSERT_EQUAL( 3.0f, arr[2][0]);
        CPPUNIT_ASSERT_EQUAL( 4.0f, arr[3][0]);
        CPPUNIT_ASSERT_EQUAL( 5.0f, arr[0][1]);
        CPPUNIT_ASSERT_EQUAL( 6.0f, arr[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0f, arr[2][1]);
        CPPUNIT_ASSERT_EQUAL( 8.0f, arr[3][1]);
        CPPUNIT_ASSERT_EQUAL( 9.0f, arr[0][2]);
        CPPUNIT_ASSERT_EQUAL(10.0f, arr[1][2]);
        CPPUNIT_ASSERT_EQUAL(11.0f, arr[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0f, arr[3][2]);
        CPPUNIT_ASSERT_EQUAL(13.0f, arr[0][3]);
        CPPUNIT_ASSERT_EQUAL(14.0f, arr[1][3]);
        CPPUNIT_ASSERT_EQUAL(15.0f, arr[2][3]);
        CPPUNIT_ASSERT_EQUAL(16.0f, arr[3][3]);
    }

    /**
     * Ensures toArrayInRowMajor works with a one-dimensional double array.
     */
    void testToArrayInRowMajorDoubleArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        double arr[16];
        mat.toArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, arr[ 0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, arr[ 1]);
        CPPUNIT_ASSERT_EQUAL( 3.0, arr[ 2]);
        CPPUNIT_ASSERT_EQUAL( 4.0, arr[ 3]);
        CPPUNIT_ASSERT_EQUAL( 5.0, arr[ 4]);
        CPPUNIT_ASSERT_EQUAL( 6.0, arr[ 5]);
        CPPUNIT_ASSERT_EQUAL( 7.0, arr[ 6]);
        CPPUNIT_ASSERT_EQUAL( 8.0, arr[ 7]);
        CPPUNIT_ASSERT_EQUAL( 9.0, arr[ 8]);
        CPPUNIT_ASSERT_EQUAL(10.0, arr[ 9]);
        CPPUNIT_ASSERT_EQUAL(11.0, arr[10]);
        CPPUNIT_ASSERT_EQUAL(12.0, arr[11]);
        CPPUNIT_ASSERT_EQUAL(13.0, arr[12]);
        CPPUNIT_ASSERT_EQUAL(14.0, arr[13]);
        CPPUNIT_ASSERT_EQUAL(15.0, arr[14]);
        CPPUNIT_ASSERT_EQUAL(16.0, arr[15]);
    }

    /**
     * Ensures toArrayInRowMajor works with a one-dimensional float array.
     */
    void testToArrayInRowMajorFloatArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        float arr[16];
        mat.toArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0f, arr[ 0]);
        CPPUNIT_ASSERT_EQUAL( 2.0f, arr[ 1]);
        CPPUNIT_ASSERT_EQUAL( 3.0f, arr[ 2]);
        CPPUNIT_ASSERT_EQUAL( 4.0f, arr[ 3]);
        CPPUNIT_ASSERT_EQUAL( 5.0f, arr[ 4]);
        CPPUNIT_ASSERT_EQUAL( 6.0f, arr[ 5]);
        CPPUNIT_ASSERT_EQUAL( 7.0f, arr[ 6]);
        CPPUNIT_ASSERT_EQUAL( 8.0f, arr[ 7]);
        CPPUNIT_ASSERT_EQUAL( 9.0f, arr[ 8]);
        CPPUNIT_ASSERT_EQUAL(10.0f, arr[ 9]);
        CPPUNIT_ASSERT_EQUAL(11.0f, arr[10]);
        CPPUNIT_ASSERT_EQUAL(12.0f, arr[11]);
        CPPUNIT_ASSERT_EQUAL(13.0f, arr[12]);
        CPPUNIT_ASSERT_EQUAL(14.0f, arr[13]);
        CPPUNIT_ASSERT_EQUAL(15.0f, arr[14]);
        CPPUNIT_ASSERT_EQUAL(16.0f, arr[15]);
    }

    /**
     * Ensures toArrayInRowMajor works with a two-dimensional double array.
     */
    void testToArrayInRowMajorDoubleArrayArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        double arr[4][4];
        mat.toArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0, arr[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0, arr[0][1]);
        CPPUNIT_ASSERT_EQUAL( 3.0, arr[0][2]);
        CPPUNIT_ASSERT_EQUAL( 4.0, arr[0][3]);
        CPPUNIT_ASSERT_EQUAL( 5.0, arr[1][0]);
        CPPUNIT_ASSERT_EQUAL( 6.0, arr[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0, arr[1][2]);
        CPPUNIT_ASSERT_EQUAL( 8.0, arr[1][3]);
        CPPUNIT_ASSERT_EQUAL( 9.0, arr[2][0]);
        CPPUNIT_ASSERT_EQUAL(10.0, arr[2][1]);
        CPPUNIT_ASSERT_EQUAL(11.0, arr[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0, arr[2][3]);
        CPPUNIT_ASSERT_EQUAL(13.0, arr[3][0]);
        CPPUNIT_ASSERT_EQUAL(14.0, arr[3][1]);
        CPPUNIT_ASSERT_EQUAL(15.0, arr[3][2]);
        CPPUNIT_ASSERT_EQUAL(16.0, arr[3][3]);
    }

    /**
     * Ensures toArrayInRowMajor works with a two-dimensional float array.
     */
    void testToArrayInRowMajorFloatArrayArray() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make an array from the matrix
        float arr[4][4];
        mat.toArrayInRowMajor(arr);

        // Compare
        CPPUNIT_ASSERT_EQUAL( 1.0f, arr[0][0]);
        CPPUNIT_ASSERT_EQUAL( 2.0f, arr[0][1]);
        CPPUNIT_ASSERT_EQUAL( 3.0f, arr[0][2]);
        CPPUNIT_ASSERT_EQUAL( 4.0f, arr[0][3]);
        CPPUNIT_ASSERT_EQUAL( 5.0f, arr[1][0]);
        CPPUNIT_ASSERT_EQUAL( 6.0f, arr[1][1]);
        CPPUNIT_ASSERT_EQUAL( 7.0f, arr[1][2]);
        CPPUNIT_ASSERT_EQUAL( 8.0f, arr[1][3]);
        CPPUNIT_ASSERT_EQUAL( 9.0f, arr[2][0]);
        CPPUNIT_ASSERT_EQUAL(10.0f, arr[2][1]);
        CPPUNIT_ASSERT_EQUAL(11.0f, arr[2][2]);
        CPPUNIT_ASSERT_EQUAL(12.0f, arr[2][3]);
        CPPUNIT_ASSERT_EQUAL(13.0f, arr[3][0]);
        CPPUNIT_ASSERT_EQUAL(14.0f, arr[3][1]);
        CPPUNIT_ASSERT_EQUAL(15.0f, arr[3][2]);
        CPPUNIT_ASSERT_EQUAL(16.0f, arr[3][3]);
    }

    /**
     * Ensures conversion to a 3x3 matrix works correctly.
     */
    void testToMat3() {

        // Make the 4x4 matrix
        Mat4 m4;
        m4[0][0] =  1; m4[1][0] =  2; m4[2][0] =  3; m4[3][0] =  4;
        m4[0][1] =  5; m4[1][1] =  6; m4[2][1] =  7; m4[3][1] =  8;
        m4[0][2] =  9; m4[1][2] = 10; m4[2][2] = 11; m4[3][2] = 12;
        m4[0][3] = 13; m4[1][3] = 14; m4[2][3] = 15; m4[3][3] = 16;

        // Make the 3x3 matrix
        const Mat3 m3 = m4.toMat3();
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 1, m3[0][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 2, m3[1][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 3, m3[2][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 5, m3[0][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 6, m3[1][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 7, m3[2][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 9, m3[0][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(10, m3[1][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(11, m3[2][2], TOLERANCE);
    }

    /**
     * Ensures toString returns the correct string.
     */
    void testToString() {

        // Make a matrix
        Mat4 mat;
        mat[0][0] =  1; mat[1][0] =  2; mat[2][0] =  3; mat[3][0] =  4;
        mat[0][1] =  5; mat[1][1] =  6; mat[2][1] =  7; mat[3][1] =  8;
        mat[0][2] =  9; mat[1][2] = 10; mat[2][2] = 11; mat[3][2] = 12;
        mat[0][3] = 13; mat[1][3] = 14; mat[2][3] = 15; mat[3][3] = 16;

        // Make expected and actual strings, and compare
        const string expect = "[[1, 5, 9, 13], [2, 6, 10, 14], [3, 7, 11, 15], [4, 8, 12, 16]]";
        const string result = mat.toString();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures transposing a matrix works correctly.
     */
    void testTranspose() {

        // Make the matrix
        double arr[4][4];
        arr[0][0] = 4; arr[1][0] = 3; arr[2][0] = 1; arr[3][0] = 1;
        arr[0][1] = 4; arr[1][1] = 2; arr[2][1] = 6; arr[3][1] = 2;
        arr[0][2] = 8; arr[1][2] = 4; arr[2][2] = 4; arr[3][2] = 3;
        arr[0][3] = 7; arr[1][3] = 6; arr[2][3] = 5; arr[3][3] = 4;
        m2 = Mat4::fromArrayInColumnMajor(arr);

        // Transpose it and compare
        m3 = transpose(m1);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                CPPUNIT_ASSERT(m2[j][i] == m3[j][i]);
            }
        }
    }

    /**
     * Ensures multiplying by a matrix works correctly.
     */
    void testMultiplyMatrix() {

        m3 = m1 * m2;

        for (int i = 0; i < Mat4::ORDER; ++i) {
            for (int j = 0; j < Mat4::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(m1[j][i], m3[j][i], TOLERANCE);
            }
        }
    }

    /**
     * Ensures multiplying a vector by a matrix works correctly.
     */
    void testMultiplyVector() {

        Vec4 u(8.0, 3.0, 1.0, 7.0);
        Vec4 v = m1 * u;

        CPPUNIT_ASSERT(101.0 == v.x);
        CPPUNIT_ASSERT( 76.0 == v.y);
        CPPUNIT_ASSERT( 65.0 == v.z);
        CPPUNIT_ASSERT( 45.0 == v.w);
    }

    CPPUNIT_TEST_SUITE(Mat4Test);
    CPPUNIT_TEST(testCreateSignChart);
    CPPUNIT_TEST(testCreateMinorChart);
    CPPUNIT_TEST(testConstructorMat3);
    CPPUNIT_TEST(testFromArrayInColumnMajorDoubleArray);
    CPPUNIT_TEST(testFromArrayInColumnMajorFloatArray);
    CPPUNIT_TEST(testFromArrayInColumnMajorDoubleArrayArray);
    CPPUNIT_TEST(testFromArrayInColumnMajorFloatArrayArray);
    CPPUNIT_TEST(testFromArrayInRowMajorDoubleArray);
    CPPUNIT_TEST(testFromArrayInRowMajorFloatArray);
    CPPUNIT_TEST(testFromArrayInRowMajorDoubleArrayArray);
    CPPUNIT_TEST(testFromArrayInRowMajorFloatArrayArray);
    CPPUNIT_TEST(testFromColumns);
    CPPUNIT_TEST(testFromRows);
    CPPUNIT_TEST(testInverse);
    CPPUNIT_TEST(testSetArray);
    CPPUNIT_TEST(testToArrayInColumnMajorDoubleArray);
    CPPUNIT_TEST(testToArrayInColumnMajorFloatArray);
    CPPUNIT_TEST(testToArrayInColumnMajorDoubleArrayArray);
    CPPUNIT_TEST(testToArrayInColumnMajorFloatArrayArray);
    CPPUNIT_TEST(testToArrayInRowMajorDoubleArray);
    CPPUNIT_TEST(testToArrayInRowMajorFloatArray);
    CPPUNIT_TEST(testToArrayInRowMajorDoubleArrayArray);
    CPPUNIT_TEST(testToArrayInRowMajorFloatArrayArray);
    CPPUNIT_TEST(testToMat3);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testTranspose);
    CPPUNIT_TEST(testMultiplyVector);
    CPPUNIT_TEST(testMultiplyMatrix);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char *argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::Mat4Test::suite());
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

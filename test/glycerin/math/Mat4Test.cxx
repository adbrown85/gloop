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

        double arr[4][4] = {
            {4.0, 4.0, 8.0, 7.0},
            {3.0, 2.0, 4.0, 6.0},
            {1.0, 6.0, 4.0, 5.0},
            {1.0, 2.0, 3.0, 4.0} };

        m1 = Mat4(arr);
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
     * Ensures the inverse function works correctly.
     */
    void testInverse() {

        m2 = inverse(m1);
        m3 = m1 * m2;

        for (int i = 0; i < 4; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m3(i,i), TOLERANCE);
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3(i,j), TOLERANCE);
            }
        }

        for (int i = 1; i < 4; ++i) {
            for (int j = 0; j<i; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3(i,j), TOLERANCE);
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
        m2 = Mat4(arr);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                CPPUNIT_ASSERT_EQUAL(arr[i*4+j], m2(i,j));
            }
        }
    }

    /**
     * Ensures transposing a matrix works correctly.
     */
    void testTranspose() {

        // Make the matrix
        double arr[4][4] = {
            {4.0, 3.0, 1.0, 1.0},
            {4.0, 2.0, 6.0, 2.0},
            {8.0, 4.0, 4.0, 3.0},
            {7.0, 6.0, 5.0, 4.0}};
        m2 = Mat4(arr);

        // Transpose it and compare
        m3 = transpose(m1);
        for (int i=0; i<4; ++i) {
            for (int j=0; j<4; ++j) {
                CPPUNIT_ASSERT(m2(i,j) == m3(i,j));
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
                CPPUNIT_ASSERT_DOUBLES_EQUAL(m1(i,j), m3(i,j), TOLERANCE);
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
    CPPUNIT_TEST(testInverse);
    CPPUNIT_TEST(testSetArray);
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

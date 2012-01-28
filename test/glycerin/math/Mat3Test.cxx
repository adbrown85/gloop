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

        double arr[3][3] = {
            {1.0, 6.0, 5.0},
            {7.0, 2.0, 8.0},
            {4.0, 9.0, 3.0} };

        m1 = Mat3(arr);
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
     * Ensures the inverse function works correctly.
     */
    void testInverse() {

        m2 = inverse(m1);
        m3 = m1 * m2;

        for (int i = 0; i < Mat3::ORDER; ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m3(i,i), TOLERANCE);
        }

        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = i + 1; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3(i,j), TOLERANCE);
            }
        }

        for (int i = 1; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < i; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m3(i,j), TOLERANCE);
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
        m2 = Mat3(arr);

        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(arr[i * Mat3::ORDER + j], m2(i, j), TOLERANCE);
            }
        }
    }

    /**
     * Ensures transposing a matrix works correctly.
     */
    void testTranspose() {
        m2 = transpose(m1);
        for (int i = 0; i < Mat3::ORDER; ++i) {
            for (int j = 0; j < Mat3::ORDER; ++j) {
                CPPUNIT_ASSERT_DOUBLES_EQUAL(m1(j,i), m2(i,j), TOLERANCE);
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
                CPPUNIT_ASSERT_DOUBLES_EQUAL(m1(i,j), m3(i,j), TOLERANCE);
            }
        }
    }

    /**
     * Ensures multiplying a vector by a matrix works correctly.
     */
    void testMultiplyVector() {
        double arr[3][3] = {
            {1.0, 6.0, 5.0},
            {7.0, 2.0, 8.0},
            {4.0, 9.0, 3.0} };

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

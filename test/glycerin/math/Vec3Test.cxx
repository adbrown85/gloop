/*
 * Vec3Test.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/common.h"
#include "glycerin/math/Math.hpp"
#include "glycerin/math/Vec3.hpp"
using namespace std;
namespace Glycerin {

const double COS_FORTY_FIVE = cos(toRadians(45));
const double SIN_FORTY_FIVE = sin(toRadians(45));

/**
 * Unit test for Vec3.
 */
class Vec3Test : public CppUnit::TestFixture {
public:

    /**
     * Ensures operator[] const works correctly.
     */
    void testOperatorIndexConst() {

        Vec3 u(1, 2, 3);

        CPPUNIT_ASSERT_EQUAL(1.0, u[0]);
        CPPUNIT_ASSERT_EQUAL(2.0, u[1]);
        CPPUNIT_ASSERT_EQUAL(3.0, u[2]);
    }

    /**
     * Ensures toArray works correctly.
     */
    void testToArray() {

        Vec3 u(1, 2, 3);
        double arr[3];

        u.toArray(arr);
        CPPUNIT_ASSERT_EQUAL(1.0, arr[0]);
        CPPUNIT_ASSERT_EQUAL(2.0, arr[1]);
        CPPUNIT_ASSERT_EQUAL(3.0, arr[2]);
    }

    /**
     * Ensures operator== returns true when it should.
     */
    void testOperatorEqualsWithTrue() {

        Vec3 u(1, 2, 3);
        Vec3 v(1, 2, 3);

        CPPUNIT_ASSERT_EQUAL(true, u == v);
    }

    /**
     * Ensures operator== returns false when it should.
     */
    void testOperatorEqualsWithFalse() {
        Vec3 u(1, 2, 3);
        Vec3 v(4, 5, 6);

        CPPUNIT_ASSERT_EQUAL(u == v, false);
    }

    /**
     * Ensures operator!= returns true when it should.
     */
    void testOperatorNotEqualsWithTrue() {

        Vec3 u(1, 1, 1);
        Vec3 v(1, 1, 2);

        CPPUNIT_ASSERT_EQUAL(true, u != v);
    }

    /**
     * Ensures operator!= returns false when it should
     */
    void testOperatorNotEqualsWithFalse() {
        Vec3 u(1, 1, 1);
        Vec3 v(1, 1, 1);

        CPPUNIT_ASSERT_EQUAL(u != v, false);
    }

    /**
     * Ensures operator+(Vec3,Vec3) works correctly.
     */
    void testOperatorAddVec3Vec3() {
        Vec3 u(1, 2, 3);
        Vec3 v(4, 5, 6);
        Vec3 r = u + v;

        CPPUNIT_ASSERT_EQUAL(5.0, r.x);
        CPPUNIT_ASSERT_EQUAL(7.0, r.y);
        CPPUNIT_ASSERT_EQUAL(9.0, r.z);
    }

    /**
     * Ensures operator-(Vec3,Vec3) works correctly.
     */
    void testOperatorSubtractVec3Vec3() {

        Vec3 u(1, 2, 3);
        Vec3 v(6, 5, 4);
        Vec3 r = u - v;

        CPPUNIT_ASSERT_EQUAL(-5.0, r.x);
        CPPUNIT_ASSERT_EQUAL(-3.0, r.y);
        CPPUNIT_ASSERT_EQUAL(-1.0, r.z);
    }

    /**
     * Ensures operator*(Vec3,Vec3) works correctly.
     */
    void testOperatorMultiplyVec3Vec3() {

        Vec3 u(1, 2, 3);
        Vec3 v(4, 5, 6);
        Vec3 r = u * v;

        CPPUNIT_ASSERT_EQUAL( 4.0, r.x);
        CPPUNIT_ASSERT_EQUAL(10.0, r.y);
        CPPUNIT_ASSERT_EQUAL(18.0, r.z);
    }

    /**
     * Ensures operator/(Vec3,Vec3) works correctly.
     */
    void testOperatorDivideVec3Vec3() {

        Vec3 u(1, 2, 3);
        Vec3 v(4, 5, 6);
        Vec3 r = u / v;

        CPPUNIT_ASSERT_EQUAL(0.25, r.x);
        CPPUNIT_ASSERT_EQUAL(0.40, r.y);
        CPPUNIT_ASSERT_EQUAL(0.50, r.z);
    }

    /**
     * Ensures operator+(Vec3,double) works correctly.
     */
    void testOperatorAddVec3Float() {

        Vec3 u(1, 2, 3);
        Vec3 r = u + 4;

        CPPUNIT_ASSERT_EQUAL(5.0, r.x);
        CPPUNIT_ASSERT_EQUAL(6.0, r.y);
        CPPUNIT_ASSERT_EQUAL(7.0, r.z);
    }

    /**
     * Ensures operator-(Vec3,double) works correctly.
     */
    void testOperatorSubtractVec3Float() {

        Vec3 u(1, 2, 3);
        Vec3 r = u - 4;

        CPPUNIT_ASSERT_EQUAL(-3.0, r.x);
        CPPUNIT_ASSERT_EQUAL(-2.0, r.y);
        CPPUNIT_ASSERT_EQUAL(-1.0, r.z);
    }

    /**
     * Ensures operator*(Vec3,double) works correctly.
     */
    void testOperatorMultiplyVec3Float() {

        Vec3 u(1, 2, 3);
        Vec3 r = u * 4;

        CPPUNIT_ASSERT_EQUAL( 4.0, r.x);
        CPPUNIT_ASSERT_EQUAL( 8.0, r.y);
        CPPUNIT_ASSERT_EQUAL(12.0, r.z);
    }

    /**
     * Ensures operator/(Vec3,double) works correctly.
     */
    void testOperatorDivideVec3Float() {

        Vec3 u(1, 2, 3);
        Vec3 r = u / 4;

        CPPUNIT_ASSERT_EQUAL(0.25, r.x);
        CPPUNIT_ASSERT_EQUAL(0.50, r.y);
        CPPUNIT_ASSERT_EQUAL(0.75, r.z);
    }

    /**
     * Ensures cross works correctly with the X and Y axes.
     */
    void testCrossWithXY() {

        Vec3 u(1, 0, 0);
        Vec3 v(0, 1, 0);
        Vec3 r = cross(u, v);

        CPPUNIT_ASSERT_EQUAL(0.0, r.x);
        CPPUNIT_ASSERT_EQUAL(0.0, r.y);
        CPPUNIT_ASSERT_EQUAL(1.0, r.z);
    }

    /**
     * Ensures cross works correctly with the Y and X axes.
     */
    void testCrossWithYX() {

        Vec3 u(0, 1, 0);
        Vec3 v(1, 0, 0);
        Vec3 r = cross(u, v);

        CPPUNIT_ASSERT_EQUAL( 0.0, r.x);
        CPPUNIT_ASSERT_EQUAL( 0.0, r.y);
        CPPUNIT_ASSERT_EQUAL(-1.0, r.z);
    }

    /**
     * Ensures dot works correctly with the X and Y axes.
     */
    void testDotWithXY() {
        Vec3 u(1, 0, 0);
        Vec3 v(0, 1, 0);
        double r = dot(u, v);

        CPPUNIT_ASSERT_EQUAL(0.0, r);
    }

    /**
     * Ensures dot works correctly with the Y axis.
     */
    void testDotWithYY() {

        Vec3 u(0, 1, 0);
        Vec3 v(0, 1, 0);
        double r = dot(u, v);

        CPPUNIT_ASSERT_EQUAL(1.0, r);
    }

    /**
     * Ensures length works correctly.
     */
    void testLength() {

        Vec3 u(5, 5, 0);
        double r = length(u);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(5 * SQRT_TWO, r, 0.01);
    }

    /**
     * Ensures normalize works correctly.
     */
    void testNormalize() {

        Vec3 u(5, 5, 0);
        Vec3 r = normalize(u);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(COS_FORTY_FIVE, r.x, 0.01);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(SIN_FORTY_FIVE, r.y, 0.01);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00, r.z, 0.01);
    }

    /**
     * Ensures min works correctly.
     */
    void testMin() {

        Vec3 u(1, 5, 3);
        Vec3 v(4, 2, 6);
        Vec3 r = min(u, v);

        CPPUNIT_ASSERT_EQUAL(1.0, r.x);
        CPPUNIT_ASSERT_EQUAL(2.0, r.y);
        CPPUNIT_ASSERT_EQUAL(3.0, r.z);
    }

    /**
     * Ensures max works correctly.
     */
    void testMax() {

        Vec3 u(1, 5, 3);
        Vec3 v(4, 2, 6);
        Vec3 r = max(u, v);

        CPPUNIT_ASSERT_EQUAL(4.0, r.x);
        CPPUNIT_ASSERT_EQUAL(5.0, r.y);
        CPPUNIT_ASSERT_EQUAL(6.0, r.z);
    }

    CPPUNIT_TEST_SUITE(Vec3Test);
    CPPUNIT_TEST(testOperatorIndexConst);
    CPPUNIT_TEST(testToArray);
    CPPUNIT_TEST(testOperatorEqualsWithTrue);
    CPPUNIT_TEST(testOperatorEqualsWithFalse);
    CPPUNIT_TEST(testOperatorNotEqualsWithTrue);
    CPPUNIT_TEST(testOperatorNotEqualsWithFalse);
    CPPUNIT_TEST(testOperatorAddVec3Vec3);
    CPPUNIT_TEST(testOperatorSubtractVec3Vec3);
    CPPUNIT_TEST(testOperatorMultiplyVec3Vec3);
    CPPUNIT_TEST(testOperatorDivideVec3Vec3);
    CPPUNIT_TEST(testOperatorAddVec3Float);
    CPPUNIT_TEST(testOperatorSubtractVec3Float);
    CPPUNIT_TEST(testOperatorMultiplyVec3Float);
    CPPUNIT_TEST(testOperatorDivideVec3Float);
    CPPUNIT_TEST(testCrossWithXY);
    CPPUNIT_TEST(testCrossWithYX);
    CPPUNIT_TEST(testDotWithXY);
    CPPUNIT_TEST(testDotWithYY);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testNormalize);
    CPPUNIT_TEST(testMin);
    CPPUNIT_TEST(testMax);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char *argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::Vec3Test::suite());
    runner.run();
    return 0;
}

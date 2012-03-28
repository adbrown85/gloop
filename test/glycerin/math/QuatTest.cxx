/*
 * QuatTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/common.h"
#include "glycerin/math/Math.hpp"
#include "glycerin/math/Quat.hpp"
using namespace std;
namespace Glycerin {

/*
 * Constants
 */
const float ANGLE_30 = toRadians(30);
const float ANGLE_45 = toRadians(45);
const float TOLERANCE = 1e-3;
const float NOT_A_NUMBER = sqrt(-1);

/**
 * Unit test for Quat.
 */
class QuatTest : public CppUnit::TestFixture {
private:

    /**
     * Makes a matrix representing a rotation around the X axis.
     *
     * <pre>
     * | 1    0       0    |
     * | 0  cos(t) -sin(t) |
     * | 0  sin(t)  cos(t) |
     * </pre>
     */
    static Mat3 createRotationMatrixX(const double t) {

        // Calculate sin and cosine
        const double sin_t = sin(t);
        const double cos_t = cos(t);

        // Make array
        double a[3][3];
        a[0][0] = 1; a[0][1] = 0;     a[0][2] = 0;
        a[1][0] = 0; a[1][1] = cos_t; a[1][2] = -sin_t;
        a[2][0] = 0; a[2][1] = sin_t; a[2][2] = cos_t;

        // Make matrix
        return Mat3::fromArrayInColumnMajor(a);
    }

    /**
     * Makes a matrix representing a rotation around the Y axis.
     *
     * |  cos(t) 0  sin(t) |
     * |    0    1    0    |
     * | -sin(t) 0  cos(t) |
     */
    static Mat3 createRotationMatrixY(const double t) {

        // Calculate sin and cosine
        const double sin_t = sin(t);
        const double cos_t = cos(t);

        // Make array
        double a[3][3];
        a[0][0] = cos_t;  a[0][1] = 0; a[0][2] = sin_t;
        a[1][0] = 0;      a[1][1] = 1; a[1][2] = 0;
        a[2][0] = -sin_t; a[2][1] = 0; a[2][2] = cos_t;

        // Make matrix
        return Mat3::fromArrayInColumnMajor(a);
    }

    /**
     * Makes a matrix representing a rotation around the Z axis.
     *
     * | cos(t) -sin(t) 0 |
     * | sin(t)  cos(t) 0 |
     * |   0       0    1 |
     */
    static Mat3 createRotationMatrixZ(const double t) {

        // Calculate sin and cosine
        const double sin_t = sin(t);
        const double cos_t = cos(t);

        // Make array
        double a[3][3];
        a[0][0] = cos_t; a[0][1] = -sin_t; a[0][2] = 0;
        a[1][0] = sin_t; a[1][1] =  cos_t; a[1][2] = 0;
        a[2][0] =     0; a[2][1] =      0; a[2][2] = 1;

        // Make matrix
        return Mat3::fromArrayInColumnMajor(a);
    }

public:

    /**
     * Ensures the default constructor makes a quaternion with all zeros.
     */
    void testDefaultConstructor() {
        Quat q;
        CPPUNIT_ASSERT(q.x == 0.0);
        CPPUNIT_ASSERT(q.y == 0.0);
        CPPUNIT_ASSERT(q.z == 0.0);
        CPPUNIT_ASSERT(q.w == 0.0);
    }

    /**
     * Ensures the constructor taking explicit values works correctly.
     */
    void testConstructorWithExplicitValues() {
        Quat q(1, 2, 3, 4);
        CPPUNIT_ASSERT_EQUAL(1, (int) q.x);
        CPPUNIT_ASSERT_EQUAL(2, (int) q.y);
        CPPUNIT_ASSERT_EQUAL(3, (int) q.z);
        CPPUNIT_ASSERT_EQUAL(4, (int) q.w);
    }

    /**
     * Ensures fromMat3 works correctly with the identity matrix.
     */
    void testFromMat3WithIdentity() {
        const Mat3 m(1);
        const Quat q = Quat::fromMat3(m);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, q.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, q.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, q.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, q.w, TOLERANCE);
    }

    /**
     * Ensures fromMat3 works with a rotation around the X axis.
     */
    void testFromMat3WithRotationX() {

        // Make expected quaternion
        const Vec3 axis(1, 0, 0);
        const double angle = ANGLE_30;
        const Quat expect = Quat::fromAxisAngle(axis, angle);

        // Make input matrix
        const Mat3 m = createRotationMatrixX(angle);
        const Quat result = Quat::fromMat3(m);

        // Compare
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.x, result.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.y, result.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.z, result.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.w, result.w, TOLERANCE);
    }

    /**
     * Ensures fromMat3 works with a rotation around the X axis.
     */
    void testFromMat3WithRotationY() {

        // Make expected quaternion
        const Vec3 axis(0, 1, 0);
        const double angle = ANGLE_30;
        const Quat expect = Quat::fromAxisAngle(axis, angle);

        // Make input matrix
        const Mat3 m = createRotationMatrixY(angle);
        const Quat result = Quat::fromMat3(m);

        // Compare
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.x, result.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.y, result.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.z, result.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.w, result.w, TOLERANCE);
    }

    /**
     * Ensures fromMat3 works with a rotation around the Z axis.
     */
    void testFromMat3WithRotationZ() {

        // Make expected quaternion
        const Vec3 axis(0, 0, 1);
        const double angle = ANGLE_30;
        const Quat expect = Quat::fromAxisAngle(axis, angle);

        // Make input matrix
        const Mat3 m = createRotationMatrixZ(angle);
        const Quat result = Quat::fromMat3(m);

        // Compare
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.x, result.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.y, result.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.z, result.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.w, result.w, TOLERANCE);
    }

    /**
     * Ensures fromMat3 works with a 180 degree rotation.
     */
    void testFromMat3WithOneEightyDegreeRotation() {

        // Make expected quaternion
        const Vec3 axis(0, 1, 0);
        const double angle = toRadians(180);
        const Quat expect = Quat::fromAxisAngle(axis, angle);

        // Make result quaternion
        const Mat3 m = createRotationMatrixY(angle);
        const Quat result = Quat::fromMat3(m);

        // Compare
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.x, result.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.y, result.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.z, result.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expect.w, result.w, TOLERANCE);
    }

    /**
     * Ensures the named constructor creating the identity quaternion works correctly.
     */
    void testIdentity() {
        Quat q = Quat::identity();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, q.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, q.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, q.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, q.w, TOLERANCE);
    }

    /**
     * Ensures isIdentity works correctly with the identity quaternion.
     */
    void testIsIdentityWithIdentity() {
        Quat q(0, 0, 0, 1);
        CPPUNIT_ASSERT(q.isIdentity());
    }

    /**
     * Ensures isIdentity works correctly with an incorrect x component.
     */
    void testIsIdentityWithIncorrectX() {
        Quat q(-1, 0, 0, 1);
        CPPUNIT_ASSERT(!q.isIdentity());
    }

    /**
     * Ensures isIdentity works correctly with an incorrect y component.
     */
    void testIsIdentityWithIncorrectY() {
        Quat q(0, -1, 0, 1);
        CPPUNIT_ASSERT(!q.isIdentity());
    }

    /**
     * Ensures isIdentity works correctly with an incorrect z component.
     */
    void testIsIdentityWithIncorrectZ() {
        Quat q(0, 0, -1, 1);
        CPPUNIT_ASSERT(!q.isIdentity());
    }

    /**
     * Ensures isIdentity works correctly with an incorrect w component.
     */
    void testIsIdentityWithIncorrectW() {
        Quat q(0, 0, 0, -1);
        CPPUNIT_ASSERT(!q.isIdentity());
    }

    /**
     * Ensures isInfinite works correctly when its x component is infinite.
     */
    void testIsInfiniteWithInfiniteX() {
        Quat q;
        q.x = +numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
        q.x = -numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
    }

    /**
     * Ensures isInfinite works correctly when its y component is infinite.
     */
    void testIsInfiniteWithInfiniteY() {
        Quat q;
        q.y = +numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
        q.y = -numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
    }

    /**
     * Ensures isInfinite works correctly when its z component is infinite.
     */
    void testIsInfiniteWithInfiniteZ() {
        Quat q;
        q.z = +numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
        q.z = -numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
    }

    /**
     * Ensures isInfinite works correctly when its w component is infinite.
     */
    void testIsInfiniteWithInfiniteW() {
        Quat q;
        q.w = +numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
        q.w = -numeric_limits<double>::infinity();
        CPPUNIT_ASSERT(q.isInfinite());
    }

    /**
     * Ensures isInfinite works correctly with finite components.
     */
    void testIsInfiniteWithFinite() {
        Quat q;
        CPPUNIT_ASSERT(!q.isInfinite());
    }

    /**
     * Ensures isNaN works correctly when its x component is NaN.
     */
    void testIsNanWithNanX() {
        Quat q;
        q.x = NOT_A_NUMBER;
        CPPUNIT_ASSERT(q.isNaN());
    }

    /**
     * Ensures isNaN works correctly when its x component is NaN.
     */
    void testIsNanWithNanY() {
        Quat q;
        q.y = NOT_A_NUMBER;
        CPPUNIT_ASSERT(q.isNaN());
    }

    /**
     * Ensures isNaN works correctly when its x component is NaN.
     */
    void testIsNanWithNanZ() {
        Quat q;
        q.z = NOT_A_NUMBER;
        CPPUNIT_ASSERT(q.isNaN());
    }

    /**
     * Ensures isNaN works correctly when its w components is NaN.
     */
    void testIsNanWithNanW() {
        Quat q;
        q.w = NOT_A_NUMBER;
        CPPUNIT_ASSERT(q.isNaN());
    }

    /**
     * Ensures isNaN worls correctly when none of its components is NaN.
     */
    void testIsNanWithoutNan() {
        Quat q;
        CPPUNIT_ASSERT(!q.isNaN());
    }

    /**
     * Ensure the equals operator works correctly with two equal quaternions.
     */
    void testOperatorEqualsWithEqual() {
        const Quat q1 = Quat(1, 2, 3, 4);
        const Quat q2 = Quat(1, 2, 3, 4);
        CPPUNIT_ASSERT(q1 == q2);
    }

    /**
     * Ensures the equals operator works with two unequal quaternions.
     */
    void testOperatorEqualsWithUnequal() {
        const Quat q1 = Quat(1, 2, 3, 4);
        const Quat q2 = Quat(4, 3, 2, 1);
        CPPUNIT_ASSERT(!(q1 == q2));
    }

    /**
     * Ensures the not-equal operator works with equal quaternions.
     */
    void testOperatorNotEqualWithEqual() {
        const Quat q1(1, 2, 3, 4);
        const Quat q2(1, 2, 3, 4);
        CPPUNIT_ASSERT(!(q1 != q2));
    }

    /**
     * Ensures the not-equal operator works with unequal quaternions.
     */
    void testOperatorNotEqualWithUnequal() {
        const Quat q1(1, 2, 3, 4);
        const Quat q2(4, 3, 2, 1);
        CPPUNIT_ASSERT(q1 != q2);
    }

    /**
     * Ensures the subscript operator works correctly.
     */
    void testOperatorSubscript() {
        Quat q;
        q[0] = 1;
        q[1] = 2;
        q[2] = 3;
        q[3] = 4;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, q[0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, q[1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, q[2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0, q[3], TOLERANCE);
        CPPUNIT_ASSERT_THROW(q[-1], out_of_range);
        CPPUNIT_ASSERT_THROW(q[4], out_of_range);
    }

    /**
     * Ensures the const subscript operator works correctly.
     */
    void testOperatorSubscriptConst() {
        const Quat q(1, 2, 3, 4);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, q[0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, q[1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, q[2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0, q[3], TOLERANCE);
        CPPUNIT_ASSERT_THROW(q[-1], out_of_range);
        CPPUNIT_ASSERT_THROW(q[4], out_of_range);
    }

    /**
     * Ensures the unary plus operator works properly.
     */
    void testOperatorUnaryPlus() {

        // Make quaternion
        const Quat q1(1, 2, 3, 4);
        const Quat q2 = +q1;

        // Compare results
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, q2.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2, q2.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3, q2.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4, q2.w, TOLERANCE);
    }

    /**
     * Ensures the unary minus operator works properly.
     */
    void testOperatorUnaryMinus() {

        // Make quaternion and negate it
        const Quat q1(1, 2, 3, 4);
        const Quat q2 = -q1;

        // Compare results
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, q2.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-2, q2.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-3, q2.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-4, q2.w, TOLERANCE);
    }

    /**
     * Ensures the addition operator works correctly.
     */
    void testOperatorAdd() {

        // Add the quaternions
        const Quat q1(1, 2, 3, 4);
        const Quat q2(11, 22, 33, 44);
        const Quat q3 = q1 + q2;

        // Compare results
        CPPUNIT_ASSERT_DOUBLES_EQUAL(12, q3.x, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(24, q3.y, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(36, q3.z, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(48, q3.w, TOLERANCE);
    }

    /**
     * Ensures the subtraction operator works correctly.
     */
    void testOperatorSubtract() {

        // Do subtraction
        const Quat q1(1, 2, 3, 4);
        const Quat q2(11, 22, 33, 44);
        const Quat q3 = q1 - q2;

        // Compare results
        CPPUNIT_ASSERT_EQUAL(-10.0, q3.x);
        CPPUNIT_ASSERT_EQUAL(-20.0, q3.y);
        CPPUNIT_ASSERT_EQUAL(-30.0, q3.z);
        CPPUNIT_ASSERT_EQUAL(-40.0, q3.w);
    }

    /**
     * Ensures conversion to a 3x3 matrix works correctly.
     */
    void testToMat3() {

        const Quat q = Quat::fromAxisAngle(Vec3(0,1,0), ANGLE_45);
        const Mat3 mat = q.toMat3();

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.707, mat[0][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[1][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.707, mat[2][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[0][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.000, mat[1][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[2][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.707, mat[0][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[1][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.707, mat[2][2], TOLERANCE);
    }

    /**
     * Ensures quaternion can be multiplied correctly.
     */
    void testMultiply() {

        const Quat q1 = Quat::fromAxisAngle(Vec3(0,1,0), ANGLE_30);
        const Quat q2 = Quat::fromAxisAngle(Vec3(0,1,0), ANGLE_45);
        const Quat q3 = q2 * q1;
        const Mat3 mat = q3.toMat3();

        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.259, mat[0][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[1][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.966, mat[2][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[0][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.000, mat[1][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[2][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.966, mat[0][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000, mat[1][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.259, mat[2][2], TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(QuatTest);
    CPPUNIT_TEST(testDefaultConstructor);
    CPPUNIT_TEST(testConstructorWithExplicitValues);
    CPPUNIT_TEST(testFromMat3WithIdentity);
    CPPUNIT_TEST(testFromMat3WithRotationX);
    CPPUNIT_TEST(testFromMat3WithRotationY);
    CPPUNIT_TEST(testFromMat3WithRotationZ);
    CPPUNIT_TEST(testFromMat3WithOneEightyDegreeRotation);
    CPPUNIT_TEST(testIdentity);
    CPPUNIT_TEST(testIsIdentityWithIdentity);
    CPPUNIT_TEST(testIsIdentityWithIncorrectX);
    CPPUNIT_TEST(testIsIdentityWithIncorrectY);
    CPPUNIT_TEST(testIsIdentityWithIncorrectZ);
    CPPUNIT_TEST(testIsIdentityWithIncorrectW);
    CPPUNIT_TEST(testIsInfiniteWithInfiniteX);
    CPPUNIT_TEST(testIsInfiniteWithInfiniteY);
    CPPUNIT_TEST(testIsInfiniteWithInfiniteZ);
    CPPUNIT_TEST(testIsInfiniteWithInfiniteW);
    CPPUNIT_TEST(testIsInfiniteWithFinite);
    CPPUNIT_TEST(testIsNanWithNanX);
    CPPUNIT_TEST(testIsNanWithNanY);
    CPPUNIT_TEST(testIsNanWithNanZ);
    CPPUNIT_TEST(testIsNanWithNanW);
    CPPUNIT_TEST(testIsNanWithoutNan);
    CPPUNIT_TEST(testOperatorUnaryPlus);
    CPPUNIT_TEST(testOperatorUnaryMinus);
    CPPUNIT_TEST(testOperatorEqualsWithEqual);
    CPPUNIT_TEST(testOperatorEqualsWithUnequal);
    CPPUNIT_TEST(testOperatorNotEqualWithEqual);
    CPPUNIT_TEST(testOperatorNotEqualWithUnequal);
    CPPUNIT_TEST(testOperatorSubscript);
    CPPUNIT_TEST(testOperatorSubscriptConst);
    CPPUNIT_TEST(testOperatorAdd);
    CPPUNIT_TEST(testOperatorSubtract);
    CPPUNIT_TEST(testToMat3);
    CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char *argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::QuatTest::suite());
    runner.run();
    return 0;
}

/*
 * Vec4Test.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <limits>
#include "glycerin/common.h"
#include "glycerin/math/Vec4.hpp"
using namespace std;
namespace Glycerin {


/**
 * Unit test for Vec4.
 */
class Vec4Test : public CppUnit::TestFixture {
public:

    /**
     * Ensures add operation works correctly.
     */
    void testAdd() {
        Vec4 A(2, 2, 2, 0);
        Vec4 B(2, 4, 5, 0);
        Vec4 C = A + B;
        CPPUNIT_ASSERT_EQUAL(4.0, C.x);
        CPPUNIT_ASSERT_EQUAL(6.0, C.y);
        CPPUNIT_ASSERT_EQUAL(7.0, C.z);
        CPPUNIT_ASSERT_EQUAL(0.0, C.w);
    }

    /**
     * Ensures subtract operation works correctly.
     */
    void testSubtract() {
        Vec4 A(2, 2, 2, 0);
        Vec4 B(2, 4, 5, 0);
        Vec4 C = A - B;
        CPPUNIT_ASSERT_EQUAL( 0.0, C.x);
        CPPUNIT_ASSERT_EQUAL(-2.0, C.y);
        CPPUNIT_ASSERT_EQUAL(-3.0, C.z);
        CPPUNIT_ASSERT_EQUAL( 0.0, C.w);
    }

    /**
     * Ensures multiply operation works correctly.
     */
    void testMultiply() {
        Vec4 A(2, 2, 2, 0);
        Vec4 B(2, 4, 5, 0);
        Vec4 C = A * B;
        CPPUNIT_ASSERT_EQUAL( 4.0, C.x);
        CPPUNIT_ASSERT_EQUAL( 8.0, C.y);
        CPPUNIT_ASSERT_EQUAL(10.0, C.z);
        CPPUNIT_ASSERT_EQUAL( 0.0, C.w);
    }

    /**
     * Ensures divide operation works correctly.
     */
    void testDivide() {
        Vec4 A(2, 2, 2, 0);
        Vec4 B(2, 4, 5, 0);
        Vec4 C = A / B;
        CPPUNIT_ASSERT_EQUAL(1.0, C.x);
        CPPUNIT_ASSERT_EQUAL(0.5, C.y);
        CPPUNIT_ASSERT_EQUAL(0.4, C.z);
        CPPUNIT_ASSERT(C.w != C.w);
    }

    CPPUNIT_TEST_SUITE(Vec4Test);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testSubtract);
    CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST(testDivide);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char *argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::Vec4Test::suite());
    runner.run();
    return 0;
}

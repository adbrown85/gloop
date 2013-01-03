#include "config.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <gloop/VertexAttribPointer.hxx>
namespace Gloop {


/**
 * Unit test for `VertexAttribPointer`.
 */
class VertexAttribPointerTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures that `index(GLuint)` sets `_index` properly.
     */
    void testIndex() {
        VertexAttribPointer vap;
        vap.index(12);
        CPPUNIT_ASSERT_EQUAL((GLuint) 12, vap._index);
    }

    /**
     * Ensures that `normalized(GLboolean)` sets `_normalized` properly.
     */
    void testNormalized() {
        VertexAttribPointer vap;
        vap.normalized(GL_TRUE);
        CPPUNIT_ASSERT_EQUAL((GLboolean) GL_TRUE, vap._normalized);
    }

    /**
     * Ensures that `offset(GLsizei)` sets `_offset` properly.
     */
    void testOffset() {
        VertexAttribPointer vap;
        vap.offset(12);
        CPPUNIT_ASSERT_EQUAL((GLsizei) 12, vap._offset);
    }

    /**
     * Ensures that `size(GLint)` sets `_size` properly.
     */
    void testSize() {
        VertexAttribPointer vap;
        vap.size(3);
        CPPUNIT_ASSERT_EQUAL((GLint) 3, vap._size);
    }

    /**
     * Ensures that `stride(GLsizei)` sets `_stride` properly.
     */
    void testStride() {
        VertexAttribPointer vap;
        vap.stride(12);
        CPPUNIT_ASSERT_EQUAL((GLsizei) 12, vap._stride);
    }

    /**
     * Ensures that `type(GLenum)` sets `_type` properly.
     */
    void testType() {
        VertexAttribPointer vap;
        vap.type(GL_INT);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_INT, vap._type);
    }

    /**
     * Ensures that `VertexAttribPointer()` initializes all fields to their default values.
     */
    void testVertexAttribPointer() {
        const VertexAttribPointer vap;
        CPPUNIT_ASSERT_EQUAL((GLuint) 0, vap._index);
        CPPUNIT_ASSERT_EQUAL(0, vap._offset);
        CPPUNIT_ASSERT_EQUAL(4, vap._size);
        CPPUNIT_ASSERT_EQUAL((GLboolean) GL_FALSE, vap._normalized);
        CPPUNIT_ASSERT_EQUAL(0, vap._stride);
    }

    CPPUNIT_TEST_SUITE(VertexAttribPointerTest);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testNormalized);
    CPPUNIT_TEST(testOffset);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testStride);
    CPPUNIT_TEST(testType);
    CPPUNIT_TEST(testVertexAttribPointer);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Gloop */

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Gloop::VertexAttribPointerTest::suite());
    runner.run();
    return 0;
}

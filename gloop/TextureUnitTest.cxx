/*
 * Copyright (c) 2012, Andrew Brown
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "config.h"
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include "gloop/TextureUnit.hxx"
using namespace std;
using namespace Gloop;


/**
 * Unit test for TextureUnit.
 */
class TextureUnitTest {
public:

    /**
     * Ensures TextureUnit::activate() works correctly.
     */
    void testActivate() {

        // Activate the second texture unit
        const TextureUnit unit = TextureUnit::fromEnum(GL_TEXTURE1);
        unit.activate();

        // Check that it's active
        GLint active;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &active);
        CPPUNIT_ASSERT_EQUAL((GLenum) active, unit.toEnum());

        // Reset it
        glActiveTexture(GL_TEXTURE0);
    }

    /**
     * Ensures TextureUnit::active() returns the correct texture unit.
     */
    void testActive() {
        glActiveTexture(GL_TEXTURE1);
        const TextureUnit unit = TextureUnit::active();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE1, unit.toEnum());
        glActiveTexture(GL_TEXTURE0);
    }

    /**
     * Ensures a TextureUnit instance can be added to an STL map.
     */
    void testAddToStlMap() {
        map<string,TextureUnit> units;
        units.insert(pair<string,TextureUnit>("GL_TEXTURE0", TextureUnit::fromEnum(GL_TEXTURE0)));
        map<string,TextureUnit>::const_iterator it = units.find("GL_TEXTURE0");
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE0, it->second.toEnum());
    }

    /**
     * Ensures a TextureUnit instance can be added to an STL set.
     */
    void testAddToStlSet() {
        set<TextureUnit> units;
        units.insert(TextureUnit::fromEnum(GL_TEXTURE0));
        units.insert(TextureUnit::fromEnum(GL_TEXTURE1));
        CPPUNIT_ASSERT_EQUAL((size_t) 2, units.size());
    }

    /**
     * Ensures a TextureUnit instance can be added to an STL vector.
     */
    void testAddToStlVector() {
        vector<TextureUnit> units;
        units.push_back(TextureUnit::fromEnum(GL_TEXTURE0));
        CPPUNIT_ASSERT_EQUAL((size_t) 1, units.size());
    }

    /**
     * Ensures TextureUnit::operator=(TextureUnit) works correctly.
     */
    void testAssignmentOperator() {
        TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE1);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE2);
        TextureUnit* ptr = &(u1 = u2);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE2, u1.toEnum());
        CPPUNIT_ASSERT_EQUAL(&u1, ptr);
    }

    /**
     * Ensures TextureUnit::operator==(TextureUnit) returns `true` for equal instances.
     */
    void testEqualityOperatorWithEqual() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE0);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE0);
        CPPUNIT_ASSERT(u1 == u2);
    }

    /**
     * Ensures TextureUnit::operator==(TextureUnit) returns `false` for unequal instances.
     */
    void testEqualityOperatorWithUnequal() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE0);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE1);
        CPPUNIT_ASSERT(!(u1 == u2));
    }

    /**
     * Ensures TextureUnit::fromOrdinal(GLint) works with `1`.
     */
    void testFromOrdinalWithOne() {
        const TextureUnit unit = TextureUnit::fromOrdinal(1);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE1, unit.toEnum());
    }

    /**
     * Ensures TextureUnit::fromOrdinal(GLint) works with `0`.
     */
    void testFromOrdinalWithZero() {
        const TextureUnit unit = TextureUnit::fromOrdinal(0);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE0, unit.toEnum());
    }

    /**
     * Ensures TextureUnit::operator!=(TextureUnit) returns `false` for equal instances.
     */
    void testInequalityOperatorWithEqual() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE0);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE0);
        CPPUNIT_ASSERT(!(u1 != u2));
    }

    /**
     * Ensures TextureUnit::operator!=(TextureUnit) returns `true` for unequal instances.
     */
    void testInequalityOperatorWithUnequal() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE0);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE1);
        CPPUNIT_ASSERT(u1 != u2);
    }

    /**
     * Ensures operator<<(ostream&, TextureUnit) works correctly.
     */
    void testInsertionOperator() {
        const TextureUnit unit = TextureUnit::fromEnum(GL_TEXTURE0);
        stringstream stream;
        stream << unit;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE0"), stream.str());
    }

    /**
     * Ensures TextureUnit::operator<(TextureUnit) returns `false` for equal instances.
     */
    void testLessThanOperatorWithEqual() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE0);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE0);
        CPPUNIT_ASSERT(!(u1 < u2));
    }

    /**
     * Ensures TextureUnit::operator<(TextureUnit) returns `true` for an instance that's greater.
     */
    void testLessThanOperatorWithGreater() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE0);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE1);
        CPPUNIT_ASSERT(u1 < u2);
    }

    /**
     * Ensures TextureUnit::operator<(TextureUnit) returns `false` for an instance that's less.
     */
    void testLessThanOperatorWithLess() {
        const TextureUnit u1 = TextureUnit::fromEnum(GL_TEXTURE1);
        const TextureUnit u2 = TextureUnit::fromEnum(GL_TEXTURE0);
        CPPUNIT_ASSERT(!(u1 < u2));
    }

    /**
     * Ensures TextureUnit::toOrdinal() returns `1` for `GL_TEXTURE1`.
     */
    void testToOrdinalWithOne() {
        const TextureUnit unit = TextureUnit::fromEnum(GL_TEXTURE1);
        CPPUNIT_ASSERT_EQUAL(1, unit.toOrdinal());
    }

    /**
     * Ensures TextureUnit::toOrdinal() returns `0` with `GL_TEXTURE0`.
     */
    void testToOrdinalWithZero() {
        const TextureUnit unit = TextureUnit::fromEnum(GL_TEXTURE0);
        CPPUNIT_ASSERT_EQUAL(0, unit.toOrdinal());
    }
};


int main(int argc, char* argv[]) {

    // Initialize
    if (!glfwInit()) {
        cerr << "Could not initialize GLFW!" << endl;
        return 1;
    }

    // Open a window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    // Run the test
    TextureUnitTest test;
    try {
        test.testActivate();
        test.testActive();
        test.testAddToStlMap();
        test.testAddToStlSet();
        test.testAddToStlVector();
        test.testAssignmentOperator();
        test.testEqualityOperatorWithEqual();
        test.testEqualityOperatorWithUnequal();
        test.testFromOrdinalWithOne();
        test.testFromOrdinalWithZero();
        test.testInequalityOperatorWithEqual();
        test.testInequalityOperatorWithUnequal();
        test.testInsertionOperator();
        test.testLessThanOperatorWithEqual();
        test.testLessThanOperatorWithGreater();
        test.testLessThanOperatorWithLess();
        test.testToOrdinalWithOne();
        test.testToOrdinalWithZero();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

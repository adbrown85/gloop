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
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <GL/glfw.h>
#include "gloop/TextureObject.hxx"
using namespace std;
using namespace Gloop;


/**
 * Unit test for TextureObject.
 */
class TextureObjectTest {
public:

    /**
     * Ensures a TextureObject can be added to an STL map.
     */
    void testAddToStlMap() {
        map<string,TextureObject> texturesByName;
        texturesByName.insert(pair<string,TextureObject>("foo", TextureObject::generate()));
    }

    /**
     * Ensures a TextureObject can be added to an STL set.
     */
    void testAddToStlSet() {
        set<TextureObject> textures;
        textures.insert(TextureObject::generate());
    }

    /**
     * Ensures a TextureObject can be added to an STL vector.
     */
    void testAddToStlVector() {
        vector<TextureObject> textures;
        textures.push_back(TextureObject::generate());
    }

    /**
     * Ensures TextureObject::operator=(TextureObject) works correctly.
     */
    void testAssignmentOperator() {
        TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(2);
        TextureObject* ptr = &(t1 = t2);
        CPPUNIT_ASSERT_EQUAL(t2.id(), t1.id());
        CPPUNIT_ASSERT_EQUAL(&t1, ptr);
    }

    /**
     * Ensures that TextureObject::dispose() deletes the underlying OpenGL texture object.
     */
    void testDispose() {
        const TextureObject to = TextureObject::generate();
        const GLuint id = to.id();
        glBindTexture(GL_TEXTURE_2D, id);
        CPPUNIT_ASSERT(glIsTexture(id));
        to.dispose();
        CPPUNIT_ASSERT(!glIsTexture(id));
    }

    /**
     * Ensures TextureObject::operator==(TextureObject) returns `true` with equal instances.
     */
    void testEqualityOperatorWithEqual() {
        const TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(1);
        CPPUNIT_ASSERT(t1 == t2);
    }

    /**
     * Ensures TextureObject::operator==(TextureObject) returns `false` with unequal instances.
     */
    void testEqualityOperatorWithUnequal() {
        const TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(2);
        CPPUNIT_ASSERT(!(t1 == t2));
    }

    /**
     * Ensures that the instance returned by TextureObject::fromId(GLuint) has the same ID that it was given.
     */
    void testFromId() {
        GLuint id;
        glGenTextures(1, &id);
        const TextureObject to = TextureObject::fromId(id);
        CPPUNIT_ASSERT_EQUAL(id, to.id());
    }

    /**
     * Ensures TextureObject::generate() returns a valid texture object.
     */
    void testGenerate() {
        const TextureObject to = TextureObject::generate();
        const GLuint id = to.id();
        CPPUNIT_ASSERT((id != 0) && (id != -1));
    }

    /**
     * Ensures TextureObject::operator!=(TextureObject) returns `false` with equal instances.
     */
    void testInequalityOperatorWithEqual() {
        const TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(1);
        CPPUNIT_ASSERT(!(t1 != t2));
    }

    /**
     * Ensures TextureObject::operator!=(TextureObject) returns `true` with unequal instances.
     */
    void testInequalityOperatorWithUnequal() {
        const TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(2);
        CPPUNIT_ASSERT(t1 != t2);
    }

    /**
     * Ensures TextureObject::operator<<(ostream, TextureObject) works correctly.
     */
    void testInsertionOperator() {
        const TextureObject to = TextureObject::fromId(37);
        stringstream stream;
        stream << to;
        CPPUNIT_ASSERT_EQUAL(string("37"), stream.str());
    }

    /**
     * Ensures TextureObject::operator<(TextureObject) returns `false` with an instance that is equal to it.
     */
    void testLessThanOperatorWithEqual() {
        const TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(1);
        CPPUNIT_ASSERT(!(t1 < t2));
    }

    /**
     * Ensures TextureObject::operator<(TextureObject) returns `true` with an instance that is greater than it.
     */
    void testLessThanOperatorWithGreater() {
        const TextureObject t1 = TextureObject::fromId(1);
        const TextureObject t2 = TextureObject::fromId(2);
        CPPUNIT_ASSERT(t1 < t2);
    }

    /**
     * Ensures TextureObject::operator<(TextureObject) returns `false` with an instance that is less than it.
     */
    void testLessThanOperatorWithLess() {
        const TextureObject t1 = TextureObject::fromId(2);
        const TextureObject t2 = TextureObject::fromId(1);
        CPPUNIT_ASSERT(!(t1 < t2));
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
    TextureObjectTest test;
    try {
        test.testAddToStlMap();
        test.testAddToStlSet();
        test.testAddToStlVector();
        test.testAssignmentOperator();
        test.testDispose();
        test.testEqualityOperatorWithEqual();
        test.testEqualityOperatorWithUnequal();
        test.testFromId();
        test.testGenerate();
        test.testInequalityOperatorWithEqual();
        test.testInequalityOperatorWithUnequal();
        test.testInsertionOperator();
        test.testLessThanOperatorWithEqual();
        test.testLessThanOperatorWithGreater();
        test.testLessThanOperatorWithLess();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

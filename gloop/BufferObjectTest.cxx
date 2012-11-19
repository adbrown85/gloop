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
#include <stdexcept>
#include "gloop/BufferObject.hxx"
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
using namespace std;
using namespace Gloop;


/**
 * Unit test for BufferObject.
 */
class BufferObjectTest {
public:

    /**
     * Ensures buffer object returned by generate is valid.
     */
    void testGenerate() {
        const BufferObject bo = BufferObject::generate();
        CPPUNIT_ASSERT(bo.id() > 0);
    }

    /**
     * Ensures wrapping a bad buffer object ID throws an exception.
     */
    void testFromIdWithBadId() {
        const GLuint id = -1;
        CPPUNIT_ASSERT_THROW(BufferObject::fromId(id), invalid_argument);
    }

    /**
     * Ensures wrapping a good buffer object ID does not throw an exception.
     */
    void testFromIdWithGoodId() {
        GLuint id;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        CPPUNIT_ASSERT(id > 0);
        const BufferObject bo = BufferObject::fromId(id);
        CPPUNIT_ASSERT_EQUAL(id, bo.id());
    }

    /**
     * Ensures a buffer object can be a key in an STL map.
     */
    void testAddToStlMap() {
        map<BufferObject,string> m;
        const BufferObject b1 = BufferObject::generate();
        const BufferObject b2 = BufferObject::generate();
        m[b1] = "foo";
        m[b2] = "bar";
    }

    /**
     * Ensures a buffer object can be added to an STL vector.
     */
    void testAddToStlVector() {
        vector<BufferObject> v;
        const BufferObject bo = BufferObject::generate();
        v.push_back(bo);
    }
};


int main(int argc, char* argv[]) {

    // Initialize GLFW
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
    BufferObjectTest test;
    try {
        test.testGenerate();
        test.testFromIdWithBadId();
        test.testFromIdWithGoodId();
        test.testAddToStlMap();
        test.testAddToStlVector();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

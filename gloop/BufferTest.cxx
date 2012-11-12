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
#include <cassert>
#include <stdexcept>
#include <GL/glfw.h>
#include "gloop/Buffer.hxx"
#include "gloop/BufferObject.hxx"
using namespace std;
using namespace Gloop;


/**
 * Unit test for Buffer.
 */
class BufferTest {
public:

    /**
     * Ensures a buffer object can be bound to the buffer target correctly.
     */
    void testBind() {

        // Create data store for buffer
        BufferObject bo = BufferObject::generate();

        // Use as the array buffer
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bo);

        // Check the binding
        GLint id;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
        assert (id == bo.id());

        // Check for OpenGL errors
        const GLuint error = glGetError();
        assert (error == GL_NO_ERROR);
    }

    /**
     * Ensures data works correctly.
     */
    void testData() {

        // Create data store for buffer
        BufferObject bo = BufferObject::generate();

        // Use as the array buffer
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bo);
        buffer.data(16, NULL, GL_STATIC_DRAW);
        buffer.unbind(bo);

        // Check for OpenGL errors
        const GLuint error = glGetError();
        assert (error == GL_NO_ERROR);
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
    BufferTest test;
    try {
        test.testBind();
        test.testData();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

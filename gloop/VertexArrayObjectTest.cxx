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
#include "gloop/VertexArrayObject.hxx"
#include <GL/glfw.h>
using namespace std;
using namespace Gloop;


/**
 * Unit test for VertexArrayObject.
 */
class VertexArrayObjectTest {
public:

    /**
     * Ensures a vertex array object can be a key in an STL map.
     */
    void testAddToStlMap() {
        map<VertexArrayObject,string> m;
        const VertexArrayObject v1 = VertexArrayObject::generate();
        const VertexArrayObject v2 = VertexArrayObject::generate();
        m[v1] = "foo";
        m[v2] = "bar";
    }

    /**
     * Ensures a vertex array object can be added to an STL vector.
     */
    void testAddToStlVector() {
        vector<VertexArrayObject> v;
        const VertexArrayObject vao = VertexArrayObject::generate();
        v.push_back(vao);
    }

    /**
     * Ensures enabling a vertex attrib array with a bad index throws an exception.
     */
    void testEnableVertexAttribArrayWithBadIndex() {

        // Get the maximum number of vertex attributes
        GLint max;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);

        // Try to set one more than the maximum
        try {
            const VertexArrayObject vao = VertexArrayObject::generate();
            vao.bind();
            vao.enableVertexAttribArray(max + 1);
        } catch (invalid_argument& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught in testEnableVertexAttribArrayWithBadIndex!");
    }

    /**
     * Ensures vertex array object returned by generate is valid.
     */
    void testGenerate() {
        const VertexArrayObject vao = VertexArrayObject::generate();
        assert (vao.id() > 0);
    }

    /**
     * Ensures unbinding a VAO that's already bound works correctly.
     */
    void testUnbindWhileBound() {

        // Generate a new VAO
        const VertexArrayObject vao = VertexArrayObject::generate();

        // Bind the VAO
        vao.bind();
        if (!vao.bound()) {
            throw runtime_error("VAO was not bound in testUnbindWhileBound!");
        }

        // Unbind the VAO
        vao.unbind();
        if (vao.bound()) {
            throw runtime_error("VAO was not unbound in testUnbindWhileBound!");
        }
    }

    /**
     * Ensures unbinding a VAO that's not already bound throws an exception.
     */
    void testUnbindWhileNotBound() {

        // Generate a new VAO
        const VertexArrayObject vao = VertexArrayObject::generate();

        // Unbind the VAO
        try {
            vao.unbind();
        } catch (logic_error& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught in testUnbindWhileNotBound");
    }

    /**
     * Ensures setting a pointer with a bad index throws an exception.
     */
    void testVertexAttribPointerWithBadIndex() {

        // Generate and bind a new VAO
        const VertexArrayObject vao = VertexArrayObject::generate();
        vao.bind();

        // Generate and bind a new buffer object
        const BufferObject bufferObject = BufferObject::generate();
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bufferObject);

        // Get the maximum number of vertex attributes
        GLint max;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);

        // Make a pointer with a bad index
        VertexAttribPointer vap;
        vap.index = max + 1;

        // Try to use a pointer with the bad index
        try {
            vao.vertexAttribPointer(vap);
        } catch (invalid_argument& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught in testVertexAttribPointerWithBadIndex!");
    }

    /**
     * Ensures setting a pointer with a low size throws an exception.
     */
    void testVertexAttribPointerWithLowSize() {

        // Generate and bind a new VAO
        const VertexArrayObject vao = VertexArrayObject::generate();
        vao.bind();

        // Generate and bind a new buffer object
        const BufferObject bufferObject = BufferObject::generate();
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bufferObject);

        // Make a pointer with a low size
        VertexAttribPointer vap;
        vap.size = 0;

        // Try to use the pointer
        try {
            vao.vertexAttribPointer(vap);
        } catch (invalid_argument& e) {
            return;
        }
        throw runtime_error("Exception not caught in testVertexAttribPointerWithLowSize!");
    }

    /**
     * Ensures setting a pointer with a high size throws an exception.
     */
    void testVertexAttribPointerWithHighSize() {

        // Generate and bind a new VAO
        const VertexArrayObject vao = VertexArrayObject::generate();
        vao.bind();

        // Generate and bind a new buffer object
        const BufferObject bufferObject = BufferObject::generate();
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bufferObject);

        // Make a pointer with a high size
        VertexAttribPointer vap;
        vap.size = 5;

        // Try to use the pointer
        try {
            vao.vertexAttribPointer(vap);
        } catch (invalid_argument& e) {
            return;
        }
        throw runtime_error("Exception not caught in testVertexAttribPointerWithHighSize!");
    }

    /**
     * Ensures wrapping a bad vertex array object ID throws an exception.
     */
    void testFromIdWithBadId() {
        const GLuint id = -1;
        try {
            VertexArrayObject::fromId(id);
        } catch (invalid_argument& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught!");
    }

    /**
     * Ensures wrapping a good vertex array object ID does not throw an exception.
     */
    void testFromIdWithGoodId() {
        GLuint id;
        glGenVertexArrays(1, &id);
        assert (id > 0);
        glBindVertexArray(id);
        const VertexArrayObject vao = VertexArrayObject::fromId(id);
        assert (vao.id() == id);
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
    VertexArrayObjectTest test;
    try {
        test.testGenerate();
        test.testFromIdWithBadId();
        test.testFromIdWithGoodId();
        test.testAddToStlMap();
        test.testAddToStlVector();
        test.testUnbindWhileBound();
        test.testUnbindWhileNotBound();
        test.testEnableVertexAttribArrayWithBadIndex();
        test.testVertexAttribPointerWithBadIndex();
        test.testVertexAttribPointerWithLowSize();
        test.testVertexAttribPointerWithHighSize();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

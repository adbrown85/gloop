/*
 * Copyright (c) 2013, Andrew Brown
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
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "gloop/RenderbufferObject.hxx"
#include "gloop/RenderbufferTarget.hxx"


/**
 * Unit test for `RenderbufferTarget`.
 */
class RenderbufferTargetTest {
public:

    // Renderbuffer target
    const Gloop::RenderbufferTarget target;

    /**
     * Ensures `RenderbufferTarget::alphaSize` works correctly.
     */
    void testAlphaSize() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.alphaSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 2, 4);

        // Check size is non-zero
        CPPUNIT_ASSERT_EQUAL(8, target.alphaSize());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::bind` works correctly.
     */
    void testBind() {

        // Generate and bind a new renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check the binding
        GLuint id;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*) &id);
        CPPUNIT_ASSERT_EQUAL(renderbuffer.id(), id);

        // Unbind
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    /**
     * Ensures `RenderbufferTarget::binding` works correctly.
     */
    void testBinding() {

        // Generate a new renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();

        // Check binding
        CPPUNIT_ASSERT_EQUAL((GLuint) 0, target.binding());

        // Bind
        target.bind(renderbuffer);

        // Check binding
        CPPUNIT_ASSERT_EQUAL(renderbuffer.id(), target.binding());

        // Unbind
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    /**
     * Ensures `RenderbufferTarget::blueSize` works correctly.
     */
    void testBlueSize() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.blueSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, 2, 4);

        // Check size is non-zero
        CPPUNIT_ASSERT_EQUAL(8, target.blueSize());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::bound` works correctly.
     */
    void testBound() {

        // Generate a new renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();

        // Check not bound
        CPPUNIT_ASSERT(!target.bound(renderbuffer));

        // Bind the renderbuffer
        target.bind(renderbuffer);

        // Check bound
        CPPUNIT_ASSERT(target.bound(renderbuffer));

        // Unbind
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    /**
     * Ensures `RenderbufferTarget::depthSize` works correctly.
     */
    void testDepthSize() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.depthSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 2, 4);

        // Check size is non-zero
        CPPUNIT_ASSERT_EQUAL(24, target.depthSize());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::greenSize` works correctly.
     */
    void testGreenSize() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.greenSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RG8, 2, 4);

        // Check size is non-zero
        CPPUNIT_ASSERT_EQUAL(8, target.greenSize());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::internalFormat` works correctly.
     */
    void testInternalFormat() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 2, 4);

        // Check internal format matches
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_RGBA8, target.internalFormat());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::redSize` works correctly.
     */
    void testRedSize() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.redSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_R8, 2, 4);

        // Check size is non-zero
        CPPUNIT_ASSERT_EQUAL(8, target.redSize());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::stencilSize` works correctly.
     */
    void testStencilSize() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.stencilSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, 2, 4);

        // Check size is non-zero
        CPPUNIT_ASSERT_EQUAL(8, target.stencilSize());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::storage` works correctly.
     */
    void testStorage() {

        // Generate and bind a renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Check size is zero
        CPPUNIT_ASSERT_EQUAL(0, target.stencilSize());

        // Allocate storage for the renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 2, 4);

        // Check format, width, and height
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_RGBA8, target.internalFormat());
        CPPUNIT_ASSERT_EQUAL(2, target.width());
        CPPUNIT_ASSERT_EQUAL(4, target.height());

        // Unbind
        target.unbind();
    }

    /**
     * Ensures `RenderbufferTarget::unbind` works correctly.
     */
    void testUnbind() {

        // Generate and bind a new renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        target.bind(renderbuffer);

        // Unbind
        target.unbind();

        // Check binding
        GLuint id;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*) &id);
        CPPUNIT_ASSERT_EQUAL((GLuint) 0, id);
    }
};

int main(int argc, char* argv[]) {

    // Initialize
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        RenderbufferTargetTest test;
        test.testAlphaSize();
        test.testBind();
        test.testBinding();
        test.testBlueSize();
        test.testBound();
        test.testDepthSize();
        test.testGreenSize();
        test.testInternalFormat();
        test.testRedSize();
        test.testStencilSize();
        test.testStorage();
        test.testUnbind();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

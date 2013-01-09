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
#include <iostream>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "gloop/FramebufferObject.hxx"


/**
 * Unit test for `FramebufferObject`.
 */
class FramebufferObjectTest {
public:

    /**
     * Ensures `FramebufferObject::operator=` copies identifier and returns reference correctly.
     */
    void testAssignmentOperator() {

        // Generate two framebuffers
        Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject::generate();

        // Store identifiers
        const GLuint id1 = f1.id();
        const GLuint id2 = f2.id();
        CPPUNIT_ASSERT(id1 != id2);

        // Assign framebuffer and check identifiers
        Gloop::FramebufferObject* ptr = &(f1 = f2);
        CPPUNIT_ASSERT_EQUAL(id2, f1.id());
        CPPUNIT_ASSERT_EQUAL(&f1, ptr);
    }

    /**
     * Ensures `FramebufferObject::dispose` works correctly.
     */
    void testDispose() {

        // Generate a framebuffer and bind it
        const Gloop::FramebufferObject fbo = Gloop::FramebufferObject::generate();
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.id());

        // Dispose of it and check it's no longer valid
        fbo.dispose();
        CPPUNIT_ASSERT(!glIsFramebuffer(fbo.id()));
    }

    /**
     * Ensures `FramebufferObject::operator==` returns `true` for equal instances.
     */
    void testEqualityOperatorWithEqualInstances() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject(f1);
        CPPUNIT_ASSERT(f1 == f2);
    }

    /**
     * Ensures `FramebufferObject::operator==` returns `false` for unequal instances.
     */
    void testEqualityOperatorWithUnequalInstances() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject::generate();
        CPPUNIT_ASSERT(!(f1 == f2));
    }

    /**
     * Ensures `FramebufferObject::fromId` wraps a valid frambuffer correctly.
     */
    void testFromId() {

        // Generate a new framebuffer
        GLuint id;
        glGenFramebuffers(1, &id);

        // Bind the framebuffer
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);

        // Wrap the framebuffer
        const Gloop::FramebufferObject fbo = Gloop::FramebufferObject::fromId(id);
        CPPUNIT_ASSERT_EQUAL(id, fbo.id());
    }

    /**
     * Ensures `FramebufferObject::generate` creates a valid framebuffer object.
     */
    void testGenerate() {
        const Gloop::FramebufferObject fbo = Gloop::FramebufferObject::generate();
        CPPUNIT_ASSERT(fbo.id() > 0);
    }

    /**
     * Ensures `FramebufferObject::operator!=` returns `false` for equal instances.
     */
    void testInequalityOperatorWithEqualInstances() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject(f1);
        CPPUNIT_ASSERT(!(f1 != f2));
    }

    /**
     * Ensures `FramebufferObject::operator!=` returns `true` for unequal instances.
     */
    void testInequalityOperatorWithUnequalInstances() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject::generate();
        CPPUNIT_ASSERT(f1 != f2);
    }

    /**
     * Ensures `FramebufferObject::operator<` returns `false` for equal instances.
     */
    void testLessThanOperatorWithEqualInstances() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject(f1);
        CPPUNIT_ASSERT(!(f1 < f2));
    }

    /**
     * Ensures `FramebufferObject::operator<` returns `true` when passed a greater instance.
     */
    void testLessThanOperatorWithGreaterInstance() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject::generate();
        CPPUNIT_ASSERT(f1 < f2);
    }

    /**
     * Ensures `FramebufferObject::operator<` returns `true` when passed a less instance.
     */
    void testLessThanOperatorWithLessInstance() {
        const Gloop::FramebufferObject f1 = Gloop::FramebufferObject::generate();
        const Gloop::FramebufferObject f2 = Gloop::FramebufferObject::generate();
        CPPUNIT_ASSERT(!(f2 < f1));
    }
};

int main(int argc, char* argv[]) {

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        FramebufferObjectTest test;
        test.testAssignmentOperator();
        test.testDispose();
        test.testEqualityOperatorWithEqualInstances();
        test.testEqualityOperatorWithUnequalInstances();
        test.testFromId();
        test.testGenerate();
        test.testInequalityOperatorWithEqualInstances();
        test.testInequalityOperatorWithUnequalInstances();
        test.testLessThanOperatorWithEqualInstances();
        test.testLessThanOperatorWithGreaterInstance();
        test.testLessThanOperatorWithLessInstance();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

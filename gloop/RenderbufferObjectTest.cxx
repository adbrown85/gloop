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


/**
 * Unit test for `RenderbufferObject`.
 */
class RenderbufferObjectTest {
public:

    /**
     * Ensures a renderbuffer can be added to an STL map.
     */
    void testAddToMap() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2 = Gloop::RenderbufferObject::generate();
        std::map<Gloop::RenderbufferObject,Gloop::RenderbufferObject> renderbuffers;
        renderbuffers.insert(std::pair<Gloop::RenderbufferObject,Gloop::RenderbufferObject>(r1, r2));
    }

    /**
     * Ensures a renderbuffer can be added to an STL set.
     */
    void testAddToSet() {
        std::set<Gloop::RenderbufferObject> renderbuffers;
        renderbuffers.insert(Gloop::RenderbufferObject::generate());
    }

    /**
     * Ensures a renderbuffer can be added to an STL vector.
     */
    void testAddToVector() {
        std::vector<Gloop::RenderbufferObject> renderbuffers;
        renderbuffers.push_back(Gloop::RenderbufferObject::generate());
    }

    /**
     * Ensures `RenderbufferObject::operator=` works correctly.
     */
    void testAssignmentOperator() {

        // Generate two renderbuffers
        Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2 = Gloop::RenderbufferObject::generate();

        // Assign second to first
        Gloop::RenderbufferObject* ptr = &(r1 = r2);

        // Check identifiers
        CPPUNIT_ASSERT_EQUAL(r2.id(), r1.id());

        // Check returned reference
        CPPUNIT_ASSERT_EQUAL(&r1, ptr);
    }

    /**
     * Ensures `RenderbufferObject::dispose` works correctly.
     */
    void testDispose() {

        // Generate and bind a new renderbuffer
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer.id());

        // Dispose and check it was deleted
        renderbuffer.dispose();
        CPPUNIT_ASSERT(!glIsRenderbuffer(renderbuffer.id()));
    }

    /**
     * Ensures `RenderbufferObject::operator==` returns `true` for equal instances.
     */
    void testEqualityOperatorWithEqual() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2(r1);
        CPPUNIT_ASSERT(r1 == r2);
    }

    /**
     * Ensures `RenderbufferObject::operator==` returns `false` for unequal instances.
     */
    void testEqualityOperatorWithUnequal() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2 = Gloop::RenderbufferObject::generate();
        CPPUNIT_ASSERT(!(r1 == r2));
    }

    /**
     * Ensures `RenderbufferObject::fromId` throws if passed an invalid identifier.
     */
    void testFromIdWithInvalidId() {

        // Generate a framebuffer
        GLuint id;
        glGenFramebuffers(1, &id);
        if (id == 0) {
            throw std::runtime_error("Could not generate framebuffer!");
        }

        // Try to create a renderbuffer from the ID
        CPPUNIT_ASSERT_THROW(Gloop::RenderbufferObject::fromId(id), std::invalid_argument);
    }

    /**
     * Ensures `RenderbufferObject::fromId` works with a valid identifier.
     */
    void testFromIdWithValidId() {

        // Generate a renderbuffer manually
        GLuint id;
        glGenRenderbuffers(1, &id);
        if (id == 0) {
            throw std::runtime_error("Could not generate renderbuffer!");
        }

        // Bind the renderbuffer
        glBindRenderbuffer(GL_RENDERBUFFER, id);

        // Create a renderbuffer from the ID
        const Gloop::RenderbufferObject rbo = Gloop::RenderbufferObject::fromId(id);
        CPPUNIT_ASSERT_EQUAL(id, rbo.id());

        // Unbind
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    /**
     * Ensures `RenderbufferObject::generate` works correctly.
     */
    void testGenerate() {
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        CPPUNIT_ASSERT(renderbuffer.id() > 0);
    }

    /**
     * Ensures `RenderbufferObject::operator!=` returns `false` for equal instances.
     */
    void testInequalityOperatorWithEqual() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2(r1);
        CPPUNIT_ASSERT(!(r1 != r2));
    }

    /**
     * Ensures `RenderbufferObject::operator!=` returns `true` for unequal instances.
     */
    void testInequalityOperatorWithUnequal() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2 = Gloop::RenderbufferObject::generate();
        CPPUNIT_ASSERT(r1 != r2);
    }

    /**
     * Ensures `RenderbufferObject::operator<` works with an instance with a larger ID.
     */
    void testLessThanOperatorWithEqual() {
        const Gloop::RenderbufferObject renderbuffer = Gloop::RenderbufferObject::generate();
        CPPUNIT_ASSERT(!(renderbuffer < renderbuffer));
    }

    /**
     * Ensures `RenderbufferObject::operator<` works with an instance with a larger ID.
     */
    void testLessThanOperatorWithGreater() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2 = Gloop::RenderbufferObject::generate();
        CPPUNIT_ASSERT(r1 < r2);
    }

    /**
     * Ensures `RenderbufferObject::operator<` works with an instance with a smaller ID.
     */
    void testLessThanOperatorWithLess() {
        const Gloop::RenderbufferObject r1 = Gloop::RenderbufferObject::generate();
        const Gloop::RenderbufferObject r2 = Gloop::RenderbufferObject::generate();
        CPPUNIT_ASSERT(!(r2 < r1));
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
        RenderbufferObjectTest test;
        test.testAddToMap();
        test.testAddToSet();
        test.testAddToVector();
        test.testAssignmentOperator();
        test.testDispose();
        test.testEqualityOperatorWithEqual();
        test.testEqualityOperatorWithUnequal();
        test.testFromIdWithInvalidId();
        test.testFromIdWithValidId();
        test.testGenerate();
        test.testInequalityOperatorWithEqual();
        test.testInequalityOperatorWithUnequal();
        test.testLessThanOperatorWithEqual();
        test.testLessThanOperatorWithGreater();
        test.testLessThanOperatorWithLess();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

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
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "gloop/FramebufferObject.hxx"
#include "gloop/FramebufferTarget.hxx"
#include "gloop/TextureObject.hxx"
#include "gloop/TextureTarget.hxx"
using Gloop::FramebufferObject;
using Gloop::FramebufferTarget;
using Gloop::TextureObject;
using Gloop::TextureTarget;
using std::string;


/**
 * Unit test for `FramebufferTarget`.
 */
class FramebufferTargetTest {
public:

    /**
     * Ensures `FramebufferTarget::operator=` copies values and returns reference correctly.
     */
    void testAssignmentOperator() {

        // Get two different targets
        FramebufferTarget t1 = FramebufferTarget::drawFramebuffer();
        const FramebufferTarget t2 = FramebufferTarget::readFramebuffer();

        // Store enums
        const GLenum e1 = t1.toEnum();
        const GLenum e2 = t2.toEnum();
        CPPUNIT_ASSERT(e1 != e2);

        // Store strings
        const string s1 = t1.toString();
        const string s2 = t2.toString();
        CPPUNIT_ASSERT(s1 != s2);

        // Assign and check enum, string, and reference
        FramebufferTarget* ptr = &(t1 = t2);
        CPPUNIT_ASSERT_EQUAL(e2, t1.toEnum());
        CPPUNIT_ASSERT_EQUAL(s2, t1.toString());
        CPPUNIT_ASSERT_EQUAL(&t1, ptr);
    }

    /**
     * Ensures `FramebufferTarget::bind` works correctly.
     */
    void testBind() {

        // Bind a new FBO to the target
        const FramebufferObject fbo = FramebufferObject::generate();
        const FramebufferTarget target = FramebufferTarget::drawFramebuffer();
        target.bind(fbo);

        // Check the binding
        GLint binding;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &binding);
        CPPUNIT_ASSERT_EQUAL(fbo.id(), (GLuint) binding);

        // Unbind
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    /**
     * Ensures `FramebufferTarget::binding` works correctly.
     */
    void testBinding() {

        // Bind a new FBO to the target
        const FramebufferObject fbo = FramebufferObject::generate();
        const FramebufferTarget target = FramebufferTarget::drawFramebuffer();
        target.bind(fbo);

        // Check the binding
        CPPUNIT_ASSERT_EQUAL(target.binding(), fbo.id());

        // Unbind
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    /**
     * Ensures `FraembufferTarget::bound()` works correctly.
     */
    void testBound() {

        // Bind a new FBO to the target
        const FramebufferObject fbo = FramebufferObject::generate();
        const FramebufferTarget target = FramebufferTarget::drawFramebuffer();
        target.bind(fbo);

        // Check the binding
        CPPUNIT_ASSERT(target.bound());

        // Unbind
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    /**
     * Ensures `FraembufferTarget::bound(FramebufferObject)` works correctly.
     */
    void testBoundFramebufferObject() {

        // Bind a new FBO to the target
        const FramebufferObject fbo = FramebufferObject::generate();
        const FramebufferTarget target = FramebufferTarget::drawFramebuffer();
        target.bind(fbo);

        // Check the binding
        CPPUNIT_ASSERT(target.bound(fbo));

        // Unbind
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    /**
     * Ensures the target returned by `FramebufferTarget::drawFramebuffer` is correct.
     */
    void testDrawFramebuffer() {
        const FramebufferTarget target = FramebufferTarget::drawFramebuffer();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_DRAW_FRAMEBUFFER, target.toEnum());
        CPPUNIT_ASSERT_EQUAL(std::string("GL_DRAW_FRAMEBUFFER"), target.toString());
    }

    /**
     * Ensures `FramebufferTarget::operator==` returns `true` for equal instances.
     */
    void testEqualityOperatorWithEqualInstances() {
        const FramebufferTarget t1 = FramebufferTarget::drawFramebuffer();
        const FramebufferTarget t2(t1);
        CPPUNIT_ASSERT(t1 == t2);
    }

    /**
     * Ensures `FramebufferTarget::operator==` returns `false` for unequal instances.
     */
    void testEqualityOperatorWithUnequalInstances() {
        const FramebufferTarget t1 = FramebufferTarget::drawFramebuffer();
        const FramebufferTarget t2 = FramebufferTarget::readFramebuffer();
        CPPUNIT_ASSERT(!(t1 == t2));
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_COMPLETE`.
     */
    void testFormatStatusWithComplete() {
        const string expected = "GL_FRAMEBUFFER_COMPLETE";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_COMPLETE);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_UNDEFINED`.
     */
    void testFormatStatusWithUndefined() {
        const string expected = "GL_FRAMEBUFFER_UNDEFINED";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_UNDEFINED);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT`.
     */
    void testFormatStatusWithIncompleteAttachment() {
        const string expected = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT`.
     */
    void testFormatStatusWithIncompleteMissingAttachment() {
        const string expected = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER`.
     */
    void testFormatStatusWithIncompleteDrawBuffer() {
        const string expected = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER`.
     */
    void testFormatStatusWithIncompleteReadBuffer() {
        const string expected = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_UNSUPPORTED`.
     */
    void testFormatStatusWithUnsupported() {
        const string expected = "GL_FRAMEBUFFER_UNSUPPORTED";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_UNSUPPORTED);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE`.
     */
    void testFormatStatusWithIncompleteMultisample() {
        const string expected = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::formatStatus` works with `GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS`.
     */
    void testFormatStatusWithIncompleteLayerTargets() {
        const string expected = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
        const string actual = FramebufferTarget::formatStatus(GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS);
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `FramebufferTarget::getMaxColorAttachment` works correctly.
     */
    void testGetMaxColorAttachments() {
        const GLint max = FramebufferTarget::getMaxColorAttachments();
        CPPUNIT_ASSERT(max >= 0);
    }

    /**
     * Ensures `FramebufferTarget::operator!=` returns `false` for equal instances.
     */
    void testInequalityOperatorWithEqualInstances() {
        const FramebufferTarget t1 = FramebufferTarget::drawFramebuffer();
        const FramebufferTarget t2(t1);
        CPPUNIT_ASSERT(!(t1 != t2));
    }

    /**
     * Ensures `FramebufferTarget::operator!=` returns `true` for unequal instances.
     */
    void testInequalityOperatorWithUnequalInstances() {
        const FramebufferTarget t1 = FramebufferTarget::drawFramebuffer();
        const FramebufferTarget t2 = FramebufferTarget::readFramebuffer();
        CPPUNIT_ASSERT(t1 != t2);
    }

    /**
     * Ensures `FramebufferTarget::isAttachment` returns `false` for max color attachment.
     */
    void testIsAttachmentWithColorAttachmentMax() {
        const GLenum enumeration = GL_COLOR_ATTACHMENT0 + FramebufferTarget::getMaxColorAttachments();
        CPPUNIT_ASSERT(!FramebufferTarget::isAttachment(enumeration));
    }

    /**
     * Ensures `FramebufferTarget::isAttachment` returns `true` for `GL_COLOR_ATTACHMENT1`.
     */
    void testIsAttachmentWithColorAttachmentOne() {
        CPPUNIT_ASSERT(FramebufferTarget::isAttachment(GL_COLOR_ATTACHMENT1));
    }

    /**
     * Ensures `FramebufferTarget::isAttachment` returns `true` for `GL_COLOR_ATTACHMENT0`.
     */
    void testIsAttachmentWithColorAttachmentZero() {
        CPPUNIT_ASSERT(FramebufferTarget::isAttachment(GL_COLOR_ATTACHMENT0));
    }

    /**
     * Ensures `FramebufferTarget::isAttachment` returns `true` for `GL_DEPTH_ATTACHMENT`.
     */
    void testIsAttachmentWithDepthAttachment() {
        CPPUNIT_ASSERT(FramebufferTarget::isAttachment(GL_DEPTH_ATTACHMENT));
    }

    /**
     * Ensures `FramebufferTarget::isAttachment` returns `true` for `GL_DEPTH_STENCIL_ATTACHMENT`.
     */
    void testIsAttachmentWithDepthStencilAttachment() {
        CPPUNIT_ASSERT(FramebufferTarget::isAttachment(GL_DEPTH_STENCIL_ATTACHMENT));
    }

    /**
     * Ensures `FramebufferTarget::isAttachment` returns `true` for `GL_STENCIL_ATTACHMENT`.
     */
    void testIsAttachmentWithStencilAttachment() {
        CPPUNIT_ASSERT(FramebufferTarget::isAttachment(GL_STENCIL_ATTACHMENT));
    }

    /**
     * Ensures the target returned by `FramebufferTarget::readFramebuffer` is correct.
     */
    void testReadFramebuffer() {
        const FramebufferTarget target = FramebufferTarget::readFramebuffer();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_READ_FRAMEBUFFER, target.toEnum());
        CPPUNIT_ASSERT_EQUAL(std::string("GL_READ_FRAMEBUFFER"), target.toString());
    }

    /**
     * Ensures `FramebufferTarget::texture2d` works correctly.
     */
    void testTexture2d() {

        // Generate and bind a new FBO
        const FramebufferObject fbo = FramebufferObject::generate();
        const FramebufferTarget drawFramebuffer = FramebufferTarget::drawFramebuffer();
        drawFramebuffer.bind(fbo);

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget texture2d = TextureTarget::texture2d();
        texture2d.bind(texture);
        texture2d.texImage2d(0, GL_RGB, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        texture2d.unbind();

        // Attach the texture
        drawFramebuffer.texture2d(GL_COLOR_ATTACHMENT0, texture2d, texture, 0);
        const GLenum status = drawFramebuffer.checkStatus();
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            throw std::runtime_error("Framebuffer is incomplete!");
        }
    }

    /**
     * Ensures `FramebufferTarget::unbind` works correctly.
     */
    void testUnbind() {

        // Bind a new FBO to the target
        const FramebufferObject fbo = FramebufferObject::generate();
        const FramebufferTarget target = FramebufferTarget::drawFramebuffer();
        target.bind(fbo);

        // Check the binding
        GLint binding;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &binding);
        CPPUNIT_ASSERT_EQUAL(fbo.id(), (GLuint) binding);

        // Unbind it
        target.unbind();

        // Check the binding again
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &binding);
        CPPUNIT_ASSERT_EQUAL((GLuint) 0, (GLuint) binding);
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
        FramebufferTargetTest test;
        test.testAssignmentOperator();
        test.testBind();
        test.testBinding();
        test.testBound();
        test.testBoundFramebufferObject();
        test.testDrawFramebuffer();
        test.testEqualityOperatorWithEqualInstances();
        test.testEqualityOperatorWithUnequalInstances();
        test.testFormatStatusWithComplete();
        test.testFormatStatusWithUndefined();
        test.testFormatStatusWithIncompleteAttachment();
        test.testFormatStatusWithIncompleteMissingAttachment();
        test.testFormatStatusWithIncompleteDrawBuffer();
        test.testFormatStatusWithIncompleteReadBuffer();
        test.testFormatStatusWithUnsupported();
        test.testFormatStatusWithIncompleteMultisample();
        test.testFormatStatusWithIncompleteLayerTargets();
        test.testGetMaxColorAttachments();
        test.testInequalityOperatorWithEqualInstances();
        test.testInequalityOperatorWithUnequalInstances();
        test.testIsAttachmentWithColorAttachmentMax();
        test.testIsAttachmentWithColorAttachmentOne();
        test.testIsAttachmentWithColorAttachmentZero();
        test.testIsAttachmentWithDepthAttachment();
        test.testIsAttachmentWithDepthStencilAttachment();
        test.testIsAttachmentWithStencilAttachment();
        test.testReadFramebuffer();
        test.testTexture2d();
        test.testUnbind();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

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
#include <cassert>
#include "gloop/RenderbufferTarget.hxx"
namespace Gloop {

/**
 * Constructs a handle for the OpenGL renderbuffer target.
 */
RenderbufferTarget::RenderbufferTarget() {
    // empty
}

/**
 * Returns the size of the current renderbuffer's alpha channel.
 *
 * @return Size of the current renderbuffer's alpha channel
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::alphaSize() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_ALPHA_SIZE);
}

/**
 * Binds a renderbuffer to the target.
 *
 * @param renderbuffer Renderbuffer to bind
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindRenderbuffer.xml
 */
void RenderbufferTarget::bind(const RenderbufferObject& renderbuffer) const {
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer.id());
}

/**
 * Returns the raw OpenGL identifier of the current renderbuffer.
 *
 * @return Identifier of the currently bound renderbuffer, or `0` if none is bound
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindRenderbuffer.xml
 */
GLuint RenderbufferTarget::binding() const {
    GLuint id;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*) &id);
    return id;
}

/**
 * Returns the size of the current renderbuffer's blue channel.
 *
 * @return Size of the current renderbuffer's blue channel
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::blueSize() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_BLUE_SIZE);
}

/**
 * Checks if a renderbuffer is currently bound.
 *
 * @param renderbuffer Renderbuffer to check
 * @return `true` if the renderbuffer is currently bound
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindRenderbuffer.xml
 */
bool RenderbufferTarget::bound(const RenderbufferObject& renderbuffer) const {
    return binding() == renderbuffer.id();
}

/**
 * Returns the size of the current renderbuffer's depth channel.
 *
 * @return Size of the current renderbuffer's depth channel
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::depthSize() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_DEPTH_SIZE);
}

/**
 * Returns the maximum size of renderbuffer.
 *
 * @return Maximum size of a renderbuffer
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGet.xml
 */
GLsizei RenderbufferTarget::getMaxRenderbufferSize() {
    GLint value;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &value);
    return (GLsizei) value;
}

/**
 * Returns the value of a renderbuffer parameter.
 *
 * @param name Name of the parameter
 * @return Value of the parameter
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLint RenderbufferTarget::getParameter(const GLenum name) {
    GLint value;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, name, &value);
    return value;
}

/**
 * Returns the size of the current renderbuffer's green channel.
 *
 * @return Size of the current renderbuffer's green channel
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::greenSize() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_GREEN_SIZE);
}

/**
 * Returns the height of the current renderbuffer.
 *
 * @return Height of the current renderbuffer
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::height() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_HEIGHT);
}

/**
 * Returns the internal format of the current renderbuffer.
 *
 * @return Internal format of the current renderbuffer
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLenum RenderbufferTarget::internalFormat() const {
    assert (binding() != 0);
    return (GLenum) getParameter(GL_RENDERBUFFER_INTERNAL_FORMAT);
}

/**
 * Returns the size of the current renderbuffer's red channel.
 *
 * @return Size of the current renderbuffer's red channel
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::redSize() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_RED_SIZE);
}

/**
 * Returns the size of the current renderbuffer's stencil channel.
 *
 * @return Size of the current renderbuffer's stencil channel
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::stencilSize() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_STENCIL_SIZE);
}

/**
 * Allocates an image for the current renderbuffer.
 *
 * @param internalFormat Data type and size of image
 * @param width Width of image
 * @param height Height of image
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @pre Internal format is color-renderable, depth-renderable, or stencil-renderable
 * @pre Width and height are less than the value of `GL_MAX_RENDERBUFFER_SIZE`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glRenderbufferStorage.xml
 */
void RenderbufferTarget::storage(const GLenum internalFormat, const GLsizei width, const GLsizei height) const {
    assert (binding() != 0);
    assert (width <= getMaxRenderbufferSize());
    assert (height <= getMaxRenderbufferSize());
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
}

/**
 * Unbinds the currently bound renderbuffer, if any.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindRenderbuffer.xml
 */
void RenderbufferTarget::unbind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

/**
 * Returns the width of the current renderbuffer.
 *
 * @return Width of the current renderbuffer
 * @pre A renderbuffer is currently bound to the renderbuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetRenderbufferParameter.xml
 */
GLsizei RenderbufferTarget::width() const {
    assert (binding() != 0);
    return (GLsizei) getParameter(GL_RENDERBUFFER_WIDTH);
}

}; /* namespace Gloop */

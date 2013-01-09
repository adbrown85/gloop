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
#include <stdexcept>
#include "gloop/FramebufferObject.hxx"
namespace Gloop {

/**
 * Constructs a framebuffer object handle with a given ID.
 *
 * @param id Identifier of framebuffer object
 */
FramebufferObject::FramebufferObject(const GLuint id) : _id(id) {
    // empty
}

/**
 * Constructs a framebuffer object handle by copying the identifier of another one.
 *
 * @param fbo Framebuffer object to copy identifier from
 */
FramebufferObject::FramebufferObject(const FramebufferObject& fbo) : _id(fbo._id) {
    // empty
}

/**
 * Deletes the underlying OpenGL framebuffer object this handle represents.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glDeleteFramebuffers.xml
 */
void FramebufferObject::dispose() const {
    glDeleteFramebuffers(1, &_id);
}

/**
 * Creates a handle from the raw OpenGL identifier of a framebuffer object.
 *
 * @param id Raw OpenGL identifier of a framebuffer object
 * @return Handle for the OpenGL framebuffer object
 * @pre Identifier is a number returned by `glGenFramebuffers` and bound with `glBindFramebuffer`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGenFramebuffers.xml
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindFramebuffer.xml
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glIsFramebuffer.xml
 */
FramebufferObject FramebufferObject::fromId(const GLuint id) {
    assert (glIsFramebuffer(id));
    return FramebufferObject(id);
}

/**
 * Generates a new OpenGL framebuffer object and returns a handle to it.
 *
 * @return Handle to the new OpenGL framebuffer object
 * @throws std::runtime_error if could not generate new OpenGL framebuffer object
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGenFramebuffers.xml
 */
FramebufferObject FramebufferObject::generate() {

    // Generate ID
    GLuint id;
    glGenFramebuffers(1, &id);

    // Check ID
    if (id == 0) {
        throw std::runtime_error("[FramebufferObject] Could not generate new FBO!");
    }

    // Return handle
    return FramebufferObject(id);
}

/**
 * Returns the raw OpenGL identifier of the framebuffer object this handle represents.
 *
 * @return Raw OpenGL identifier of the framebuffer object this handle represents
 */
GLuint FramebufferObject::id() const {
    return _id;
}

/**
 * Checks if this handle represents a different OpenGL framebuffer object than another handle.
 *
 * @param fbo Handle to check
 * @return `true` if this handle reperesents a different OpenGL framebuffer object than the given handle
 */
bool FramebufferObject::operator!=(const FramebufferObject& fbo) const {
    return _id != fbo._id;
}

/**
 * Compares the raw OpenGL identifier of this handle to that of another one.
 *
 * @param fbo Handle to compare to
 * @return `true` if this handle's raw OpenGL identifier is less than that of the given handle
 */
bool FramebufferObject::operator<(const FramebufferObject& fbo) const {
    return _id < fbo._id;
}

/**
 * Changes which OpenGL framebuffer object this handle represents.
 *
 * @param fbo Framebuffer object to copy raw OpenGL identifier from
 * @return Reference to this handle to support chaining
 */
FramebufferObject& FramebufferObject::operator=(const FramebufferObject& fbo) {
    _id = fbo._id;
    return (*this);
}

/**
 * Checks if this handle represents the same OpenGL framebuffer object as another handle.
 *
 * @param fbo Handle to check
 * @return `true` if this handle reperesents the same OpenGL framebuffer object as the given handle
 */
bool FramebufferObject::operator==(const FramebufferObject& fbo) const {
    return _id == fbo._id;
}

} /* namespace Gloop */

std::ostream& operator<<(std::ostream& stream, const Gloop::FramebufferObject& fbo) {
    stream << fbo.id();
    return stream;
}

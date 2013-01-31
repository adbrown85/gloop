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
#include "gloop/RenderbufferObject.hxx"
namespace Gloop {

/**
 * Constructs a renderbuffer from a raw OpenGL identifier.
 *
 * @param id Raw OpenGL identifier
 */
RenderbufferObject::RenderbufferObject(const GLuint id) : _id(id) {
    // empty
}

/**
 * Constructs a renderbuffer by copying the identifier of another one.
 *
 * @param renderbuffer Renderbuffer to copy
 */
RenderbufferObject::RenderbufferObject(const RenderbufferObject& renderbuffer) : _id(renderbuffer._id) {
    // empty
}

/**
 * Deletes the underlying OpenGL renderbuffer this handle represents.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glDeleteRenderbuffers.xml
 */
void RenderbufferObject::dispose() const {
    glDeleteRenderbuffers(1, &_id);
}

/**
 * Creates a renderbuffer handle from an existing OpenGL renderbuffer.
 *
 * @param id Raw OpenGL identifier of renderbuffer
 * @return Handle for the renderbuffer
 * @throws std::invalid_argument if identifier is not a valid renderbuffer
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glIsRenderbuffer.xml
 */
RenderbufferObject RenderbufferObject::fromId(const GLuint id) {
    if (!glIsRenderbuffer(id)) {
        throw std::invalid_argument("[RenderbufferObject] ID is not a valid renderbuffer!");
    }
    return RenderbufferObject(id);
}

/**
 * Creates a new OpenGL renderbuffer.
 *
 * @return Handle for the OpenGL renderbuffer
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGenRenderbuffers.xml
 */
RenderbufferObject RenderbufferObject::generate() {

    // Generate the renderbuffer
    GLuint id;
    glGenRenderbuffers(1, &id);
    if (id == 0) {
        throw std::runtime_error("[RenderbufferObject] Could not generate new renderbuffer!");
    }

    // Return the renderbuffer
    return RenderbufferObject(id);
}

/**
 * Returns the raw OpenGL identifier of this renderbuffer.
 *
 * @return Raw OpenGL identifier of this renderbuffer
 */
GLuint RenderbufferObject::id() const {
    return _id;
}

/**
 * Checks if a handle represents a different OpenGL renderbuffer than this one.
 *
 * @param renderbuffer Other renderbuffer to compare to
 * @return `true` if this handle represents a different OpenGL renderbuffer than this one
 */
bool RenderbufferObject::operator!=(const RenderbufferObject& renderbuffer) const {
    return _id != renderbuffer._id;
}

/**
 * Compares this renderbuffer handle to another.
 *
 * @param renderbuffer Other renderbuffer handle to compare to
 * @return `true` if this handle's raw OpenGL identifer is less than the other's
 */
bool RenderbufferObject::operator<(const RenderbufferObject& renderbuffer) const {
    return _id < renderbuffer._id;
}

/**
 * Changes which OpenGL renderbuffer this handle represents.
 *
 * @param renderbuffer Renderbuffer handle to copy identifier from
 * @return Reference to this handle to support chaining
 */
RenderbufferObject& RenderbufferObject::operator=(const RenderbufferObject& renderbuffer) {
    _id = renderbuffer._id;
    return (*this);
}

/**
 * Checks if a handle represents the same OpenGL renderbuffer as this one.
 *
 * @param renderbuffer Other renderbuffer to compare to
 * @return `true` if this handle represents the same OpenGL renderbuffer as this one
 */
bool RenderbufferObject::operator==(const RenderbufferObject& renderbuffer) const {
    return _id == renderbuffer._id;
}

} /* namespace Gloop */

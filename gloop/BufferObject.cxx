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
#include "gloop/BufferObject.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs an invalid buffer object handle.
 */
BufferObject::BufferObject() {
    throw runtime_error("[BufferObject] Default constructor should not be called!");
}

/**
 * Constructs a buffer object handle from the identifer of an OpenGL buffer object.
 *
 * @param id Identifier of OpenGL buffer object, previously created using glGenBuffers
 */
BufferObject::BufferObject(GLuint id) : _id(id) {
    assert (_id > 0);
}

/**
 * Constructs a buffer object handle representing the same OpenGL buffer object as another one.
 *
 * @param bo Handle for buffer object to copy identifier from
 */
BufferObject::BufferObject(const BufferObject& bo) : _id(bo._id) {
    // pass
}

/**
 * Destructs a buffer object handle, leaving the corresponding OpenGL buffer object unaffected.
 *
 * @see @ref dispose
 */
BufferObject::~BufferObject() {
    // pass
}

/**
 * Deletes the OpenGL buffer object this handle represents.
 */
void BufferObject::dispose() const {
    glDeleteBuffers(1, &_id);
}

/**
 * Creates a buffer object handle representing an existing OpenGL buffer object.
 *
 * @param id Identifier of existing OpenGL buffer object to represent
 * @return Resulting buffer object handle
 * @throws std::invalid_argument if identifier is not an existing OpenGL buffer object
 */
BufferObject BufferObject::fromId(const GLuint id) {
    if (!glIsBuffer(id)) {
        throw invalid_argument("[BufferObject] ID is not an OpenGL buffer object!");
    }
    return BufferObject(id);
}

/**
 * Creates a buffer object handle representing a new OpenGL buffer object.
 *
 * @return Handle for new OpenGL buffer object
 * @throws std::runtime_error if could not generate a new OpenGL buffer object
 */
BufferObject BufferObject::generate() {

    // Make an OpenGL buffer object
    GLuint id;
    glGenBuffers(1, &id);
    if (id <= 0) {
        throw runtime_error("[BufferObject] Could not generate new buffer object!");
    }

    // Make the handle
    return BufferObject(id);
}

/**
 * Returns the identifer of the OpenGL buffer object this handle represents.
 */
GLuint BufferObject::id() const {
    return _id;
}

/**
 * Changes which OpenGL buffer object this handle represents.
 *
 * @param bo Handle for buffer object to copy identifier from
 * @return Reference to this handle
 */
BufferObject& BufferObject::operator=(const BufferObject& bo) {
    _id = bo._id;
    return (*this);
}

/**
 * Checks if another handle represents the same OpenGL buffer object as this one.
 *
 * @param bo Other buffer object handle to check
 * @return `true` if the other handle represents the same OpenGL buffer object
 */
bool BufferObject::operator==(const BufferObject& bo) const {
    return _id == bo._id;
}

/**
 * Checks if another handle does not represent the same OpenGL buffer object as this one.
 *
 * @param bo Other buffer object handle to check
 * @return `true` if the other handle does not represent the same OpenGL buffer object
 */
bool BufferObject::operator!=(const BufferObject& bo) const {
    return _id != bo._id;
}

/**
 * Compares the identifier of this handle's OpenGL buffer object to that of another one.
 *
 * @param bo Handle for buffer object to compare to
 * @return `true` if this handle's identifier is less than the other one's
 */
bool BufferObject::operator<(const BufferObject& bo) const {
    return _id < bo._id;
}

} /* namespace Gloop */

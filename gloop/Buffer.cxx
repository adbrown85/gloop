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
#include "gloop/Buffer.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs an invalid buffer handle.
 */
Buffer::Buffer() {
    throw runtime_error("[Buffer] Default constructor should not be called!");
}

/**
 * Constructs a buffer handle representing an OpenGL buffer.
 *
 * @param name Enumeration for the OpenGL buffer, e.g. `GL_ARRAY_BUFFER`
 * @param binding Enumeration used to look up the current binding, e.g. `GL_ARRAY_BUFFER_BINDING`
 */
Buffer::Buffer(GLenum name, GLenum binding) : _name(name), _binding(binding) {
    // pass
}

/**
 * Constructs a buffer handle representing the same OpenGL buffer as another one.
 *
 * @param bt Other buffer handle to copy
 */
Buffer::Buffer(const Buffer& bt) : _name(bt._name), _binding(bt._binding) {
    // pass
}

/**
 * Destructs a buffer handle, leaving the corresponding OpenGL buffer unaffected.
 */
Buffer::~Buffer() {
    // pass
}

/**
 * Uses a buffer object as the data store for the OpenGL buffer this handle represents.
 *
 * @param bo Handle for the buffer object to use
 */
void Buffer::bind(const BufferObject& bo) const {
    glBindBuffer(_name, bo.id());
}

/**
 * Determines the buffer object currently being used as the data store for the buffer.
 *
 * @return Identifier of the buffer object, or zero if nothing bound
 */
GLuint Buffer::binding() const {
    GLint i;
    glGetIntegerv(_binding, &i);
    return i;
}

/**
 * Checks if any buffer object is currently being used as the data store for the buffer.
 *
 * @return `true` if a buffer object is being used
 */
bool Buffer::bound() const {
    return binding() != 0;
}

/**
 * Checks if a specific buffer object is currently being used as the data store for the buffer.
 *
 * @param bo Handle for buffer object to check for
 * @return `true` if the buffer object is being used
 */
bool Buffer::bound(const BufferObject& bo) const {
    return binding() == bo.id();
}

/**
 * Allocates or reallocates memory for the data store currently bound to the buffer.
 *
 * @param size Number of bytes to allocate or reallocate
 * @param data Data to initialize memory with, or `NULL` to leave it uninitialized
 * @param usage Hint for how the memory will be used, e.g. `GL_STATIC_DRAW`
 * @pre A buffer object is currently bound to the buffer as its data store
 */
void Buffer::data(GLsizeiptr size, const GLvoid* data, GLenum usage) const {
    assert (bound());
    glBufferData(_name, size, data, usage);
}

/**
 * Changes which OpenGL buffer this handle represents.
 *
 * @param bt Other buffer handle to copy name from
 * @return Reference to this handle
 */
Buffer& Buffer::operator=(const Buffer& bt) {
    _name = bt._name;
    _binding = bt._binding;
    return (*this);
}

/**
 * Checks if another buffer represents the same OpenGL buffer as this one.
 *
 * @param bt Other buffer handle to check
 * @return `true` if the other handle represents the same OpenGL buffer
 */
bool Buffer::operator==(const Buffer& bt) const {
    return _name == bt._name;
}

/**
 * Checks if another buffer does not represent the same OpenGL buffer as this one.
 *
 * @param bt Other buffer handle to check
 * @return `true` if the other handle does not represent the same OpenGL buffer
 */
bool Buffer::operator!=(const Buffer& bt) const {
    return _name != bt._name;
}

/**
 * Compares the name of this buffer handle to that of another one.
 *
 * @param bt Other buffer handle to compare to
 * @return `true` if this handle's identifier is less than the other one's
 */
bool Buffer::operator<(const Buffer& bt) const {
    return _name < bt._name;
}

/**
 * Changes all or some of the data in the buffer object currently bound to the buffer.
 *
 * @param offset Number of bytes from the start of the buffer object to start replacing data
 * @param size Number of bytes to copy into the buffer object
 * @param data Pointer to the data to copy into the buffer object
 * @pre A buffer object is currently bound to the buffer as its data store
 */
void Buffer::subData(GLintptr offset, GLsizeiptr size, const GLvoid* data) const {
    assert (bound());
    glBufferSubData(_name, offset, size, data);
}

/**
 * Unbinds a buffer object from the OpenGL buffer this handle represents.
 *
 * @param bo Handle for the buffer object to unbind
 * @pre Specified buffer object is currently bound to the buffer
 */
void Buffer::unbind(const BufferObject& bo) const {
    assert (bound(bo));
    glBindBuffer(_name, 0);
}

// INSTANCES

/**
 * Returns a handle for the `GL_ARRAY_BUFFER` buffer.
 */
Buffer Buffer::arrayBuffer() {
    return Buffer(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
}

/**
 * Returns a handle for the `GL_COPY_READ_BUFFER` buffer.
 */
Buffer Buffer::copyReadBuffer() {
    return Buffer(GL_COPY_READ_BUFFER, GL_COPY_READ_BUFFER);
}

/**
 * Returns a handle for the `GL_COPY_WRITE_BUFFER` buffer.
 */
Buffer Buffer::copyWriteBuffer() {
    return Buffer(GL_COPY_WRITE_BUFFER, GL_COPY_WRITE_BUFFER);
}

/**
 * Returns a handle for the `GL_ELEMENT_ARRAY_BUFFER` buffer.
 */
Buffer Buffer::elementArrayBuffer() {
    return Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING);
}

/**
 * Returns a handle for the `GL_PIXEL_PACK_BUFFER`.
 */
Buffer Buffer::pixelPackBuffer() {
    return Buffer(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
}

/**
 * Returns a handle for the `GL_PIXEL_UNPACK_BUFFER`.
 */
Buffer Buffer::pixelUnpackBuffer() {
    return Buffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
}

/**
 * Returns a handle for the `GL_TEXTURE_BUFFER` buffer.
 */
Buffer Buffer::textureBuffer() {
    return Buffer(GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER);
}

/**
 * Returns a handle for the `GL_TRANSFORM_FEEDBACK_BUFFER`.
 */
Buffer Buffer::transformFeedbackBuffer() {
    return Buffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING);
}

/**
 * Returns a handle for the `GL_UNIFORM_BUFFER` buffer.
 */
Buffer Buffer::uniformBuffer() {
    return Buffer(GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING);
}

} /* namespace Gloop */

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
#include <stdexcept>
#include "gloop/VertexArrayObject.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs a vertex array object handle.
 */
VertexArrayObject::VertexArrayObject() : _id(0) {
    // pass
}

/**
 * Constructs a vertex array object handle from the identifier of an existing vertex array object.
 *
 * @param id Identifier of an existing vertex array object
 */
VertexArrayObject::VertexArrayObject(const GLuint id) : _id(id) {
    // pass
}

/**
 * Constructs a vertex array object handle representing the same OpenGL vertex array object as another one.
 *
 * @param vao Vertex array object handle to copy
 */
VertexArrayObject::VertexArrayObject(const VertexArrayObject& vao) : _id(vao._id) {
    // pass
}

/**
 * Destructs a vertex array object handle, leaving the corresponding OpenGL vertex array object unaffected.
 */
VertexArrayObject::~VertexArrayObject() {
    // pass
}

/**
 * Binds the vertex array object represented by this handle into the current OpenGL context.
 *
 * @see @ref unbind
 * @see @ref bound
 */
void VertexArrayObject::bind() const {
    glBindVertexArray(_id);
}

/**
 * Checks if the vertex array object represented by this handle is currently bound.
 *
 * @return `true` if the vertex array object represented by this handle is currently bound
 * @see @ref bind
 */
bool VertexArrayObject::bound() const {

    // Get the current binding
    GLint binding;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding);

    // Check if equal
    return _id == binding;
}

/**
 * Disables a vertex array.
 *
 * @param index Index of vertex attribute the vertex array is for
 * @throws logic_error if this vertex array object is not currently bound
 * @throws invalid_argument if index is greater than or equal to `GL_MAX_VERTEX_ATTRIBS`
 * @see @ref vertexAttribPointer
 * @see @ref enableVertexAttribArray
 * @see @ref Program::attribLocation
 */
void VertexArrayObject::disableVertexAttribArray(const GLuint index) const {

    // Check if bound
    if (!bound()) {
        throw logic_error("[VertexArrayObject] Vertex array object is not currently bound!");
    }

    // Check index
    if (index >= maxVertexAttribs()) {
        throw invalid_argument("[VertexArrayObject] Index is greater than or equal to GL_MAX_VERTEX_ATTRIBS!");
    }

    // Enable it
    glEnableVertexAttribArray(index);
}

/**
 * Deletes the vertex array object represented by this handle.
 */
void VertexArrayObject::dispose() const {
    glDeleteVertexArrays(1, &_id);
}

/**
 * Enables a vertex array.
 *
 * @param index Index of vertex attribute the vertex array is for
 * @throws logic_error if this vertex array object is not currently bound
 * @throws invalid_argument if index is greater than or equal to `GL_MAX_VERTEX_ATTRIBS`
 * @see @ref vertexAttribPointer
 * @see @ref disableVertexAttribArray
 * @see @ref Program::attribLocation
 */
void VertexArrayObject::enableVertexAttribArray(const GLuint index) const {

    // Check if bound
    if (!bound()) {
        throw logic_error("[VertexArrayObject] Vertex array object is not currently bound!");
    }

    // Check index
    if (index >= maxVertexAttribs()) {
        throw invalid_argument("[VertexArrayObject] Index is greater than or equal to GL_MAX_VERTEX_ATTRIBS!");
    }

    // Enable it
    glEnableVertexAttribArray(index);
}

/**
 * Creates a vertex array object handle from the identifier of an existing vertex array object.
 *
 * @param id Identifier of an existing vertex array object
 * @return Vertex array object handle for the existing vertex array object
 * @throws invalid_argument if identifier is not a valid vertex array object
 * @see @ref generate
 */
VertexArrayObject VertexArrayObject::fromId(const GLuint id) {
    if (!glIsVertexArray(id)) {
        throw invalid_argument("[VertexArrayObject] ID is not a valid vertex array object!");
    }
    return VertexArrayObject(id);
}

/**
 * Generates a new vertex array object.
 *
 * @return Handle representing the vertex array object that was generated
 * @throws runtime_error if could not generate new vertex array object
 * @see @ref fromId
 */
VertexArrayObject VertexArrayObject::generate() {

    // Generate vertex array object
    GLuint id;
    glGenVertexArrays(1, &id);

    // Check if generated correctly
    if (id <= 0) {
        throw runtime_error("[VertexArrayObject] Could not generate vertex array object!");
    }

    // Return handle
    return VertexArrayObject(id);
}

/**
 * Returns the internal OpenGL identifier of the vertex array object this handle represents.
 *
 * @return Internal OpenGL identifier of the vertex array object this handle represents
 */
GLuint VertexArrayObject::id() const {
    return _id;
}

/**
 * Determines the value of `GL_MAX_VERTEX_ATTRIBS`.
 *
 * @return Value of `GL_MAX_VERTEX_ATTRIBS`
 */
GLint VertexArrayObject::maxVertexAttribs() {
    GLint value;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
    return value;
}

/**
 * Changes which OpenGL vertex array object this handle represents.
 *
 * @param vao Handle to copy identifier from
 * @return Reference to this handle
 */
VertexArrayObject& VertexArrayObject::operator=(const VertexArrayObject& vao) {
    _id = vao._id;
    return (*this);
}

/**
 * Checks if this vertex array object handle represents the same vertex array object as another one.
 *
 * @param vao Vertex array object handle to check
 * @return `true` if the handles represent the same vertex array object
 */
bool VertexArrayObject::operator==(const VertexArrayObject& vao) const {
    return _id == vao._id;
}

/**
 * Checks if this vertex array object handle represents a different vertex array object than another one.
 *
 * @param vao Vertex array object handle to check
 * @return `true` if the handles represent different vertex array objects
 */
bool VertexArrayObject::operator!=(const VertexArrayObject& vao) const {
    return _id != vao._id;
}

/**
 * Checks if this vertex array object handle is less than another one.
 *
 * @param vao Vertex array object handle to compare
 * @return `true` if this handle is less than the other one
 */
bool VertexArrayObject::operator<(const VertexArrayObject& vao) const {
    return _id < vao._id;
}

/**
 * Unbinds the vertex array object represented by this handle.
 *
 * @throws logic_error if vertex array object is not already bound
 * @see @ref bind
 */
void VertexArrayObject::unbind() const {
    if (!bound()) {
        throw logic_error("[VertexArrayObject] Vertex array object is not already bound!");
    }
    glBindVertexArray(0);
}

/**
 * Specifies the location and data format of a vertex array.
 *
 * @param pointer Vertex attribute pointer specifying the location and data format of a vertex array
 * @throws logic_error if vertex array object is not bound, or if a buffer object is not bound to `GL_ARRAY_BUFFER`
 * @throws invalid_argument if vertex attribute pointer is invalid
 * @see @ref enableVertexAttribArray
 */
void VertexArrayObject::vertexAttribPointer(const VertexAttribPointer& pointer) const {

    // Check if bound
    if (!bound()) {
        throw logic_error("[VertexArrayObject] Vertex array object is not currently bound!");
    }

    // Check if a buffer object is bound to the array buffer
    const BufferTarget arrayBuffer = BufferTarget::arrayBuffer();
    if (!arrayBuffer.bound()) {
        throw logic_error("[VertexArrayObject] No buffer object currently bound to GL_ARRAY_BUFFER!");
    }

    // Check index
    if (pointer._index >= maxVertexAttribs()) {
        throw invalid_argument("[VertexArrayObject] Index is greater than or equal to GL_MAX_VERTEX_ATTRIBS");
    }

    // Check size
    if ((pointer._size < 1) || (pointer._size > 4)) {
        throw invalid_argument("[VertexArrayObject] Size must be 1, 2, 3, or 4!");
    }

    // Check type
    switch (pointer._type) {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_HALF_FLOAT:
    case GL_FLOAT:
    case GL_DOUBLE:
        break;
    default:
        throw invalid_argument("[VertexArrayObject] Type is invalid!");
    }

    // Set up pointer
    glVertexAttribPointer(
            pointer._index,
            pointer._size,
            pointer._type,
            pointer._normalized,
            pointer._stride,
            (const GLvoid*) pointer._offset);
}

} /* namespace Gloop */

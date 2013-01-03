/**
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
#ifndef GLOOP_VERTEXATTRIBPOINTER_HXX
#define GLOOP_VERTEXATTRIBPOINTER_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Parameters for a pointer to a vertex array.
 *
 * A _vertex array_ is a sequence of data specifying the values of one or more
 * vertex attributes for a set of vertices.  A _vertex attribute pointer_
 * specifies the location and data format of a vertex array so that it can be
 * used for drawing commands such as `glDrawArrays`.
 *
 * As of OpenGL 3 and 4, _vertex array objects_ store the state of vertex
 * attribute pointers.  Furthermore, all vertex arrays should be stored in
 * buffer objects, in which case the pointer is really a byte offset into the
 * buffer object bound to the `GL_ARRAY_BUFFER` target when
 * `glVertexAttribPointer`, or [vertex-attrib-pointer] is called.
 *
 * Note that this structure does not create or enable a vertex attribute
 * pointer in OpenGL, it only holds the parameters for one.  Pass it to
 * [vertex-attrib-pointer] to actually create the pointer in OpenGL, and then
 * call [enable-vertex-attrib-array] to enable it.  The example below sets up a
 * vertex attribute pointer for a vertex attribute representing position.
 *
 * ~~~
 *     // Bind the vertex array object
 *     myVertexArrayObject.bind();
 *
 *     // Bind the buffer object with the vertex array
 *     Buffer buffer = Buffer::arrayBuffer();
 *     buffer.bind(myBufferObject);
 *
 *     // Find the location of the position attribute
 *     int location = myShaderProgram.attribLocation("Position");
 *     assert (location >= 0);
 *
 *     // Create and enable the vertex attribute pointer
 *     myVertexArrayObject.enableVertexAttribPointer(location);
 *     myVertexArrayObject.vertexAttribPointer(VertexAttribPointer()
 *             .index(location)
 *             .size(3)
 *             .type(GL_FLOAT)
 *             .normalized(GL_FALSE)
 *             .stride(0)
 *             .offset(0));
 *
 *     // Unbind the buffer object
 *     buffer.unbind(bufferObject);
 *
 *     // Unbind the vertex array object until it's needed again
 *     myVertexArrayObject.unbind();
 * ~~~
 *
 * @see @ref VertexArrayObject
 * @see @ref BufferObject
 *
 * [vertex-attrib-pointer]:
 *     @ref VertexArrayObject::vertexAttribPointer
 *     "VertexArrayObject::vertexAttribPointer"
 * [enable-vertex-attrib-array]:
 *     @ref VertexArrayObject::enableVertexAttribArray
 *     "VertexArrayObject::enableVertexAttribArray"
 */
class VertexAttribPointer {
public:
// Methods
    VertexAttribPointer();
    VertexAttribPointer& index(GLuint index);
    VertexAttribPointer& size(GLint size);
    VertexAttribPointer& type(GLenum type);
    VertexAttribPointer& normalized(GLboolean normalized);
    VertexAttribPointer& stride(GLsizei stride);
    VertexAttribPointer& offset(GLsizei offset);
private:
// Attributes
    GLuint _index;
    GLint _size;
    GLenum _type;
    GLboolean _normalized;
    GLsizei _stride;
    GLsizei _offset;
// Friends
    friend class VertexArrayObject;
    friend class VertexAttribPointerTest;
};

} /* namespace Gloop */
#endif

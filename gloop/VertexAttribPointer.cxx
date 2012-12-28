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
#include "config.h"
#include "gloop/VertexAttribPointer.hxx"
namespace Gloop {

/**
 * Initializes all the parameters to their default values.
 */
VertexAttribPointer::VertexAttribPointer() {
   _index = 0;
   _size = 4;
   _type = GL_FLOAT;
   _normalized = GL_FALSE;
   _offset = 0;
}

/**
 * Specifies the index of the vertex attribute in the shader program used to render the vertex array.
 *
 * Users should find the index using `glGetAttribLocation` or set it
 * explicitly using `glBindAttribLocation` before the program is linked.
 * Values should range from zero to one minus `GL_MAX_VERTEX_ATTRIBS`, which
 * should be at least sixteen.
 *
 * Note here _index_ and _location_ are used interchangeably.
 *
 * By default _index_ is set to zero.
 *
 * @param index Index of the vertex attribute in the shader program used to render the vertex array
 * @return Reference to this _VertexAttribPointer_ to support chaining
 */
VertexAttribPointer& VertexAttribPointer::index(const GLuint index) {
    this->_index = index;
    return (*this);
}

/**
 * Specifies the number of values specified for each vertex in the vertex array, in the range one to four.
 *
 * Users should specify how many scalar values per vertex they are supplying
 * for the vertex attribute, not necessarily the number of components
 * declared to be in the vertex attribute in the shader, since OpenGL will
 * fill in any missing components with either a one or a zero.
 *
 * For example, a user might declare a vertex attribute with `vec4` in her
 * shader but only pass in three values for each vertex, letting OpenGL fill
 * in a one for the fourth component.  In that case, she should use three
 * for _size_, not four.
 *
 * By default _size_ is set to four.
 *
 * @param size Number of values specified for each vertex in the vertex array, in the range one to four
 * @return Reference to this _VertexAttribPointer_ to support chaining
 */
VertexAttribPointer& VertexAttribPointer::size(const GLint size) {
    this->_size = size;
    return (*this);
}

/**
 * Specifies the data type of each value in the vertex array.
 *
 * Users should specify the primitive data type for each scalar value they
 * are supplying in the vertex array.  Generally the user will specify one
 * of `GL_BYTE`, `GL_UNSIGNED_BYTE`, `GL_SHORT`, `GL_UNSIGNED_SHORT`,
 * `GL_INT`, `GL_UNSIGNED_INT`, `GL_HALF_FLOAT`, `GL_FLOAT`, or `GL_DOUBLE`.
 *
 * Note the data type may be different than what is declared in the shader,
 * since OpenGL can convert the values automatically.  For example, one may
 * supply a vertex array of shorts, but have OpenGL convert them to floats
 * internally.
 *
 * By default _type_ is set to `GL_FLOAT`.
 *
 * @param type Data type of each value in the vertex array
 * @return Reference to this _VertexAttribPointer_ to support chaining
 */
VertexAttribPointer& VertexAttribPointer::type(const GLenum type) {
    this->_type = type;
    return (*this);
}

/**
 * Specifies whether fixed-point values should be normalized, by default `GL_FALSE`.
 *
 * @param normalized Whether fixed-point values should be normalized, by default `GL_FALSE`
 * @return Reference to this _VertexAttribPointer_ to support chaining
 */
VertexAttribPointer& VertexAttribPointer::normalized(const GLboolean normalized) {
    this->_normalized = normalized;
    return (*this);
}

/**
 * Specifies the byte offset between the values of consecutive vertices for the vertex attribute.
 *
 * Normally the values for different vertex attributes are stored in
 * separate vertex arrays.  There is one for positions, one for normals,
 * another for texture coordinates, and so on.  Or if the values are in the
 * same array, they are stored separately with all the values for one vertex
 * attribute together, followed by all the values for the second, and so on.
 * These types of vertex arrays are called _tightly-packed_.  The diagram
 * below shows the format of a tightly-packed vertex array for a simple
 * triangle with three vertices.
 *
 *     POSITION FOR FIRST VERTEX
 *     POSITION FOR SECOND VERTEX
 *     POSITION FOR THIRD VERTEX
 *     NORMAL FOR FIRST VERTEX
 *     NORMAL FOR SECOND VERTEX
 *     NORMAL FOR THIRD VERTEX
 *     TEXTURE COORDINATE FOR FIRST VERTEX
 *     TEXTURE COORDINATE FOR SECOND VERTEX
 *     TEXTURE COORDINATE FOR THIRD VERTEX
 *
 * However, putting more than one vertex attribute in the same vertex array
 * so that all the values for each vertex are together may improve
 * performance.  The graphics card no longer has to jump around in memory to
 * get all the values for each vertex.  When a vertex array holds the values
 * of multiple vertex attributes, it is said to be _interleaved_.  The
 * diagram below shows the format of an interleaved vertex array for the
 * same simple triangle with three vertices.
 *
 *     POSITION FOR FIRST VERTEX
 *     NORMAL FOR FIRST VERTEX
 *     TEXTURE COORDINATE FOR FIRST VERTEX
 *     POSITION FOR SECOND VERTEX
 *     NORMAL FOR SECOND VERTEX
 *     TEXTURE COORDINATE FOR SECOND VERTEX
 *     POSITION FOR THIRD VERTEX
 *     NORMAL FOR THIRD VERTEX
 *     TEXTURE COORDINATE FOR THIRD VERTEX
 *
 * If a user is using interleaved vertex arrays, she should specify the byte
 * offset required to skip to the values of the next vertex for the same
 * vertex attribute.  The offset should include the size of the values for
 * the vertex attribute itself, not just the size of those of the other
 * vertex attributes.
 *
 * In the example above, assuming three values make up each position, three
 * values make up each normal, and two values make up each texture
 * coordinate, and that a float is four bytes, the user would specify a byte
 * offset of thirty-two bytes.  The values for the position attribute take
 * up twelve bytes, the values for the normal attribute take up another
 * twelve bytes, and the values for the texture attribute take up another
 * eight bytes.  Generally the stride should be the same for each vertex
 * attribute in an interleaved vertex array.
 *
 * If this vertex attribute pointer does not point to an interleaved vertex
 * array, the user should specify a _stride_ of zero, indicating the vertex
 * array is tightly-packed.
 *
 * By default _stride_ is set to zero.
 *
 * @param stride Byte offset between the values of consecutive vertices for the vertex attribute
 * @return Reference to this _VertexAttribPointer_ to support chaining
 */
VertexAttribPointer& VertexAttribPointer::stride(const GLsizei stride) {
    this->_stride = stride;
    return (*this);
}

/**
 * Specifies the offset of the vertex array in the buffer object currently bound to the `GL_ARRAY_BUFFER` target.
 *
 * With the OpenGL 3 and 4 core profiles, vertex arrays must now be stored
 * in a buffer object.  Instead of specifying an actual pointer to an array
 * in system memory, the user now specifies a byte offset into the buffer
 * object bound to the `GL_ARRAY_BUFFER` target when
 * `glVertexAttribPointer`, or [vertex-attrib-pointer] is called.
 *
 * Furthermore, the vertex attribute pointer, including which buffer object
 * it was pointing to, will be stored in the vertex array object that was
 * active at that time.  From then on, the buffer object need not be bound,
 * and other vertex attribute pointers may point to other buffer objects.
 *
 * [vertex-attrib-pointer]:
 *     @ref VertexArrayObject::vertexAttribPointer
 *     "VertexArrayObject::vertexAttribPointer"
 *
 * @param offset Offset of the vertex array in the buffer object currently bound to the `GL_ARRAY_BUFFER` target
 * @return Reference to this _VertexAttribPointer_ to support chaining
 */
VertexAttribPointer& VertexAttribPointer::offset(const GLsizei offset) {
    this->_offset = offset;
    return (*this);
}

} /* namespace Gloop */

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
#ifndef GLOOP_VERTEXARRAYOBJECT_HXX
#define GLOOP_VERTEXARRAYOBJECT_HXX
#include "gloop/common.h"
#include "gloop/VertexAttribPointer.hxx"
#include "gloop/BufferTarget.hxx"
namespace Gloop {


/**
 * Handle for an OpenGL Vertex Array Object.
 *
 * A _vertex array_ is a sequence of data specifying the values of one or more
 * vertex attributes for a set of vertices.  A _vertex attribute pointer_
 * specifies the location and data format of a vertex array, and a _vertex array
 * object_ stores the state of those pointers.  The state can be switched
 * quickly by changing which vertex array object is bound.
 *
 * To use _VertexArrayObject_, first generate a new one.
 *
 * ~~~
 *     VertexArrayObject myVertexArrayObject = VertexArrayObject::generate();
 * ~~~
 *
 * Then activate the vertex array object by binding it.
 *
 * ~~~
 *     myVertexArrayObject.bind();
 * ~~~
 *
 * Note that as of OpenGL 3, all vertex arrays should be stored in a buffer
 * object, so we bind the one with our vertex array in it, assuming we've
 * already uploaded it.  The buffer object must be bound as the
 * `GL_ARRAY_BUFFER` when we set up the pointers, although after that it can be
 * unbound.
 *
 * ~~~
 *     BufferTarget arrayBuffer = Buffer::arrayBuffer();
 *     arrayBuffer.bind(myBufferObject);
 * ~~~
 *
 * Next, set up a pointer to the vertex array.  Here we use
 * _VertexAttribPointer_ to specify the parameters and then pass it to @ref
 * vertexAttribPointer.  See @ref VertexAttribPointer for more information
 * about each of the parameters.
 *
 * ~~~
 *     VertexAttribPointer pointer;
 *     pointer.index = myShaderProgram.attribLocation("Position");
 *     pointer.size = 3;
 *     pointer.type = GL_FLOAT;
 *     pointer.offset = 0;
 *     vao.vertexAttribPointer(pointer);
 * ~~~
 *
 * Now that the pointer is set up, we don't need to keep the buffer object
 * bound.  The vertex array object will remember it.
 *
 * ~~~
 *     arrayBuffer.unbind(myBufferObject);
 * ~~~
 *
 * Next, we'll enable the vertex array while we still have the index.  Even with
 * the pointer set up, the vertex array needs to be enabled or it won't be used.
 *
 * ~~~
 *     vao.enableVertexAttribArray(pointer.index);
 * ~~~
 *
 * From there, repeat the process with other vertex arrays, then unbind the
 * vertex array object until you need to use it for rendering, or to change it
 * again later.
 *
 * ~~~
 *     vao.unbind();
 * ~~~
 */
class VertexArrayObject {
public:
// Methods
    VertexArrayObject(const VertexArrayObject& vao);
    ~VertexArrayObject();
    void bind() const;
    bool bound() const;
    void disableVertexAttribArray(GLuint index) const;
    void dispose() const;
    void enableVertexAttribArray(GLuint index) const;
    static VertexArrayObject fromId(GLuint id);
    static VertexArrayObject generate();
    GLuint id() const;
    VertexArrayObject& operator=(const VertexArrayObject& vao);
    bool operator==(const VertexArrayObject& vao) const;
    bool operator!=(const VertexArrayObject& vao) const;
    bool operator<(const VertexArrayObject& vao) const;
    void unbind() const;
    void vertexAttribPointer(const VertexAttribPointer& pointer) const;
private:
// Attributes
    GLuint _id;
// Methods
    VertexArrayObject();
    explicit VertexArrayObject(GLuint id);
    static int maxVertexAttribs();
};

} /* namespace Gloop */
#endif

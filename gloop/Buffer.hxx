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
#ifndef GLOOP_BUFFER_HXX
#define GLOOP_BUFFER_HXX
#include "gloop/common.h"
#include "gloop/BufferObject.hxx"
namespace Gloop {


/**
 * Handle for one of the OpenGL buffers.
 *
 * To use _Buffer_, first get a handle to one of the standard OpenGL buffers.
 * Unless you're planning to change what buffer it represents, the handle can
 * be marked `const` because it's just an alias, similar to a reference or
 * pointer, not the actual buffer itself.
 *
 * ~~~
 *     const Buffer buf = Buffer::arrayBuffer();
 * ~~~
 *
 * Next, bind a buffer object to it.  Despite the name, conceptually a buffer
 * object is just a data store for one of the standard OpenGL buffers.  When you
 * bind a buffer object to one of the buffers, you're just changing the state of
 * where that buffer points to in memory.  Doing so allows us to quickly swap
 * out the contents of one the buffers, rather than copying data in every time.
 * In the example below, we generate a new buffer object for the buffer.
 *
 * ~~~
 *    const BufferObject bo = BufferObject::generate();
 *    buf.bind(bo);
 * ~~~
 *
 * After that, fill the buffer with the data you want to use.  You need to give
 * it a pointer to the data, the size of that data, and a hint on how to use
 * that data, e.g. `GL_STATIC_DRAW` or `GL_STREAM_DRAW`.
 *
 * ~~~
 *    float arr[][] = { { +1, +1 }, { -1, +1 }, { -1, -1 } };
 *    buf.data(sizeof(arr), arr, GL_STATIC_DRAW);
 * ~~~
 *
 * Finally, set up any state or perform operations that will use the data
 * currently in the buffer, such as establishing and enabling a vertex attribute
 * pointer in a Vertex Array Object.  When you're finished, the buffer object
 * should be unbound from the buffer.
 *
 * ~~~
 *    buf.unbind(bo);
 * ~~~
 */
class Buffer {
public:
// Methods
    Buffer(const Buffer& bt);
    ~Buffer();
    void bind(const BufferObject& bo) const;
    bool bound() const;
    bool bound(const BufferObject& bo) const;
    void data(GLsizeiptr size, const GLvoid* data, GLenum usage) const;
    Buffer& operator=(const Buffer& bt);
    bool operator==(const Buffer& bt) const;
    bool operator!=(const Buffer& bt) const;
    bool operator<(const Buffer& bt) const;
    void subData(GLintptr offset, GLsizeiptr size, const GLvoid* data) const;
    void unbind(const BufferObject& bo) const;
// Instances
    static Buffer arrayBuffer();
    static Buffer copyReadBuffer();
    static Buffer copyWriteBuffer();
    static Buffer elementArrayBuffer();
    static Buffer pixelPackBuffer();
    static Buffer pixelUnpackBuffer();
    static Buffer textureBuffer();
    static Buffer transformFeedbackBuffer();
    static Buffer uniformBuffer();
private:
// Attributes
    GLenum _name;
    GLenum _binding;
// Methods
    Buffer();
    Buffer(GLenum name, GLenum lookup);
    GLuint binding() const;
};

} /* namespace Gloop */
#endif

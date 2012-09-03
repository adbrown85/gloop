/*
 * Buffer.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_BUFFER_HPP
#define GLYCERIN_BUFFER_HPP
#include "glycerin/common.h"
#include "glycerin/buffer/BufferObject.hpp"
namespace Glycerin {


/**
 * Handle for one of the OpenGL buffers.
 *
 * To use <i>Buffer</i>, first get a handle to one of the standard OpenGL
 * buffers.  Unless you're planning to change what buffer it represents, the
 * handle can be marked const because it's just an alias, similar to a reference
 * or pointer, not the actual buffer itself.
 *
 * @code
 *     const Buffer buf = Buffer::arrayBuffer();
 * @endcode
 *
 * Next, bind a buffer object to it.  Despite the name, conceptually a buffer
 * object is just a data store for one of the standard OpenGL buffers.  When you
 * bind a buffer object to one of the buffers, you're just changing the state of
 * where that buffer points to in memory.  Doing so allows us to quickly swap
 * out the contents of one the buffers, rather than copying data in every time.
 * In the example below, we generate a new buffer object for the buffer.
 *
 * @code
 *    const BufferObject bo = BufferObject::generate();
 *    buf.bind(bo);
 * @endcode
 *
 * After that, fill the buffer with the data you want to use.  You need to give
 * it a pointer to the data, the size of that data, and a hint on how to use
 * that data, e.g. <tt>GL_STATIC_DRAW</tt> or <tt>GL_STREAM_DRAW</tt>.
 *
 * @code
 *    float arr[][] = { { +1, +1 }, { -1, +1 }, { -1, -1 } };
 *    buf.data(sizeof(arr), arr, GL_STATIC_DRAW);
 * @endcode
 *
 * Finally, set up any state or perform operations that will use the data
 * currently in the buffer, such as establishing and enabling a vertex attribute
 * pointer in a Vertex Array Object.  When you're finished, the buffer object
 * should be unbound from the buffer.
 *
 * @code
 *    buf.unbind(bo);
 * @endcode
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

} /* namespace Glycerin */
#endif

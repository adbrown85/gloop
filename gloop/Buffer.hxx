/*
 * Buffer.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
 *
 * @ingroup core
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

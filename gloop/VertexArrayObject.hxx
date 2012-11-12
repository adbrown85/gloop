/*
 * VertexArrayObject.hxx
 *
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_VERTEXARRAYOBJECT_HXX
#define GLOOP_VERTEXARRAYOBJECT_HXX
#include "gloop/common.h"
#include "gloop/VertexAttribPointer.hxx"
#include "gloop/Buffer.hxx"
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
 *     Buffer arrayBuffer = Buffer::arrayBuffer();
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
 *
 * @ingroup core
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

/**
 * VertexAttribPointer.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
 *     // Specify the parameters for the vertex attribute pointer
 *     VertexAttribPointer pointer;
 *     pointer.index = location;
 *     pointer.size = 3;
 *     pointer.type = GL_FLOAT;
 *     pointer.normalized = GL_FALSE;
 *     pointer.stride = 0;
 *     pointer.offset = 0;
 *
 *     // Create and enable the vertex attribute pointer
 *     myVertexArrayObject.vertexAttribPointer(pointer);
 *     myVertexArrayObject.enableVertexAttribPointer(location);
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
 *
 * @ingroup core
 */
struct VertexAttribPointer {

   VertexAttribPointer();

   /**
    * Index of the vertex attribute in the shader program used to render the vertex array.
    *
    * Users should find the index using `glGetAttribLocation` or set it
    * explicitly using `glBindAttribLocation` before the program is linked.
    * Values should range from zero to one minus `GL_MAX_VERTEX_ATTRIBS`, which
    * should be at least sixteen.
    *
    * Note here _index_ and _location_ are used interchangeably.
    *
    * By default _index_ is set to zero.
    */
   GLuint index;

   /**
    * Number of values specified for each vertex in the vertex array, in the range one to four.
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
    */
   GLint size;

   /**
    * Data type of each value in the vertex array.
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
    */
   GLenum type;

   /**
    * Whether fixed-point values should be normalized, by default `GL_FALSE`.
    */
   GLboolean normalized;

   /**
    * Byte offset between the values of consecutive vertices for the vertex attribute.
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
    */
   GLsizei stride;

   /**
    * Offset of the vertex array in the buffer object currently bound to the `GL_ARRAY_BUFFER` target.
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
    */
   GLsizei offset;
};

} /* namespace Gloop */
#endif

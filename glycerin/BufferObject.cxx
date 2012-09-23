/*
 * BufferObject.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include <stdexcept>
#include "glycerin/BufferObject.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs an invalid buffer object handle.
 */
BufferObject::BufferObject() {
    throw runtime_error("[BufferObject] Default constructor should not be called!");
}

/**
 * Constructs a buffer object handle from the identifer of an OpenGL buffer object.
 *
 * @param id Identifier of OpenGL buffer object, previously created using glGenBuffers
 */
BufferObject::BufferObject(GLuint id) : _id(id) {
    assert (_id > 0);
}

/**
 * Constructs a buffer object handle representing the same OpenGL buffer object as another one.
 *
 * @param bo Handle for buffer object to copy identifier from
 */
BufferObject::BufferObject(const BufferObject& bo) : _id(bo._id) {
    // pass
}

/**
 * Destructs a buffer object handle, leaving the corresponding OpenGL buffer object unaffected.
 *
 * @see @ref dispose
 */
BufferObject::~BufferObject() {
    // pass
}

/**
 * Deletes the OpenGL buffer object this handle represents.
 */
void BufferObject::dispose() const {
    glDeleteBuffers(1, &_id);
}

/**
 * Returns the identifer of the OpenGL buffer object this handle represents.
 */
GLuint BufferObject::id() const {
    return _id;
}

/**
 * Creates a buffer object handle representing a new OpenGL buffer object.
 *
 * @return Handle for new OpenGL buffer object
 * @throws std::runtime_error if could not generate a new OpenGL buffer object
 */
BufferObject BufferObject::generate() {

    // Make an OpenGL buffer object
    GLuint id;
    glGenBuffers(1, &id);
    if (id <= 0) {
        throw runtime_error("[BufferObject] Could not generate new buffer object!");
    }

    // Make the handle
    return BufferObject(id);
}

/**
 * Changes which OpenGL buffer object this handle represents.
 *
 * @param bo Handle for buffer object to copy identifier from
 * @return Reference to this handle
 */
BufferObject& BufferObject::operator=(const BufferObject& bo) {
    _id = bo._id;
    return (*this);
}

/**
 * Checks if another handle represents the same OpenGL buffer object as this one.
 *
 * @param bo Other buffer object handle to check
 * @return `true` if the other handle represents the same OpenGL buffer object
 */
bool BufferObject::operator==(const BufferObject& bo) const {
    return _id == bo._id;
}

/**
 * Checks if another handle does not represent the same OpenGL buffer object as this one.
 *
 * @param bo Other buffer object handle to check
 * @return `true` if the other handle does not represent the same OpenGL buffer object
 */
bool BufferObject::operator!=(const BufferObject& bo) const {
    return _id != bo._id;
}

/**
 * Compares the identifier of this handle's OpenGL buffer object to that of another one.
 *
 * @param bo Handle for buffer object to compare to
 * @return `true` if this handle's identifier is less than the other one's
 */
bool BufferObject::operator<(const BufferObject& bo) const {
    return _id < bo._id;
}

/**
 * Creates a buffer object handle representing an existing OpenGL buffer object.
 *
 * @param id Identifier of existing OpenGL buffer object to represent
 * @return Resulting buffer object handle
 * @throws std::invalid_argument if identifier is not an existing OpenGL buffer object
 */
BufferObject BufferObject::wrap(const GLuint id) {
    if (!glIsBuffer(id)) {
        throw invalid_argument("[BufferObject] ID is not an OpenGL buffer object!");
    }
    return BufferObject(id);
}

} /* namespace Glycerin */

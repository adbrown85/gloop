/*
 * BufferRegion.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include "glycerin/BufferRegion.hpp"
using namespace std;
namespace Glycerin {

/**
 * Returns the number of components per vector in the region, in the range one to four.
 */
GLsizei BufferRegion::components() const {
    return _components;
}

/**
 * Returns the total number of vectors in the region, numbering at least one.
 */
GLuint BufferRegion::count() const {
    return _count;
}

/**
 * Returns the name of the region.
 */
string BufferRegion::name() const {
    return _name;
}

/**
 * Returns whether vector components in the region should be normalized.
 */
bool BufferRegion::normalized() const {
    return _normalized;
}

/**
 * Returns the number of bytes before the first vector in the region.
 */
GLsizei BufferRegion::offset() const {
    return _offset;
}

/**
 * Returns the number of bytes between consecutive vectors in the region.
 */
GLsizei BufferRegion::stride() const {
    return _stride;
}

/**
 * Returns the base type of the components in each vector in the region, such as `GL_FLOAT`.
 */
GLenum BufferRegion::type() const {
    return _type;
}

} /* namespace Glycerin */

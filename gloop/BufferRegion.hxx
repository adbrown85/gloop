/*
 * BufferRegion.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_BUFFERREGION_HXX
#define GLOOP_BUFFERREGION_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Section in a buffer.
 *
 * @ingroup extensions
 */
class BufferRegion {
public:
// Methods
    GLsizei components() const;
    GLuint count() const;
    std::string name() const;
    bool normalized() const;
    GLsizei offset() const;
    GLsizei stride() const;
    GLenum type() const;
private:
// Attributes
    GLsizei _components;
    GLuint _count;
    std::string _name;
    bool _normalized;
    GLsizei _offset;
    GLsizei _stride;
    GLenum _type;
// Friends
    friend class BufferLayout;
    friend class BufferLayoutBuilder;
};

} /* namespace Gloop */
#endif

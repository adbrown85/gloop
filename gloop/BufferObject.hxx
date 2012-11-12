/*
 * BufferObject.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_BUFFEROBJECT_HXX
#define GLOOP_BUFFEROBJECT_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Handle for an OpenGL buffer object.
 */
class BufferObject {
public:
// Methods
    BufferObject(const BufferObject& bo);
    ~BufferObject();
    void dispose() const;
    static BufferObject fromId(GLuint id);
    static BufferObject generate();
    GLuint id() const;
    BufferObject& operator=(const BufferObject& bo);
    bool operator==(const BufferObject& bo) const;
    bool operator!=(const BufferObject& bo) const;
    bool operator<(const BufferObject& bo) const;
private:
// Attributes
    GLuint _id;
// Methods
    BufferObject();
    explicit BufferObject(GLuint id);
};

} /* namespace Gloop */
#endif

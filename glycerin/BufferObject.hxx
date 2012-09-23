/*
 * BufferObject.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_BUFFEROBJECT_HPP
#define GLYCERIN_BUFFEROBJECT_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Handle for an OpenGL buffer object.
 */
class BufferObject {
public:
// Methods
    BufferObject(const BufferObject& bo);
    ~BufferObject();
    void dispose() const;
    static BufferObject generate();
    GLuint id() const;
    BufferObject& operator=(const BufferObject& bo);
    bool operator==(const BufferObject& bo) const;
    bool operator!=(const BufferObject& bo) const;
    bool operator<(const BufferObject& bo) const;
    static BufferObject wrap(GLuint id);
private:
// Attributes
    GLuint _id;
// Methods
    BufferObject();
    explicit BufferObject(GLuint id);
};

} /* namespace Glycerin */
#endif

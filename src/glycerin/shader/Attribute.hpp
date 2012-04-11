/*
 * Attribute.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_ATTRIBUTE_HPP
#define GLYCERIN_ATTRIBUTE_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * OpenGL vertex attribute.
 */
struct Attribute {
public:
    std::string name;
    GLint size;
    GLenum type;
};

} /* namespace Glycerin */
#endif

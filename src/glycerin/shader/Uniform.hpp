/*
 * Uniform.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_UNIFORM_HPP
#define GLYCERIN_UNIFORM_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * OpenGL uniform information.
 */
struct Uniform {
public:
    std::string name;
    GLint size;
    GLenum type;
};

} /* namespace Glycerin */
#endif

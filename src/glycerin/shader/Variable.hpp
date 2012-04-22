/*
 * Variable.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_VARIABLE_HPP
#define GLYCERIN_VARIABLE_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Input to a shader program.
 */
struct Variable {
public:
    std::string name;
    GLint size;
    GLenum type;
};

} /* namespace Glycerin */
#endif

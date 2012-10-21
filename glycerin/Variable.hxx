/*
 * Variable.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_VARIABLE_HXX
#define GLYCERIN_VARIABLE_HXX
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Input to a shader program.
 *
 * @ingroup core
 */
struct Variable {
public:
    std::string name;
    GLint size;
    GLenum type;
    GLint location;
    GLuint program;
};

} /* namespace Glycerin */
#endif

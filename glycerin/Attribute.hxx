/*
 * Attribute.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_ATTRIBUTE_HXX
#define GLYCERIN_ATTRIBUTE_HXX
#include "glycerin/common.h"
#include "glycerin/Variable.hxx"
namespace Glycerin {


/**
 * OpenGL vertex attribute.
 *
 * @ingroup core
 */
class Attribute : public Variable {
// Friends
    friend class Program;
private:
// Methods
    Attribute(GLint location, const std::string& name, GLuint program, GLint size, GLenum type);
};

} /* namespace Glycerin */
#endif

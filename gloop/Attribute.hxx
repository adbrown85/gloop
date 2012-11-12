/*
 * Attribute.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_ATTRIBUTE_HXX
#define GLOOP_ATTRIBUTE_HXX
#include "gloop/common.h"
#include "gloop/Variable.hxx"
namespace Gloop {


/**
 * OpenGL vertex attribute.
 */
class Attribute : public Variable {
// Friends
    friend class Program;
private:
// Methods
    Attribute(GLint location, const std::string& name, GLuint program, GLint size, GLenum type);
};

} /* namespace Gloop */
#endif

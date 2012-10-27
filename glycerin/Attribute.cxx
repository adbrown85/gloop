/*
 * Attribute.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/Attribute.hxx"
namespace Glycerin {

/**
 * Constructs an attribute.
 *
 * @param location Location in program
 * @param name Name of attribute in shader
 * @param program ID of the program attribute is from
 * @param size Number of components
 * @param type Data type of components, as in `GL_FLOAT`
 */
Attribute::Attribute(GLint location,
                     const std::string& name,
                     GLuint program,
                     GLint size,
                     GLenum type)
        : Variable(location, name, program, size, type) {
    // empty
}

} /* namespace Glycerin */

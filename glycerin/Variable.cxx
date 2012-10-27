/*
 * Variable.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/Variable.hxx"
namespace Glycerin {

/**
 * Constructs a variable.
 *
 * @param location Location in program
 * @param name Name of variable in shader
 * @param program ID of the program variable is from
 * @param size Number of components
 * @param type Data type of components, as in `GL_FLOAT`
 */
Variable::Variable(GLint location,
                   const std::string& name,
                   GLuint program,
                   GLint size,
                   GLenum type) {
   this->_location = location;
   this->_name = name;
   this->_program = program;
   this->_size = size;
   this->_type = type;
}

/**
 * Destructs a variable.
 */
Variable::~Variable() {
    // empty
}

/**
 * Retrieves the location of this variable in the program it is from.
 *
 * @return Location of this variable in the program it is from
 */
GLint Variable::location() const {
    return _location;
}

/**
 * Retrieves the name of this variable in the shader it is from.
 *
 * @return Name of this variable in the shader it is from
 */
std::string Variable::name() const {
    return _name;
}


/**
 * Retrieves the ID of the program this variable is from.
 *
 * @return ID of the program this variable is from
 */
GLuint Variable::program() const {
   return _program;
}

/**
 * Retrieves the number of components in this variable.
 *
 * @return Number of components in this variable
 */
GLint Variable::size() const {
   return _size;
}

/**
 * Retrieves the data type of this variable, as in `GL_FLOAT`.
 *
 * @return Data type of this variable, as in `GL_FLOAT`
 */
GLenum Variable::type() const {
   return _type;
}

} /* namespace Glycerin */

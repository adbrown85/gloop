/*
 * Program.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include "glycerin/shader/Program.hpp"
using namespace std;
namespace Glycerin {

/**
 * Constructs a new program.
 *
 * @throws std::runtime_error if program could not be created
 */
Program::Program() : _handle(glCreateProgram()) {
    if (_handle == 0) {
        throw runtime_error("[Program] Could not create program!");
    }
}

/**
 * Constructs a program wrapping an existing shader program.
 *
 * @param handle Existing shader program to wrap
 * @throws invalid_argument if handle is <tt>null</tt>
 */
Program::Program(GLuint handle) : _handle(handle) {
    if (!glIsProgram(_handle)) {
        throw invalid_argument("[Program] Handle is not a valid shader program!");
    }
}

/**
 * Construcs a program by copying another program.
 *
 * @param program Program to copy
 */
Program::Program(const Program& program) : _handle(program._handle) {
    // pass
}

/**
 * Attaches a shader to the program.
 *
 * @param shader OpenGL identifier for the shader to attach
 * @throw std::invalid_argument if shader is not valid
 */
void Program::attachShader(GLuint shader) {
    if (!glIsShader(shader)) {
        throw invalid_argument("[Program] Not a valid shader!");
    }
    glAttachShader(_handle, shader);
}

/**
 * Determines the location of an attribute.
 *
 * @param name Name of attribute
 * @throws invalid_argument if name empty
 * @throws runtime_error if program has not been linked yet
 */
GLuint Program::attribLocation(const string &name) const {

    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (!linked()) {
        throw runtime_error("[Program] Program not linked yet!");
    }

    return glGetAttribLocation(_handle, name.c_str());
}

/**
 * Binds an attribute to a specific location.
 *
 * @param name Name of attribute
 * @param location Location to bind to
 * @throw invalid_argument if name is empty
 */
void Program::attribLocation(const string& name, GLuint location) {
    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    }
    glBindAttribLocation(_handle, location, name.c_str());
}

/**
 * Returns all the attributes in the program.
 */
vector<Attribute> Program::attributes() const {

    // Get number of active attributes
    GLint num;
    glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &num);
    if (num == 0) {
        return vector<Attribute>(0);
    }

    // Make a buffer to hold name of an attribute
    GLint len;
    glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &len);
    char* const buf = new char[len];

    // Put active attributes into an array
    vector<Attribute> attribs;
    for (int i = 0; i < num; ++i) {
        Attribute attrib;
        glGetActiveAttrib(_handle, i, len, NULL, &attrib.size, &attrib.type, buf);
        attrib.name = buf;
        attribs.push_back(attrib);
    }

    // Delete the buffer
    delete[] buf;

    // Return the vector
    return attribs;
}

/**
 * Detaches a shader from the program.
 *
 * @param shader Shader to detach
 * @throws invalid_argument if shader is not a valid shader
 */
void Program::detachShader(GLuint shader) {
    if (!glIsShader(shader)) {
        throw invalid_argument("[Program] Not a valid shader!");
    }
    glDetachShader(_handle, shader);
}

/**
 * Deletes the underlying OpenGL shader program.
 */
void Program::dispose() {
    glDeleteProgram(_handle);
}

/**
 * Returns the location of an output variable.
 *
 * @param name Name of output variable
 * @return Location of output variable, or -1 if name is not an active output variable
 */
GLint Program::fragDataLocation(const string& name) const {
    return glGetFragDataLocation(_handle, name.c_str());
}

/**
 * Binds a fragment shader output variable to a location.
 *
 * @param name Name of output variable to bind
 * @param location Location of draw buffer to bind to
 * @throws invalid_argument if location greater than GL_MAX_DRAW_BUFFERS
 * @throws invalid_argument if name is empty or starts with 'gl_'
 */
void Program::fragDataLocation(const string &name, GLuint location) {

    if (location > getMaxDrawBuffers()) {
        throw invalid_argument("[Program] Location greater than GL_MAX_DRAW_BUFFERS");
    } else if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (name.find("gl_") == 0) {
        throw invalid_argument("[Program] Name starts with 'gl_'");
    }

    glBindFragDataLocation(_handle, location, name.c_str());
}

/**
 * Returns the OpenGL indentifier for the program.
 */
GLuint Program::handle() const {
    return _handle;
}

/**
 * Links the program.
 */
void Program::link() {
    glLinkProgram(_handle);
}

/**
 * Returns <tt>true</tt> if program is linked.
 */
bool Program::linked() const {
    GLint linked;
    glGetProgramiv(_handle, GL_LINK_STATUS, &linked);
    return linked;
}

/**
 * Returns the program's log.
 */
string Program::log() const {

    // Make a buffer big enough to hold the log
    GLint len;
    glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &len);
    GLchar* const buf = new GLchar[len + 1];

    // Put the log into the buffer
    GLint num;
    glGetProgramInfoLog(_handle, len, &num, buf);
    buf[num] = '\0';

    // Make a string from the buffer and then delete it
    string str(buf);
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Returns all the shaders attached to the program.
 */
vector<GLuint> Program::shaders() const {

    // Determine how many shaders are attached
    GLint len;
    glGetProgramiv(_handle, GL_ATTACHED_SHADERS, &len);
    if (len == 0) {
        return vector<GLuint>();
    }

    // Put attached shaders into array
    GLuint* const arr = new GLuint[len];
    glGetAttachedShaders(_handle, len, NULL, arr);

    // Add them to a vector
    vector<GLuint> vec;
    for (int i = 0; i < len; ++i) {
        vec.push_back(arr[i]);
    }

    // Delete the array
    delete[] arr;

    // Return the vector
    return vec;
}

/**
 * Returns the names of all the active uniforms in the program.
 */
vector<Uniform> Program::uniforms() const {

    // Get number of active uniforms
    GLint num;
    glGetProgramiv(_handle, GL_ACTIVE_UNIFORMS, &num);
    if (num == 0) {
        return vector<Uniform>(0);
    }

    // Make a buffer to hold name of a uniform
    GLint len;
    glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &len);
    char* const buf = new char[len];

    // Put active uniforms into an array
    vector<Uniform> uniforms;
    for (int i = 0; i < num; ++i) {
        Uniform uniform;
        glGetActiveUniform(_handle, i, len, NULL, &uniform.size, &uniform.type, buf);
        uniform.name = buf;
        uniforms.push_back(uniform);
    }

    // Delete the buffer
    delete[] buf;

    // Return the vector
    return uniforms;
}

/**
 * Activates the program.
 */
void Program::use() const {
    glUseProgram(_handle);
}

/**
 * Checks if the program is valid.
 */
bool Program::valid() const {
    GLint valid;
    glGetProgramiv(_handle, GL_VALIDATE_STATUS, &valid);
    return valid;
}

/**
 * Ensures the program is valid.
 */
void Program::validate() {
    glValidateProgram(_handle);
}

// HELPERS

/**
 * Returns the value of GL_MAX_DRAW_BUFFERS.
 */
GLint Program::getMaxDrawBuffers() {
    GLint value;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &value);
    return value;
}

} /* namespace Glycerin */

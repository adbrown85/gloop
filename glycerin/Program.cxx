/*
 * Program.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include "glycerin/Program.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs a program wrapping an existing shader program.
 *
 * @param id ID of existing shader program to wrap
 * @throws invalid_argument if ID is not an existing OpenGL shader program
 */
Program::Program(GLuint id) : _id(id) {
    if (!glIsProgram(_id)) {
        throw invalid_argument("[Program] ID not an existing OpenGL shader program!");
    }
}

/**
 * Constructs a program by copying another program.
 *
 * @param program Program to copy
 */
Program::Program(const Program& program) : _id(program._id) {
    // pass
}

/**
 * Returns all the active attributes in this program.
 */
map<string,Attribute> Program::activeAttributes() const {

    // Get number of active attributes
    GLint num;
    glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES, &num);
    if (num == 0) {
        return map<string,Attribute>();
    }

    // Make a buffer to hold name of an attribute
    GLint len;
    glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &len);
    char* const buf = new char[len];

    // Make variables to hold size and type of an attribute
    GLint size;
    GLenum type;

    // Put active attributes into a map
    map<string,Attribute> attribs;
    for (int i = 0; i < num; ++i) {
        glGetActiveAttrib(_id, i, len, NULL, &size, &type, buf);
        const GLint location = glGetAttribLocation(_id, buf);
        const string name = buf;
        const Attribute attrib(location, name, _id, size, type);
        attribs.insert(pair<string,Attribute>(name, attrib));
    }

    // Delete the buffer
    delete[] buf;

    // Return the vector
    return attribs;
}

/**
 * Returns all the active uniforms in this program.
 */
map<string,Uniform> Program::activeUniforms() const {

    // Get number of active uniforms
    GLint num;
    glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &num);
    if (num == 0) {
        return map<string,Uniform>();
    }

    // Make a buffer to hold name of a uniform
    GLint len;
    glGetProgramiv(_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &len);
    char* const buf = new char[len];

    // Make variables to hold size and type of a uniform
    GLint size;
    GLenum type;

    // Put active uniforms into a map
    map<string,Uniform> uniforms;
    for (int i = 0; i < num; ++i) {
        glGetActiveUniform(_id, i, len, NULL, &size, &type, buf);
        const GLint location = glGetUniformLocation(_id, buf);
        const string name = buf;
        const Uniform uniform(location, name, _id, size, type);
        uniforms.insert(pair<string,Uniform>(name, uniform));
    }

    // Delete the buffer
    delete[] buf;

    // Return the vector
    return uniforms;
}

/**
 * Attaches a shader to this program.
 *
 * @param shader OpenGL identifier for the shader to attach
 * @throw std::invalid_argument if shader is not valid
 * @throw std::invalid_argument if shader is already attached
 */
void Program::attachShader(GLuint shader) const {
    attachShader(Shader::wrap(shader));
}

/**
 * Attaches a shader to this program.
 *
 * @param shader Wrapper for an OpenGL shader
 * @throw std::invalid_argument if shader is already attached
 */
void Program::attachShader(const Shader &shader) const {
    if (isAttached(shader)) {
        throw invalid_argument("[Program] Shader is already attached!");
    }
    glAttachShader(_id, shader.id());
}

/**
 * Determines the location of an attribute.
 *
 * @param name Name of attribute
 * @throws invalid_argument if name empty
 * @throws runtime_error if program has not been linked yet
 */
GLint Program::attribLocation(const std::string &name) const {

    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (!linked()) {
        throw runtime_error("[Program] Program not linked yet!");
    }

    return glGetAttribLocation(_id, name.c_str());
}

/**
 * Binds an attribute to a specific location.
 *
 * @param name Name of attribute
 * @param location Location to bind to
 * @throw invalid_argument if name is empty
 */
void Program::attribLocation(const std::string& name, GLuint location) const {
    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    }
    glBindAttribLocation(_id, location, name.c_str());
}

/**
 * Creates a new program.
 *
 * @return New program instance
 * @throws std::runtime_error if program could not be created
 */
Program Program::create() {

    // Create an ID
    const GLuint id = glCreateProgram();
    if (id == 0) {
        throw runtime_error("[Program] Could not create program!");
    }

    // Make the program
    return Program(id);
}

/**
 * Detaches a shader from this program.
 *
 * @param shader Shader to detach
 * @throws invalid_argument if shader is not a valid shader
 * @throws invalid_argument if shader is not already attached
 */
void Program::detachShader(GLuint shader) const {
    detachShader(Shader::wrap(shader));
}

/**
 * Detaches a shader from this program.
 *
 * @param shader Shader to detach
 * @throws invalid_argument if shader is not already attached
 */
void Program::detachShader(const Shader &shader) const {
    if (!isAttached(shader)) {
        throw invalid_argument("[Program] Shader not already attached!");
    }
    glDetachShader(_id, shader.id());
}

/**
 * Deletes the underlying OpenGL shader program.
 */
void Program::dispose() const {
    glDeleteProgram(_id);
}

/**
 * Returns the location of an output variable.
 *
 * @param name Name of output variable
 * @return Location of output variable, or -1 if name is not an active output variable
 */
GLint Program::fragDataLocation(const std::string& name) const {
    return glGetFragDataLocation(_id, name.c_str());
}

/**
 * Binds a fragment shader output variable to a location.
 *
 * @param name Name of output variable to bind
 * @param location Location of draw buffer to bind to
 * @throws invalid_argument if location greater than GL_MAX_DRAW_BUFFERS
 * @throws invalid_argument if name is empty or starts with 'gl_'
 */
void Program::fragDataLocation(const std::string &name, GLuint location) const {

    if (location > getMaxDrawBuffers()) {
        throw invalid_argument("[Program] Location greater than GL_MAX_DRAW_BUFFERS");
    } else if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (name.find("gl_") == 0) {
        throw invalid_argument("[Program] Name starts with 'gl_'");
    }

    glBindFragDataLocation(_id, location, name.c_str());
}

/**
 * Returns the OpenGL identifier for this program.
 */
GLuint Program::id() const {
    return _id;
}

/**
 * Links this program.
 */
void Program::link() const {
    glLinkProgram(_id);
}

/**
 * Returns `true` if program is linked.
 */
bool Program::linked() const {
    GLint linked;
    glGetProgramiv(_id, GL_LINK_STATUS, &linked);
    return linked;
}

/**
 * Returns this program's log.
 */
string Program::log() const {

    // Make a buffer big enough to hold the log
    GLint len;
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &len);
    GLchar* const buf = new GLchar[len + 1];

    // Put the log into the buffer
    GLint num;
    glGetProgramInfoLog(_id, len, &num, buf);
    buf[num] = '\0';

    // Make a string from the buffer and then delete it
    string str(buf);
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Copies the ID of another program.
 *
 * @param program Program to copy
 * @return Reference to this program
 */
Program& Program::operator=(const Program& program) {
    _id = program._id;
}

/**
 * Checks if another program has the same ID as this one.
 *
 * @param program Program to check
 * @return `true` if both programs have same ID
 */
bool Program::operator==(const Program& program) const {
    return _id == program._id;
}

/**
 * Checks if another program has a different ID than this one.
 *
 * @param program Program to check
 * @return `true` if programs have different IDs
 */
bool Program::operator!=(const Program& program) const {
    return _id != program._id;
}

/**
 * Returns all the shaders attached to this program.
 */
vector<Shader> Program::shaders() const {

    // Determine how many shaders are attached
    GLint len;
    glGetProgramiv(_id, GL_ATTACHED_SHADERS, &len);
    if (len == 0) {
        return vector<Shader>();
    }

    // Put attached shaders into array
    GLuint* const arr = new GLuint[len];
    glGetAttachedShaders(_id, len, NULL, arr);

    // Add them to a vector
    vector<Shader> vec;
    for (int i = 0; i < len; ++i) {
        const Shader shader = Shader::wrap(arr[i]);
        vec.push_back(shader);
    }

    // Delete the array
    delete[] arr;

    // Return the vector
    return vec;
}

/**
 * Determines the location of a uniform in this program.
 *
 * @param name Name of the uniform to look for
 * @return Location of the uniform, or `-1` if not in program
 */
GLint Program::uniformLocation(const string& name) const {
    return glGetUniformLocation(_id, name.c_str());
}

/**
 * Activates this program.
 */
void Program::use() const {
    glUseProgram(_id);
}

/**
 * Checks if this program is valid.
 */
bool Program::valid() const {
    GLint valid;
    glGetProgramiv(_id, GL_VALIDATE_STATUS, &valid);
    return valid;
}

/**
 * Ensures this program is valid.
 */
void Program::validate() const {
    glValidateProgram(_id);
}

/**
 * Wraps an existing OpenGL program.
 *
 * @param id OpenGL identifier for program
 * @return Wrapper for OpenGL program
 * @throws std::invalid_argument if ID is not an OpenGL program
 */
Program Program::wrap(const GLuint id) {
    return Program(id);
}

// HELPERS

/**
 * Checks if a shader is attached to this program.
 *
 * @param shader Shader to check
 * @return `true` if shader is attached
 */
bool Program::isAttached(const Shader &shader) const {
    const vector<Shader> attachedShaders = shaders();
    vector<Shader>::const_iterator it = attachedShaders.begin();
    while (it != attachedShaders.end()) {
        if ((*it) == shader) {
            return true;
        }
        ++it;
    }
    return false;
}

/**
 * Returns the value of GL_MAX_DRAW_BUFFERS.
 */
GLint Program::getMaxDrawBuffers() {
    GLint value;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &value);
    return value;
}

} /* namespace Glycerin */

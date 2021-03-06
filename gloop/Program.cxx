/*
 * Copyright (c) 2012, Andrew Brown
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "config.h"
#include <stdexcept>
#include "gloop/Program.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs a program wrapping an existing shader program.
 *
 * @param id ID of existing shader program to wrap
 */
Program::Program(GLuint id) : _id(id) {
    // empty
}

/**
 * Destroys this program handle, leaving the underlying OpenGL shader program unaffected.
 *
 * @see @ref dispose
 */
Program::~Program() {
    // empty
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
 * Retrieves all the active attributes in this program.
 *
 * @return Mapping of all the active attributes in this program by name
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetActiveAttrib.xml
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
 * Retrieves all the active uniforms in this program.
 *
 * @return Mapping of all the active uniforms in this program by name
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetActiveUniform.xml
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
 * @throw invalid_argument if shader is not valid
 * @throw logic_error if shader is already attached
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glAttachShader.xml
 */
void Program::attachShader(GLuint shader) const {
    attachShader(Shader::fromId(shader));
}

/**
 * Attaches a shader to this program.
 *
 * @param shader Wrapper for an OpenGL shader
 * @throw logic_error if shader is already attached
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glAttachShader.xml
 */
void Program::attachShader(const Shader &shader) const {
    if (isAttached(shader)) {
        throw logic_error("[Program] Shader is already attached!");
    }
    glAttachShader(_id, shader.id());
}

/**
 * Gets the location of an attribute in this program.
 *
 * @param name Name of attribute to look up
 * @return Location of the attribute in this program, or `-1` if attribute is not in this program
 * @throws invalid_argument if name is empty
 * @throws logic_error if program has not been linked yet
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetAttribLocation.xml
 */
GLint Program::attribLocation(const std::string &name) const {

    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (!linked()) {
        throw logic_error("[Program] Program not linked yet!");
    }

    return glGetAttribLocation(_id, name.c_str());
}

/**
 * Binds an attribute to a specific location.
 *
 * @param name Name of attribute
 * @param location Location to bind to
 * @throw invalid_argument if name is empty
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindAttribLocation.xml
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
 * @throws runtime_error if program could not be created
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glCreateProgram.xml
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
 * Returns a handle for the current OpenGL program.
 *
 * @return Handle for the current OpenGL program
 * @throws runtime_error if there is no current OpenGL program
 */
Program Program::current() {
    const GLuint id = getCurrentProgram();
    if (id == 0) {
        throw runtime_error("[Program] No current OpenGL shader program!");
    }
    return Program(id);
}

/**
 * Detaches a shader from this program.
 *
 * @param shader Shader to detach
 * @throws invalid_argument if shader is not a valid shader
 * @throws logic_error if shader is not already attached
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glDetachShader.xml
 */
void Program::detachShader(GLuint shader) const {
    detachShader(Shader::fromId(shader));
}

/**
 * Detaches a shader from this program.
 *
 * @param shader Shader to detach
 * @throws logic_error if shader is not already attached
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glDetachShader.xml
 */
void Program::detachShader(const Shader &shader) const {
    if (!isAttached(shader)) {
        throw logic_error("[Program] Shader not already attached!");
    }
    glDetachShader(_id, shader.id());
}

/**
 * Deletes the underlying OpenGL shader program.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glDeleteProgram.xml
 */
void Program::dispose() const {
    glDeleteProgram(_id);
}

/**
 * Gets the location of an output variable in this program.
 *
 * @param name Name of output variable to look up
 * @return Location of output variable, or `-1` if name is not an active output variable
 * @throws invalid_argument if name is empty
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetFragDataLocation.xml
 */
GLint Program::fragDataLocation(const std::string& name) const {
    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    }
    return glGetFragDataLocation(_id, name.c_str());
}

/**
 * Binds a fragment shader output variable to a location.
 *
 * @param name Name of output variable to bind
 * @param location Location of draw buffer to bind to
 * @throws invalid_argument if name is empty or starts with `gl_`
 * @throws invalid_argument if location greater than `GL_MAX_DRAW_BUFFERS`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindFragDataLocation.xml
 */
void Program::fragDataLocation(const std::string &name, GLuint location) const {

    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (name.find("gl_") == 0) {
        throw invalid_argument("[Program] Name starts with 'gl_'!");
    } else if (location > getMaxDrawBuffers()) {
        throw invalid_argument("[Program] Location greater than GL_MAX_DRAW_BUFFERS!");
    }

    glBindFragDataLocation(_id, location, name.c_str());
}

/**
 * Creates a program handle from the ID of an existing OpenGL program.
 *
 * @param id ID of existing OpenGL program
 * @return Handle for OpenGL program
 * @throws invalid_argument if ID is not an OpenGL program
 */
Program Program::fromId(const GLuint id) {
    if (!glIsProgram(id)) {
        throw invalid_argument("[Program] ID is not an existing OpenGL shader program!");
    }
    return Program(id);
}

/**
 * Returns the identifier of the current OpenGL shader program.
 *
 * @return Identifier of the current OpenGL shader program, or `0` if none
 */
GLuint Program::getCurrentProgram() {
    GLuint id;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &id);
    return id;
}

/**
 * Determines the ID of the underlying OpenGL shader program this program handle represents.
 *
 * @return ID of the underlying OpenGL shader program this program handle represents
 */
GLuint Program::id() const {
    return _id;
}

/**
 * Links this program.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glLinkProgram.xml
 */
void Program::link() const {
    glLinkProgram(_id);
}

/**
 * Checks if this program is linked.
 *
 * @return `true` if this program is linked
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetProgram.xml
 */
bool Program::linked() const {
    GLint linked;
    glGetProgramiv(_id, GL_LINK_STATUS, &linked);
    return linked;
}

/**
 * Retrieves a copy of this program's log.
 *
 * @return Copy of this program's log
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetProgramInfoLog.xml
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
 * Changes which OpenGL shader program this program represents.
 *
 * @param program Program to copy ID from
 * @return Reference to this program to support chaining
 */
Program& Program::operator=(const Program& program) {
    _id = program._id;
    return (*this);
}

/**
 * Checks if another program has the same ID as this one.
 *
 * @param program Program to check
 * @return `true` if both programs have the same ID
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
 * Checks if this program's ID is less than another program's ID.
 *
 * @param program Program to check
 * @return `true` if this program's ID is less than the other program's ID
 */
bool Program::operator<(const Program& program) const {
    return _id < program._id;
}

/**
 * Retrieves all the shaders attached to this program.
 *
 * @return Vector of all the shaders attached to this program
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetAttachedShaders.xml
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
        const Shader shader = Shader::fromId(arr[i]);
        vec.push_back(shader);
    }

    // Delete the array
    delete[] arr;

    // Return the vector
    return vec;
}

/**
 * Gets the location of a uniform in this program.
 *
 * @param name Name of uniform to look up
 * @return Location of the uniform in this program, or `-1` if uniform is not in this program
 * @throws invalid_argument if name is empty
 * @throws logic_error if program has not been linked yet
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetUniformLocation.xml
 */
GLint Program::uniformLocation(const string& name) const {

    if (name.empty()) {
        throw invalid_argument("[Program] Name is empty!");
    } else if (!linked()) {
        throw logic_error("[Program] Program not linked yet!");
    }

    return glGetUniformLocation(_id, name.c_str());
}

/**
 * Activates this program.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glUseProgram.xml
 */
void Program::use() const {
    glUseProgram(_id);
}

/**
 * Checks if this program is valid.
 *
 * @return `true` if this program is valid
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetProgram.xml
 */
bool Program::valid() const {
    GLint valid;
    glGetProgramiv(_id, GL_VALIDATE_STATUS, &valid);
    return valid;
}

/**
 * Ensures this program is valid.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glValidateProgram.xml
 */
void Program::validate() const {
    glValidateProgram(_id);
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

} /* namespace Gloop */

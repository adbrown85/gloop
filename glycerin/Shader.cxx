/**
 * Shader.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include "glycerin/Shader.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs a shader.
 *
 * @param id OpenGL identifier for shader
 */
Shader::Shader(const GLuint id) : _id(id) {
    // pass
}

/**
 * Constructs a shader by copying another shader.
 *
 * @param shader Shader to copy
 */
Shader::Shader(const Shader& shader) : _id(shader._id) {
    // pass
}

/**
 * Destroys this shader.
 */
Shader::~Shader() {
    // pass
}

/**
 * Compiles this shader.
 */
void Shader::compile() {
    glCompileShader(_id);
}

/**
 * Creates a new shader of a particular type.
 *
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @return New shader of specified type
 * @throw std::runtime_error if shader could not be created
 */
Shader Shader::create(const GLenum type) {

    // Create an ID
    const GLuint id = glCreateShader(type);
    if (id == 0) {
        throw runtime_error("[Shader] Could not create shader!");
    }

    // Make the shader
    return Shader(id);
}

/**
 * Deletes this shader.
 */
void Shader::dispose() {
    glDeleteShader(_id);
}

/**
 * Returns the OpenGL identifier for this shader.
 */
GLuint Shader::id() const {
    return _id;
}

/**
 * Copies the ID of another shader.
 *
 * @param shader Shader to copy
 * @return Reference to this shader to support chaining
 */
Shader& Shader::operator=(const Shader &shader) {
    _id = shader._id;
}

/**
 * Checks if another shader is equal to this one.
 *
 * @param shader Shader to check
 * @return `true` if shaders represent same OpenGL shader
 */
bool Shader::operator==(const Shader &shader) const {
    return _id == shader._id;
}

/**
 * Checks if another shader is not equal to this one.
 *
 * @param shader Shader to check
 * @return `true` if shaders do not represent same OpenGL shader
 */
bool Shader::operator!=(const Shader &shader) const {
    return _id != shader._id;
}

/**
 * Returns this shader's source code.
 */
string Shader::source() const {

    // Get the size of the source code
    GLint len;
    glGetShaderiv(_id, GL_SHADER_SOURCE_LENGTH, &len);
    if (len == 0) {
        return "";
    }

    // Put the source code into a buffer and make a string from it
    char* const buf = new char[len];
    glGetShaderSource(_id, len, NULL, buf);
    const string str(buf);

    // Delete the buffer
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Returns this shader's log.
 */
string Shader::log() const {

    // Allocate a character buffer large enough for the log
    GLsizei count;
    glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &count);
    GLchar* buf = new GLchar[count + 1];

    // Put the log into the buffer and make a string from it
    GLsizei returned;
    glGetShaderInfoLog(_id, count, &returned, buf);
    buf[returned] = '\0';
    string str(buf);

    // Delete the buffer
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Returns the kind of this shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`.
 */
GLenum Shader::type() const {
    GLint type;
    glGetShaderiv(_id, GL_SHADER_TYPE, &type);
    return type;
}

/**
 * Returns `true` if shader is compiled.
 */
bool Shader::compiled() const {
    GLint compiled;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
    return compiled;
}

/**
 * Changes this shader's source code.
 *
 * @param source Code for shader
 * @throws invalid_argument if source code is empty
 */
void Shader::source(const std::string& source) {
    const char* buf = source.c_str();
    const char** ptr = &buf;
    glShaderSource(_id, 1, ptr, NULL);
}

/**
 * Wraps an existing OpenGL shader.
 *
 * @param id OpenGL identifier for shader
 * @return Wrapper for OpenGL shader
 * @throws std::invalid_argument if ID is not a valid OpenGL shader
 */
Shader Shader::wrap(const GLuint id) {
    if (!glIsShader(id)) {
        throw invalid_argument("[Shader] ID is not a valid shader!");
    }
    return Shader(id);
}

} /* namespace Glycerin */

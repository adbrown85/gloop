/**
 * ShaderFactory.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include "glycerin/shader/Shader.hpp"
using namespace std;
namespace Glycerin {

/**
 * Constructs a shader.
 *
 * @param handle OpenGL identifier for shader
 */
Shader::Shader(const GLuint handle) : _handle(handle) {
    // pass
}

/**
 * Constructs a shader by copying another shader.
 *
 * @param shader Shader to copy
 */
Shader::Shader(const Shader& shader) : _handle(shader._handle) {
    // pass
}

/**
 * Destroys the shader.
 */
Shader::~Shader() {
    // pass
}

/**
 * Compiles the shader.
 */
void Shader::compile() {
    glCompileShader(_handle);
}

/**
 * Creates a new shader of a particular type.
 *
 * @param type Kind of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @return New shader of specified type
 * @throw std::runtime_error if shader could not be created
 */
Shader Shader::create(const GLenum type) {

    // Create a handle
    const GLuint handle = glCreateShader(type);
    if (handle == 0) {
        throw runtime_error("[Shader] Could not create shader!");
    }

    // Make the shader
    return Shader(handle);
}

/**
 * Deletes the shader.
 */
void Shader::dispose() {
    glDeleteShader(_handle);
}

/**
 * Returns the OpenGL identifier for the shader.
 */
GLuint Shader::handle() const {
    return _handle;
}

/**
 * Copies the handle of another shader.
 *
 * @param shader Shader to copy
 * @return Reference to this shader to support chaining
 */
Shader& Shader::operator=(const Shader &shader) {
    _handle = shader._handle;
}

/**
 * Checks if another shader is equal to this one.
 *
 * @param shader Shader to check
 * @return <tt>true</tt> if shaders represent same OpenGL shader
 */
bool Shader::operator==(const Shader &shader) {
    return _handle == shader.handle();
}

/**
 * Checks if another shader is not equal to this one.
 *
 * @param shader Shader to check
 * @return <tt>true</tt> if shaders do not represent same OpenGL shader
 */
bool Shader::operator!=(const Shader &shader) {
    return _handle != shader.handle();
}

/**
 * Returns the shader's source code.
 */
string Shader::source() const {

    // Get the size of the source code
    GLint len;
    glGetShaderiv(_handle, GL_SHADER_SOURCE_LENGTH, &len);
    if (len == 0) {
        return "";
    }

    // Put the source code into a buffer and make a string from it
    char* const buf = new char[len];
    glGetShaderSource(_handle, len, NULL, buf);
    const string str(buf);

    // Delete the buffer
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Returns the shader's log.
 */
string Shader::log() const {

    // Allocate a character buffer large enough for the log
    GLsizei count;
    glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &count);
    GLchar* buf = new GLchar[count + 1];

    // Put the log into the buffer and make a string from it
    GLsizei returned;
    glGetShaderInfoLog(_handle, count, &returned, buf);
    buf[returned] = '\0';
    string str(buf);

    // Delete the buffer
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Returns the kind of this shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
 */
GLenum Shader::type() const {
    GLint type;
    glGetShaderiv(_handle, GL_SHADER_TYPE, &type);
    return type;
}

/**
 * Returns <tt>true</tt> if shader is compiled.
 */
bool Shader::compiled() const {
    GLint compiled;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &compiled);
    return compiled;
}

/**
 * Changes the shader's source code.
 *
 * @param source Code for shader
 * @throws invalid_argument if source code is empty
 */
void Shader::source(const string& source) {
    const char* buf = source.c_str();
    const char** ptr = &buf;
    glShaderSource(_handle, 1, ptr, NULL);
}

/**
 * Wraps an existing OpenGL shader.
 *
 * @param handle OpenGL identifier for shader
 * @return Wrapper for OpenGL shader
 * @throws runtime_error if handle is not a valid OpenGL shader
 */
Shader Shader::wrap(const GLuint handle) {
    if (!glIsShader(handle)) {
        throw runtime_error("[Shader] Handle is not a valid shader!");
    }
    return Shader(handle);
}

} /* namespace Glycerin */

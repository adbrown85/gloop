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
 * Destroys this shader handle, leaving the underlying OpenGL shader unaffected.
 *
 * @see @ref dispose
 */
Shader::~Shader() {
    // pass
}

/**
 * Compiles this shader.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glCompileShader.xml
 */
void Shader::compile() const {
    glCompileShader(_id);
}

/**
 * Checks if this shader is compiled.
 *
 * @return `true` if this shader is compiled
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetShader.xml
 */
bool Shader::compiled() const {
    GLint compiled;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
    return compiled;
}

/**
 * Creates a new shader of a particular type.
 *
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @return New shader of specified type
 * @throw runtime_error if shader could not be created
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glCreateShader.xml
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
 * Deletes the underlying OpenGL shader.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glDeleteShader.xml
 */
void Shader::dispose() const {
    glDeleteShader(_id);
}

/**
 * Creates a shader handle from the ID of an existing OpenGL shader.
 *
 * @param id ID of existing OpenGL shader
 * @return Handle for OpenGL shader
 * @throws invalid_argument if ID is not a valid OpenGL shader
 */
Shader Shader::fromId(const GLuint id) {
    if (!glIsShader(id)) {
        throw invalid_argument("[Shader] ID is not a valid shader!");
    }
    return Shader(id);
}

/**
 * Determines the ID of the underlying OpenGL shader this shader handle represents.
 *
 * @return ID of the underlying OpenGL shader this shader handle represents
 */
GLuint Shader::id() const {
    return _id;
}

/**
 * Retrieves a copy of this shader's log.
 *
 * @return Copy of this shader's log
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetShaderInfoLog.xml
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
 * Changes which OpenGL shader this shader represents.
 *
 * @param shader Shader to copy ID from
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
 * Checks if this shader's ID is less than another shader's ID.
 *
 * @param shader Shader to check
 * @return `true` if this shader's ID is less than the other shader's ID
 */
bool Shader::operator<(const Shader &shader) const {
    return _id < shader._id;
}

/**
 * Retrieves a copy of this shader's source code.
 *
 * @return Copy of this shader's source code
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetShaderSource.xml
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
 * Changes this shader's source code.
 *
 * @param source Code for shader
 * @throws invalid_argument if source code is empty
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glShaderSource.xml
 */
void Shader::source(const std::string& source) const {
    const char* buf = source.c_str();
    const char** ptr = &buf;
    glShaderSource(_id, 1, ptr, NULL);
}

/**
 * Returns the kind of this shader, as in `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`.
 */
GLenum Shader::type() const {
    GLint type;
    glGetShaderiv(_id, GL_SHADER_TYPE, &type);
    return type;
}

} /* namespace Glycerin */

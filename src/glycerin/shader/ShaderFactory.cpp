/*
 * ShaderFactory.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "glycerin/shader/ShaderFactory.hpp"
using namespace std;
namespace Glycerin {

/**
 * Constructs a shader factory.
 */
ShaderFactory::ShaderFactory() {
    // pass
}

/**
 * Creates a shader from a file.
 *
 * @param type Kind of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param filename Path to the file containing shader's source code
 * @return OpenGL handle to the shader
 * @throw std::invalid_argument if filename is empty
 */
GLuint ShaderFactory::createShaderFromFile(GLenum type, const string& filename) {

    // Make a stream from the file
    ifstream fs(filename.c_str());

    // Make the shader from the stream
    return createShaderFromStream(type, fs);
}

/**
 * Creates a shader from a stream.
 *
 * @param type Kind of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param stream Stream containing shader's source code
 * @return OpenGL handle to the shader
 */
GLuint ShaderFactory::createShaderFromStream(GLenum type, istream& stream) {

    // Make a string from the stream
    stringstream ss;
    while (stream) {
        string line;
        getline(stream, line);
        ss << line << '\n';
    }

    // Make the shader from the string
    return createShaderFromString(type, ss.str());
}

/**
 * Creates a shader from a string.
 *
 * @param type Kind of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param str String containing shader's source code
 * @return OpenGL handle to the shader
 * @throw runtime_error if could not create or compile shader
 */
GLuint ShaderFactory::createShaderFromString(GLenum type, const string &str) {

    // Create the shader
    const GLuint handle = glCreateShader(type);
    if (handle == 0) {
        throw runtime_error("[ShaderFactory] Could not create shader!");
    }

    // Load the source
    const char* buf = str.c_str();
    const char** ptr = &buf;
    glShaderSource(handle, 1, ptr, NULL);

    // Compile
    glCompileShader(handle);
    if (!isCompiled(handle)) {
        string log = getLog(handle);
        throw runtime_error(log);
    }

    // Return the shader
    return handle;
}

// HELPERS

/**
 * Retrieves the log of a shader.
 *
 * @param handle Handle to shader
 * @return String containing log
 */
string ShaderFactory::getLog(const GLuint handle) {

    // Allocate a character buffer large enough for the log
    GLsizei count;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &count);
    GLchar* buf = new GLchar[count + 1];

    // Put the log into the buffer and make a string from it
    GLsizei returned;
    glGetShaderInfoLog(handle, count, &returned, buf);
    buf[returned] = '\0';
    string str(buf);

    // Delete the buffer
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Checks if a shader is compiled.
 *
 * @param handle Handle to shader
 * @return <tt>true</tt> if shader is compiled
 */
bool ShaderFactory::isCompiled(const GLuint handle) {
    GLint compiled;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
    return compiled;
}

} /* namespace Glycerin */

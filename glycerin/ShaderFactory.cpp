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
#include "glycerin/ShaderFactory.hxx"
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
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param filename Path to the file containing shader's source code
 * @return OpenGL handle to the shader
 * @throw std::invalid_argument if filename is empty
 */
Shader ShaderFactory::createShaderFromFile(GLenum type, const string& filename) {

    // Make a stream from the file
    ifstream fs(filename.c_str());
    if (!fs) {
        throw invalid_argument("[ShaderFactory] Could not open file!");
    }

    // Make the shader from the stream
    return createShaderFromStream(type, fs);
}

/**
 * Creates a shader from a stream.
 *
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param stream Stream containing shader's source code
 * @return OpenGL handle to the shader
 */
Shader ShaderFactory::createShaderFromStream(GLenum type, istream& stream) {

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
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param str String containing shader's source code
 * @return OpenGL handle to the shader
 * @throw runtime_error if could not create or compile shader
 */
Shader ShaderFactory::createShaderFromString(GLenum type, const string &str) {

    // Create the shader
    Shader shader = Shader::create(type);

    // Load the source
    shader.source(str);

    // Compile
    shader.compile();
    if (!shader.compiled()) {
        string log = shader.log();
        throw runtime_error(log);
    }

    // Return the shader
    return shader;
}

} /* namespace Glycerin */

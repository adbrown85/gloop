/*
 * ProgramBuilder.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include "glycerin/shader/ProgramBuilder.hpp"
using namespace std;
namespace Glycerin {

/**
 * Constructs a program builder.
 */
ProgramBuilder::ProgramBuilder() {
    // pass
}

/**
 * Destroys a program builder.
 */
ProgramBuilder::~ProgramBuilder() {
    // pass
}

/**
 * Adds a shader to the program being built.
 *
 * @param shader Existing shader to add
 */
void ProgramBuilder::addShader(GLuint shader) {
    shaders.push_back(shader);
}

/**
 * Binds an attribute to an index.
 *
 * @param index Index to bind to
 * @param name Name of vertex attribute to bind
 * @throw invalid_argument if name is empty
 */
void ProgramBuilder::bindAttribute(GLuint index, const string& name) {
    if (name.empty()) {
        throw invalid_argument("[ProgramBuilder] Name is empty!");
    }
    locations[index] = name;
}

/**
 * Resets the builder to its default state.
 */
void ProgramBuilder::reset() {
    shaders.clear();
    locations.clear();
}

/**
 * Finishes building a shader program.
 *
 * @return Handle to the new shader program
 * @throw std::runtime_error if program could not be created or linked
 */
GLuint ProgramBuilder::toProgram() {

    // Create a program
    GLuint handle = glCreateProgram();
    if (handle == 0) {
        throw runtime_error("[ProgramBuilder] Could not create program!");
    }

    // Attach all the shaders
    for (list<GLuint>::iterator it = shaders.begin(); it != shaders.end(); ++it) {
        glAttachShader(handle, (*it));
    }

    // Bind locations
    for (map<GLuint,string>::iterator it = locations.begin(); it != locations.end(); ++it) {
        glBindAttribLocation(handle, it->first, it->second.c_str());
    }

    // Link the program
    glLinkProgram(handle);
    if (!isLinked(handle)) {
        throw runtime_error(getLog(handle));
    }

    // Return the program
    return handle;
}

/**
 * Retrieves the log for a shader program.
 *
 * @param handle OpenGL handle to a shader program
 * @return Log of the program
 */
string ProgramBuilder::getLog(GLuint handle) {

    // Make a buffer big enough to hold the log
    GLint len;
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &len);
    GLchar* const buf = new GLchar[len + 1];

    // Put the log into the buffer
    GLint num;
    glGetProgramInfoLog(handle, len, &num, buf);
    buf[num] = '\0';

    // Make a string from the buffer and then delete it
    string str(buf);
    delete[] buf;

    // Return the string
    return str;
}

/**
 * Checks if a program is linked.
 *
 * @param handle OpenGL handle to a shader program
 * @return <tt>true</tt> if program is linked
 */
bool ProgramBuilder::isLinked(GLuint handle) {
    GLint linked;
    glGetProgramiv(handle, GL_LINK_STATUS, &linked);
    return linked;
}

} /* namespace Glycerin */

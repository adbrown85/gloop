/*
 * ErrorChecker.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/ErrorChecker.hxx"
using namespace std;
using namespace Glycerin;

/**
 * Checks for an OpenGL error.
 *
 * @param location Location in code
 */
void ErrorChecker::checkErrors(const string &location) {

    GLenum error;

    error = glGetError();
    while (error != GL_NO_ERROR) {
        report(error, location);
        error = glGetError();
    }
}

/**
 * Clears all the error flags.
 */
void ErrorChecker::clearErrors() {

    GLenum error;

    error = glGetError();
    while (error != GL_NO_ERROR) {
        error = glGetError();
    }
}

/**
 * Prints information about an error.
 */
void ErrorChecker::report(GLenum error, const string &location) {
    cerr << "At '" << location << "':" << endl;
    cerr << toString(error) << endl;
}

/**
 * Returns human-readable description for an error.
 */
string ErrorChecker::toString(GLenum error) {
    switch (error) {
    case GL_INVALID_ENUM:
        return "Invalid enumeration.";
    case GL_INVALID_VALUE:
        return "Invalid value.";
    case GL_INVALID_OPERATION:
        return "Invalid operation.";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "Invalid framebuffer operation.";
    case GL_OUT_OF_MEMORY:
        return "Out of memory.";
    default:
        cerr << "[ErrorChecker] Unexpected error flag." << endl;
        exit(1);
    }
}


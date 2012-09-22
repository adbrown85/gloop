/*
 * Uniform.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include "glycerin/Uniform.hpp"
namespace Glycerin {

/**
 * Loads a float value into the uniform's location in the current program.
 *
 * @param x Value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT`
 */
void Uniform::load1f(GLfloat x) {
    assert (currentProgram() == program);
    assert (type = GL_FLOAT);
    glUniform1f(location, x);
}

/**
 * Loads two float values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_VEC2`
 */
void Uniform::load2f(GLfloat x, GLfloat y) {
    assert (currentProgram() == program);
    assert (type = GL_FLOAT_VEC2);
    glUniform2f(location, x, y);
}

/**
 * Loads three float values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @param z Third value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_VEC3`
 */
void Uniform::load3f(GLfloat x, GLfloat y, GLfloat z) {
    assert (currentProgram() == program);
    assert (type = GL_FLOAT_VEC3);
    glUniform3f(location, x, y, z);
}

/**
 * Loads four float values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @param z Third value to load
 * @param w Fourth value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_VEC4`
 */
void Uniform::load4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    assert (currentProgram() == program);
    assert (type = GL_FLOAT_VEC4);
    glUniform4f(location, x, y, z, w);
}

/**
 * Loads an integer value into the uniform's location in the current program.
 *
 * @param x Value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT`
 */
void Uniform::load1i(GLint x) {
    assert (currentProgram() == program);
    assert (type = GL_INT);
    glUniform1i(location, x);
}

/**
 * Loads two integer values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT_VEC2`
 */
void Uniform::load2i(GLint x, GLint y) {
    assert (currentProgram() == program);
    assert (type = GL_INT_VEC2);
    glUniform2i(location, x, y);
}

/**
 * Loads three integer values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @param z Third value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT_VEC3`
 */
void Uniform::load3i(GLint x, GLint y, GLint z) {
    assert (currentProgram() == program);
    assert (type = GL_INT_VEC3);
    glUniform3i(location, x, y, z);
}

/**
 * Loads four integer values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @param z Third value to load
 * @param w Fourth value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT_VEC4`
 */
void Uniform::load4i(GLint x, GLint y, GLint z, GLint w) {
    assert (currentProgram() == program);
    assert (type = GL_INT_VEC4);
    glUniform4i(location, x, y, z, w);
}

/**
 * Loads an unsigned integer value into the uniform's location in the current program.
 *
 * @param x Value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT`
 */
void Uniform::load1ui(GLuint x) {
    assert (currentProgram() == program);
    assert (type = GL_UNSIGNED_INT);
    glUniform1ui(location, x);
}

/**
 * Loads two unsigned values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT_VEC2`
 */
void Uniform::load2ui(GLuint x, GLuint y) {
    assert (currentProgram() == program);
    assert (type = GL_UNSIGNED_INT_VEC2);
    glUniform2ui(location, x, y);
}

/**
 * Loads three unsigned values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @param z Third value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT_VEC3`
 */
void Uniform::load3ui(GLuint x, GLuint y, GLuint z) {
    assert (currentProgram() == program);
    assert (type = GL_UNSIGNED_INT_VEC3);
    glUniform3ui(location, x, y, z);
}

/**
 * Loads four unsigned integer values into the uniform's location in the current program.
 *
 * @param x First value to load
 * @param y Second value to load
 * @param z Third value to load
 * @param w Fourth value to load
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT_VEC4`
 */
void Uniform::load4ui(GLuint x, GLuint y, GLuint z, GLuint w) {
    assert (currentProgram() == program);
    assert (type = GL_UNSIGNED_INT_VEC4);
    glUniform4ui(location, x, y, z, w);
}

/**
 * Loads one or more float values into the uniform.
 *
 * @param count Number of values to load
 * @param value Pointer to array with values
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load1fv(GLsizei count, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT);
    assert (count <= size);
    glUniform1fv(location, count, value);
}

/**
 * Loads one or more 2-component float vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_VEC2`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load2fv(GLsizei count, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_VEC2);
    assert (count <= size);
    glUniform2fv(location, count, value);
}

/**
 * Loads one or more 3-component float vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_VEC3`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load3fv(GLsizei count, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_VEC3);
    assert (count <= size);
    glUniform3fv(location, count, value);
}

/**
 * Loads one or more 4-component float vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_VEC4`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load4fv(GLsizei count, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_VEC4);
    assert (count <= size);
    glUniform4fv(location, count, value);
}

/**
 * Loads one or more integer values into the uniform.
 *
 * @param count Number of values to load
 * @param value Pointer to array with values
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load1iv(GLsizei count, const GLint* value) {
    assert (currentProgram() == program);
    assert (type == GL_INT);
    assert (count <= size);
    glUniform1iv(location, count, value);
}

/**
 * Loads one or more 2-component integer vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT_VEC2`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load2iv(GLsizei count, const GLint* value) {
    assert (currentProgram() == program);
    assert (type == GL_INT_VEC2);
    assert (count <= size);
    glUniform2iv(location, count, value);
}

/**
 * Loads one or more 3-component integer vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT_VEC3`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load3iv(GLsizei count, const GLint* value) {
    assert (currentProgram() == program);
    assert (type == GL_INT_VEC3);
    assert (count <= size);
    glUniform3iv(location, count, value);
}

/**
 * Loads one or more 4-component integer vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_INT_VEC4`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load4iv(GLsizei count, const GLint* value) {
    assert (currentProgram() == program);
    assert (type == GL_INT_VEC4);
    assert (count <= size);
    glUniform4iv(location, count, value);
}

/**
 * Loads one or more unsigned integer values into the uniform.
 *
 * @param count Number of values to load
 * @param value Pointer to array with values
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load1uiv(GLsizei count, const GLuint* value) {
    assert (currentProgram() == program);
    assert (type == GL_UNSIGNED_INT);
    assert (count <= size);
    glUniform1uiv(location, count, value);
}

/**
 * Loads one or more 2-component unsigned integer vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT_VEC2`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load2uiv(GLsizei count, const GLuint* value) {
    assert (currentProgram() == program);
    assert (type == GL_UNSIGNED_INT_VEC2);
    assert (count <= size);
    glUniform2uiv(location, count, value);
}

/**
 * Loads one or more 3-component unsigned integer vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT_VEC3`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load3uiv(GLsizei count, const GLuint* value) {
    assert (currentProgram() == program);
    assert (type == GL_UNSIGNED_INT_VEC3);
    assert (count <= size);
    glUniform3uiv(location, count, value);
}

/**
 * Loads one or more 4-component unsigned integer vectors into the uniform.
 *
 * @param count Number of vectors to load
 * @param value Pointer to array with vectors
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_UNSIGNED_INT_VEC4`
 * @pre Number of values to load is less than or equal to size of uniform
 */
void Uniform::load4uiv(GLsizei count, const GLuint* value) {
    assert (currentProgram() == program);
    assert (type == GL_UNSIGNED_INT_VEC4);
    assert (count <= size);
    glUniform4uiv(location, count, value);
}

/**
 * Loads one or more 2x2 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT2`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT2);
    assert (count <= size);
    glUniformMatrix2fv(location, count, transpose, value);
}

/**
 * Loads one or more 3x3 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT3`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT3);
    assert (count <= size);
    glUniformMatrix3fv(location, count, transpose, value);
}

/**
 * Loads one or more 4x4 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT4`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat* value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT4);
    assert (count <= size);
    glUniformMatrix4fv(location, count, transpose, value);
}

/**
 * Loads one or more 2x3 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT2x3`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix2x3fv(GLsizei count, GLboolean transpose, const GLfloat *value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT2x3);
    assert (count <= size);
    glUniformMatrix2x3fv(location, count, transpose, value);
}

/**
 * Loads one or more 3x2 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT3x2`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix3x2fv(GLsizei count, GLboolean transpose, const GLfloat *value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT3x2);
    assert (count <= size);
    glUniformMatrix3x2fv(location, count, transpose, value);
}

/**
 * Loads one or more 2x4 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT2x4`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix2x4fv(GLsizei count, GLboolean transpose, const GLfloat *value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT2x4);
    assert (count <= size);
    glUniformMatrix2x4fv(location, count, transpose, value);
}

/**
 * Loads one or more 4x2 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT4x2`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix4x2fv(GLsizei count, GLboolean transpose, const GLfloat *value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT4x2);
    assert (count <= size);
    glUniformMatrix4x2fv(location, count, transpose, value);
}

/**
 * Loads one or more 3x4 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT3x4`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix3x4fv(GLsizei count, GLboolean transpose, const GLfloat *value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT3x4);
    assert (count <= size);
    glUniformMatrix3x4fv(location, count, transpose, value);
}

/**
 * Loads one or more 4x3 float matrices into the uniform.
 *
 * @param count Number of matrices to load
 * @param transpose `true` if matrices should be transposed
 * @param value Pointer to the array of matrices
 * @pre Current program is this uniform's program
 * @pre Uniform's type is `GL_FLOAT_MAT4x3`
 * @pre Number of matrices to load is less than or equal to size of uniform
 */
void Uniform::loadMatrix4x3fv(GLsizei count, GLboolean transpose, const GLfloat *value) {
    assert (currentProgram() == program);
    assert (type == GL_FLOAT_MAT4x3);
    assert (count <= size);
    glUniformMatrix4x3fv(location, count, transpose, value);
}

// HELPERS

GLuint Uniform::currentProgram() {
    GLint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    return program;
}

} /* namespace Glycerin */

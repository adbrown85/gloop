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
#ifndef GLOOP_UNIFORM_HXX
#define GLOOP_UNIFORM_HXX
#include "gloop/common.h"
#include "gloop/Variable.hxx"
namespace Gloop {


/**
 * OpenGL uniform information.
 */
class Uniform : public Variable {
// Friends
    friend class Program;
public:
// Methods
    void load1f(GLfloat x);
    void load2f(GLfloat x, GLfloat y);
    void load3f(GLfloat x, GLfloat y, GLfloat z);
    void load4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void load1i(GLint x);
    void load2i(GLint x, GLint y);
    void load3i(GLint x, GLint y, GLint z);
    void load4i(GLint x, GLint y, GLint z, GLint w);
    void load1ui(GLuint x);
    void load2ui(GLuint x, GLuint y);
    void load3ui(GLuint x, GLuint y, GLuint z);
    void load4ui(GLuint x, GLuint y, GLuint z, GLuint w);
    void load1fv(GLsizei count, const GLfloat* value);
    void load2fv(GLsizei count, const GLfloat* value);
    void load3fv(GLsizei count, const GLfloat* value);
    void load4fv(GLsizei count, const GLfloat* value);
    void load1iv(GLsizei count, const GLint* value);
    void load2iv(GLsizei count, const GLint* value);
    void load3iv(GLsizei count, const GLint* value);
    void load4iv(GLsizei count, const GLint* value);
    void load1uiv(GLsizei count, const GLuint* value);
    void load2uiv(GLsizei count, const GLuint* value);
    void load3uiv(GLsizei count, const GLuint* value);
    void load4uiv(GLsizei count, const GLuint* value);
    void loadMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat* value);
    void loadMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat* value);
    void loadMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat* value);
    void loadMatrix2x3fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix3x2fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix2x4fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix4x2fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix3x4fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix4x3fv(GLsizei count, GLboolean transpose, const GLfloat *value);
private:
// Methods
    Uniform(GLint location, const std::string& name, GLuint program, GLint size, GLenum type);
    static GLuint currentProgram();
};

} /* namespace Gloop */
#endif

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
#ifndef GLOOP_PROGRAM_HXX
#define GLOOP_PROGRAM_HXX
#include "gloop/common.h"
#include <map>
#include <vector>
#include "gloop/Attribute.hxx"
#include "gloop/Shader.hxx"
#include "gloop/Uniform.hxx"
namespace Gloop {


/**
 * Handle for an OpenGL shader program.
 */
class Program {
public:
// Methods
    Program(const Program& program);
    ~Program();
    std::map<std::string,Attribute> activeAttributes() const;
    std::map<std::string,Uniform> activeUniforms() const;
    void attachShader(GLuint shader) const;
    void attachShader(const Shader& shader) const;
    GLint attribLocation(const std::string& name) const;
    void attribLocation(const std::string& name, GLuint location) const;
    static Program create();
    void detachShader(GLuint shader) const;
    void detachShader(const Shader& shader) const;
    void dispose() const;
    GLint fragDataLocation(const std::string& name) const;
    void fragDataLocation(const std::string& name, GLuint location) const;
    static Program fromId(GLuint id);
    GLuint id() const;
    void link() const;
    bool linked() const;
    std::string log() const;
    Program& operator=(const Program& program);
    bool operator==(const Program& program) const;
    bool operator!=(const Program& program) const;
    bool operator<(const Program& program) const;
    std::vector<Shader> shaders() const;
    GLint uniformLocation(const std::string& name) const;
    void use() const;
    bool valid() const;
    void validate() const;
private:
// Attributes
    GLuint _id;
// Methods
    explicit Program(GLuint id);
    Program();
    static GLint getMaxDrawBuffers();
    bool isAttached(const Shader& shader) const;
};

} /* namespace Gloop */
#endif


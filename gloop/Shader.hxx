/**
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
#ifndef GLOOP_SHADER_HXX
#define GLOOP_SHADER_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * OpenGL shader.
 */
class Shader {
public:
// Methods
    Shader(const Shader& shader);
    ~Shader();
    void compile() const;
    bool compiled() const;
    static Shader create(GLenum type);
    void dispose() const;
    static Shader fromId(GLuint id);
    GLuint id() const;
    std::string log() const;
    Shader& operator=(const Shader& shader);
    bool operator==(const Shader& shader) const;
    bool operator!=(const Shader& shader) const;
    bool operator<(const Shader& shader) const;
    std::string source() const;
    void source(const std::string& source) const;
    GLenum type() const;
private:
// Attributes
    GLuint _id;
// Methods
    explicit Shader(GLuint id);
};

} /* namespace Gloop */
#endif

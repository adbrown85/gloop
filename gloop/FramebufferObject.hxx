/*
 * Copyright (c) 2013, Andrew Brown
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
#ifndef GLOOP_FRAMEBUFFER_OBJECT_HXX
#define GLOOP_FRAMEBUFFER_OBJECT_HXX
#include <iostream>
#include "gloop/common.h"
namespace Gloop {


/**
 * Handle for state of a framebuffer.
 */
class FramebufferObject {
public:
// Methods
    FramebufferObject(const FramebufferObject& fbo);
    void dispose() const;
    static FramebufferObject fromId(GLuint id);
    static FramebufferObject generate();
    GLuint id() const;
    bool operator!=(const FramebufferObject& fbo) const;
    bool operator<(const FramebufferObject& fbo) const;
    FramebufferObject& operator=(const FramebufferObject& fbo);
    bool operator==(const FramebufferObject& fbo) const;
private:
// Attributes
    GLuint _id;
// Methods
    FramebufferObject(GLuint id);
};

} /* namespace Gloop */

std::ostream& operator<<(std::ostream& stream, const Gloop::FramebufferObject& fbo);

#endif

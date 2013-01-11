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
#ifndef GLOOP_FRAMEBUFFER_TARGET_HXX
#define GLOOP_FRAMEBUFFER_TARGET_HXX
#include <iostream>
#include <string>
#include "gloop/common.h"
#include "gloop/FramebufferObject.hxx"
#include "gloop/TextureObject.hxx"
#include "gloop/TextureTarget.hxx"
namespace Gloop {


/**
 * Pointer for manipulating a framebuffer object.
 */
class FramebufferTarget {
public:
// Methods
    FramebufferTarget(const FramebufferTarget& target);
    void bind(const FramebufferObject& fbo) const;
    GLuint binding() const;
    bool bound() const;
    bool bound(const FramebufferObject& fbo) const;
    GLenum checkStatus() const;
    static FramebufferTarget drawFramebuffer();
    static std::string formatStatus(GLenum status);
    static GLint getMaxColorAttachments();
    static bool isAttachment(GLenum enumeration);
    bool operator!=(const FramebufferTarget& target) const;
    bool operator<(const FramebufferTarget& target) const;
    FramebufferTarget& operator=(const FramebufferTarget& target);
    bool operator==(const FramebufferTarget& target) const;
    static FramebufferTarget readFramebuffer();
    void texture1d(GLenum attachment, TextureTarget, TextureObject, GLint level) const;
    void texture2d(GLenum attachment, TextureTarget, TextureObject, GLint level) const;
    void texture3d(GLenum attachment, TextureTarget, TextureObject, GLint level, GLint layer) const;
    GLenum toEnum() const;
    std::string toString() const;
    void unbind() const;
private:
// Attributes
    GLenum _id;
    std::string _str;
    GLenum _key;
// Methods
    FramebufferTarget(GLenum id, const std::string& str, GLenum key);
    static bool isColorAttachment(GLenum enumeration);
};

} /* namespace Gloop */

std::ostream& operator<<(std::ostream& stream, const Gloop::FramebufferTarget& target);

#endif

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
#include "config.h"
#include <cassert>
#include <stdexcept>
#include "gloop/FramebufferTarget.hxx"
namespace Gloop {

/**
 * Constructs a framebuffer target from an identifier and descriptor.
 *
 * @param id OpenGL identifier of framebuffer target
 * @param str Human-readable descriptor of framebuffer target
 */
FramebufferTarget::FramebufferTarget(const GLenum id, const std::string& str, const GLenum key) :
        _id(id), _str(str), _key(key) {
    // empty
}

/**
 * Constructs a framebuffer target by copying the identifier of another one.
 *
 * @param target Framebuffer target to copy identifier from
 */
FramebufferTarget::FramebufferTarget(const FramebufferTarget& target) :
        _id(target._id), _str(target._str), _key(target._key) {
    // empty
}

/**
 * Binds a framebuffer object to this framebuffer target.
 *
 * @param fbo Framebuffer object to bind to this framebuffer target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindFramebuffer.xml
 */
void FramebufferTarget::bind(const FramebufferObject& fbo) const {
    glBindFramebuffer(_id, fbo.id());
}

/**
 * Determines the framebuffer currently bound to this framebuffer target.
 *
 * @return Identifier of the framebuffer currently bound to this target, or `0` if none
 */
GLuint FramebufferTarget::binding() const {
    GLint value;
    glGetIntegerv(_key, &value);
    return value;
}

/**
 * Checks if any framebuffer object is currently bound to this framebuffer target.
 *
 * @return `true` if a framebuffer object is currently bound to this framebuffer target
 */
bool FramebufferTarget::bound() const {
    return binding() != 0;
}

/**
 * Checks if a specific framebuffer object is currently bound to this framebuffer target.
 *
 * @param fbo Framebuffer object to check for
 * @return `true` if given framebuffer object is currently bound to this framebuffer target
 */
bool FramebufferTarget::bound(const FramebufferObject& fbo) const {
    return binding() == fbo.id();
}

/**
 * Checks the completeness of this framebuffer.
 *
 * @return Enumeration representing completeness of framebuffer, i.e. `GL_FRAMEBUFFER_COMPLETE`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glCheckFramebufferStatus.xml
 */
GLenum FramebufferTarget::checkStatus() const {
    return glCheckFramebufferStatus(_id);
}

/**
 * Returns a target for the framebuffer to draw to.
 *
 * @return Target for the framebuffer to draw to
 */
FramebufferTarget FramebufferTarget::drawFramebuffer() {
    return FramebufferTarget(GL_DRAW_FRAMEBUFFER, "GL_DRAW_FRAMEBUFFER", GL_DRAW_FRAMEBUFFER_BINDING);
}

/**
 * Returns a human-readable string for a framebuffer status enumeration.
 *
 * @param status Framebuffer status enumeration to get string for, i.e. `GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT`
 * @return Human-readable string for given enumeration
 * @throws std::invalid_argument if enumeration is not a valid framebuffer status
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glCheckFramebufferStatus.xml
 */
std::string FramebufferTarget::formatStatus(const GLenum status) {
    switch (status) {
    case GL_FRAMEBUFFER_COMPLETE:
        return "GL_FRAMEBUFFER_COMPLETE";
    case GL_FRAMEBUFFER_UNDEFINED:
        return "GL_FRAMEBUFFER_UNDEFINED";
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
    case GL_FRAMEBUFFER_UNSUPPORTED:
        return "GL_FRAMEBUFFER_UNSUPPORTED";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
    default:
        throw std::invalid_argument("[FramebufferTarget] Unexpected status!");
    }
}

/**
 * Returns the maximum number of color attachments a framebuffer can have.
 *
 * @return Maximum number of color attachments a framebuffer can have
 */
GLint FramebufferTarget::getMaxColorAttachments() {
    GLint value;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &value);
    return value;
}

/**
 * Checks if an OpenGL enumeration represents a valid framebuffer attachment.
 *
 * @param enumeration OpenGL enumeration to check
 * @return `true` if enumeration represents a valid framebuffer attachment
 */
bool FramebufferTarget::isAttachment(const GLenum enumeration) {
    switch (enumeration) {
    case GL_DEPTH_ATTACHMENT:
    case GL_DEPTH_STENCIL_ATTACHMENT:
    case GL_STENCIL_ATTACHMENT:
        return true;
    default:
        return isColorAttachment(enumeration);
    }
}

/**
 * Checks if an OpenGL enumeration represents a valid framebuffer color attachment.
 *
 * @param enumeration OpenGL enumeration to check
 * @return `true` if enumeration represents a valid framebuffer color attachment
 */
bool FramebufferTarget::isColorAttachment(const GLenum enumeration) {
    if (enumeration < GL_COLOR_ATTACHMENT0) {
        return false;
    } else if (enumeration >= GL_COLOR_ATTACHMENT0 + getMaxColorAttachments()) {
        return false;
    } else {
        return true;
    }
}

/**
 * Checks if this framebuffer target represents a different framebuffer than another target.
 *
 * @param target Framebuffer target to check
 * @return `true` if this framebuffer target represents a different framebuffer than the given target
 */
bool FramebufferTarget::operator!=(const FramebufferTarget& target) const {
    return _id != target._id;
}

/**
 * Compares this framebuffer target to another framebuffer target.
 *
 * @param target Target to compare to
 * @return `true` if this framebuffer target's identifier is less than that of the other target
 */
bool FramebufferTarget::operator<(const FramebufferTarget& target) const {
    return _id < target._id;
}

/**
 * Changes which framebuffer this target represents.
 *
 * @param target Target to copy identifier from
 * @return Reference to this framebuffer target to support chaining
 */
FramebufferTarget& FramebufferTarget::operator=(const FramebufferTarget& target) {
    _id = target._id;
    _str = target._str;
    _key = target._key;
    return (*this);
}

/**
 * Checks if this target represents the same OpenGL framebuffer as another target.
 *
 * @param target Target to compare to
 * @return `true` if this target represents the same OpenGL framebuffer as another target
 */
bool FramebufferTarget::operator==(const FramebufferTarget& target) const {
    return _id == target._id;
}

/**
 * Returns the target for the framebuffer to read from.
 *
 * @return Target for the framebuffer to read from
 */
FramebufferTarget FramebufferTarget::readFramebuffer() {
    return FramebufferTarget(GL_READ_FRAMEBUFFER, "GL_READ_FRAMEBUFFER", GL_READ_FRAMEBUFFER_BINDING);
}

/**
 * Attaches a renderbuffer to the framebuffer currently bound to this target.
 *
 * @param attachment Framebuffer attachment to attach to, e.g. `GL_COLOR_ATTACHMENT0`
 * @param rbo Renderbuffer to attach
 * @pre A framebuffer is currently bound to this target
 * @pre Attachment is a valid framebuffer attachment type
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glFramebufferRenderbuffer.xml
 */
void FramebufferTarget::renderbuffer(const GLenum attachment, const RenderbufferObject& rbo) const {
    assert (bound());
    assert (isAttachment(attachment));
    glFramebufferRenderbuffer(_id, attachment, GL_RENDERBUFFER, rbo.id());
}

/**
 * Attaches a one-dimensional texture to this framebuffer.
 *
 * @param attachment Attachment to attach to
 * @param target What type of texture is being attached
 * @param texture Texture object to attach
 * @param level Mipmap level of texture object to attach
 */
void FramebufferTarget::texture1d(const GLenum attachment,
                                  const TextureTarget target,
                                  const TextureObject texture,
                                  const GLint level) const {
    assert (isAttachment(attachment));
    assert (level >= 0);
    glFramebufferTexture1D(_id, attachment, target.toEnum(), texture.id(), level);
}

/**
 * Attaches a two-dimensional texture to this framebuffer.
 *
 * @param attachment Attachment to attach to
 * @param target What type of texture is being attached
 * @param texture Texture object to attach
 * @param level Mipmap level of texture object to attach
 */
void FramebufferTarget::texture2d(const GLenum attachment,
                                  const TextureTarget target,
                                  const TextureObject texture,
                                  const GLint level) const {
    assert (isAttachment(attachment));
    assert (level >= 0);
    glFramebufferTexture2D(_id, attachment, target.toEnum(), texture.id(), level);
}

/**
 * Attaches a layer of a three-dimensional texture to this framebuffer.
 *
 * @param attachment Attachment to attach to
 * @param target What type of texture is being attached
 * @param texture Texture object to attach
 * @param level Mipmap level of texture object to attach
 * @param layer Layout of texture to attach
 */
void FramebufferTarget::texture3d(const GLenum attachment,
                                  const TextureTarget target,
                                  const TextureObject texture,
                                  const GLint level,
                                  const GLint layer) const{
    assert (isAttachment(attachment));
    assert (level >= 0);
    assert (layer >= 0);
    glFramebufferTexture3D(_id, attachment, target.toEnum(), texture.id(), level, layer);
}

/**
 * Returns the OpenGL enumeration for this framebuffer target.
 *
 * @return OpenGL enumeration for this framebuffer target
 */
GLenum FramebufferTarget::toEnum() const {
    return _id;
}

/**
 * Returns a string descriptor of this framebuffer target.
 *
 * @return String descriptor of this framebuffer target
 */
std::string FramebufferTarget::toString() const {
    return _str;
}

/**
 * Unbinds any currently bound framebuffer object.
 *
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindFramebuffer.xml
 */
void FramebufferTarget::unbind() const {
    glBindFramebuffer(_id, 0);
}

} /* namespace Gloop */

std::ostream& operator<<(std::ostream& stream, const Gloop::FramebufferTarget& target) {
    stream << target.toString();
    return stream;
}

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
#ifndef GLOOP_TEXTURETARGET_HXX
#define GLOOP_TEXTURETARGET_HXX
#include "gloop/common.h"
#include "gloop/TextureObject.hxx"
namespace Gloop {


/**
 * Part of a texture unit that a texture object can be bound to.
 *
 * A _TextureTarget_ represents one of the OpenGL texture targets that texture
 * objects can be bound to, e.g. `GL_TEXTURE_1D`, `GL_TEXTURE_2D`, or
 * `GL_TEXTURE_3D`.  To get a handle to one, use one of the @ref texture1d, @ref
 * texture2d, or @ref texture3d methods.
 *
 * ~~~
 *     TextureTarget target = TextureTarget::texture2d();
 * ~~~
 *
 * You can change which texture target an instance represents using the
 * assignment operator.
 *
 * ~~~
 *     target = TextureTarget::texture3d();
 * ~~~
 *
 * If you don't plan on changing which one an instance represents, you can mark
 * the instance as `const`.
 *
 * ~~~
 *     const TextureTarget target = TextureTarget::texture2d();
 * ~~~
 *
 * To bind a texture object to the target, create a texture object and then use
 * the @ref bind method.
 *
 * ~~~
 *     const TextureObject texture = TextureObject::generate();
 *     target.bind(texture);
 * ~~~
 *
 * Once you have a texture object bound, you can manipulate it using the methods
 * in _TextureTarget_.  To specify an image for the texture, use the approriate
 * _texImage_ method for the dimension, either @ref texImage1d, @ref texImage2d,
 * or @ref texImage3d.
 *
 * ~~~
 *     target.texImage2d(...);
 * ~~~
 *
 * You can access and modify texture parameters using the appropriate getters
 * and setters.  For example, often if you haven't generated mipmaps you'll need
 * to change the minification filter to either `GL_LINEAR` or `GL_NEAREST` since
 * the default value uses `GL_NEAREST_MIPMAP_LINEAR`.
 *
 * ~~~
 *     target.minFilter(GL_LINEAR);
 * ~~~
 */
class TextureTarget {
// Friends
    friend std::ostream& operator<<(std::ostream& stream, const TextureTarget& textureTarget);
public:
// Methods
    TextureTarget(const TextureTarget& textureTarget);
    virtual ~TextureTarget();
    GLsizei alphaSize(GLint level = 0) const;
    GLenum alphaType(GLint level = 0) const;
    GLint baseLevel() const;
    void baseLevel(GLint baseLevel) const;
    void bind(const TextureObject& textureObject) const;
    TextureObject binding() const;
    GLsizei blueSize(GLint level = 0) const;
    GLenum blueType(GLint level = 0) const;
    bool bound(const TextureObject& textureObject) const;
    GLenum compareFunc() const;
    void compareFunc(GLenum compareFunc) const;
    GLenum compareMode() const;
    void compareMode(GLenum compareMode) const;
    bool compressed(GLint level = 0) const;
    GLsizei compressedImageSize(GLint level = 0) const;
    GLsizei depth(GLint level = 0) const;
    static TextureTarget fromEnum(GLenum enumeration);
    void generateMipmap() const;
    GLsizei greenSize(GLint level = 0) const;
    GLenum greenType(GLint level = 0) const;
    GLsizei height(GLint level = 0) const;
    GLenum internalFormat(GLint level = 0) const;
    GLfloat lodBias() const;
    void lodBias(GLfloat lodBias) const;
    GLenum magFilter() const;
    void magFilter(GLenum magFilter) const;
    GLint maxLevel() const;
    void maxLevel(GLint maxLevel) const;
    GLfloat maxLod() const;
    void maxLod(GLfloat maxLod) const;
    GLenum minFilter() const;
    void minFilter(GLenum minFilter) const;
    GLfloat minLod() const;
    void minLod(GLfloat minLod) const;
    bool operator!=(const TextureTarget& textureTarget) const;
    bool operator<(const TextureTarget& textureTarget) const;
    TextureTarget& operator=(const TextureTarget& textureTarget);
    bool operator==(const TextureTarget& textureTarget) const;
    GLsizei redSize(GLint level = 0) const;
    GLenum redType(GLint level = 0) const;
    void texImage1d(GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid*) const;
    void texImage2d(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*) const;
    void texImage3d(GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*) const;
    void texSubImage1d(GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid*) const;
    void texSubImage2d(GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*) const;
    void texSubImage3d(GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*) const;
    static TextureTarget texture1d();
    static TextureTarget texture1dArray();
    static TextureTarget texture2d();
    static TextureTarget texture2dArray();
    static TextureTarget texture3d();
    static TextureTarget textureBuffer();
    static TextureTarget textureCubeMap();
    static TextureTarget textureRectangle();
    GLenum toEnum() const;
    GLsizei width(GLint level = 0) const;
    GLenum wrapR() const;
    void wrapR(GLenum wrapR) const;
    GLenum wrapS() const;
    void wrapS(GLenum wrapS) const;
    GLenum wrapT() const;
    void wrapT(GLenum wrapT) const;
private:
// Attributes
    GLenum _id;
    GLenum _key;
    std::string _name;
// Methods
    TextureTarget(GLenum id, GLenum key, const std::string& name);
    static GLfloat getMaxTextureLodBias();
    static GLsizei getMaxTextureSize();
    GLint getTexLevelParameteri(GLint level, GLenum name) const;
    GLfloat getTexParameterf(GLenum name) const;
    GLint getTexParameteri(GLenum name) const;
    static bool isAbleToGenerateMipmapFor(GLenum enumeration);
    static bool isCompareFunc(GLenum enumeration);
    static bool isCompareMode(GLenum enumeration);
    static bool isComponentType(GLenum enumeration);
    static bool isDataFormat(GLenum enumeration);
    static bool isDataType(GLenum enumeration);
    static bool isInternalFormat(GLenum enumeration);
    static bool isLodBias(GLfloat value);
    static bool isMagFilter(GLenum enumeration);
    static bool isMinFilter(GLenum enumeration);
    static bool isSingleValuedTextureParameter(GLenum enumeration);
    static bool isTexImage1dTarget(GLenum enumeration);
    static bool isTexImage2dTarget(GLenum enumeration);
    static bool isTexImage3dTarget(GLenum enumeration);
    static bool isWrap(GLenum enumeration);
    void texParameteri(GLenum name, GLint value) const;
    void texParameterf(GLenum name, GLfloat value) const;
};

} /* namespace Gloop */
#endif

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
#include "config.h"
#include <cassert>
#include <stdexcept>
#include "gloop/TextureTarget.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs a texture target from an ID, key, and name.
 *
 * @param id Identifier of texture target
 * @param key Value used to query which texture object is bound to the target
 * @param name Human-readable name of the texture target
 */
TextureTarget::TextureTarget(const GLenum id,
                             const GLenum key,
                             const std::string& name) :
        _id(id),
        _key(key),
        _name(name) {
    // empty
}

/**
 * Constructs a texture target by copying another one.
 *
 * @param textureTarget Texture target to copy
 */
TextureTarget::TextureTarget(const TextureTarget& textureTarget) :
        _id(textureTarget._id),
        _key(textureTarget._key),
        _name(textureTarget._name) {
    // empty
}

/**
 * Destroys this texture target handle, leaving the corresponding OpenGL texture target unaffected.
 *
 * @see @ref dispose
 */
TextureTarget::~TextureTarget() {
    // empty
}

/**
 * Retrieves the size of the alpha component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail number, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Size of the alpha component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::alphaSize(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_ALPHA_SIZE);
}

/**
 * Retrieves the type of the alpha component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Type of the alpha component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLenum TextureTarget::alphaType(const GLint level) const {
    const GLenum value = getTexLevelParameteri(level, GL_TEXTURE_ALPHA_TYPE);
    assert (isComponentType(value));
    return value;
}

/**
 * Retrieves the index of the lowest defined mipmap level.
 *
 * @return Index of the lowest defined mipmap level
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLint TextureTarget::baseLevel() const {
    return getTexParameteri(GL_TEXTURE_BASE_LEVEL);
}

/**
 * Changes the index of the lowest defined mipmap level.
 *
 * @param baseLevel Index of the lowest defined mipmap level
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::baseLevel(const GLint baseLevel) const {
    texParameteri(GL_TEXTURE_BASE_LEVEL, baseLevel);
}

/**
 * Binds a texture object to the texture target.
 *
 * @param textureObject Texture object to bind to this texture target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glBindTexture.xml
 */
void TextureTarget::bind(const TextureObject& textureObject) const {
    glBindTexture(_id, textureObject.id());
}

/**
 * Determines the texture object bound to this texture target.
 *
 * @return Texture object bound to this texture target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGet.xml
 */
TextureObject TextureTarget::binding() const {
    GLint id;
    glGetIntegerv(_key, &id);
    return TextureObject::fromId((GLuint) id);
}

/**
 * Retrieves the size of the blue component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail number, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Size of the blue component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::blueSize(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_BLUE_SIZE);
}

/**
 * Retrieves the type of the blue component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Type of the blue component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLenum TextureTarget::blueType(const GLint level) const {
    const GLenum value = getTexLevelParameteri(level, GL_TEXTURE_BLUE_TYPE);
    assert (isComponentType(value));
    return value;
}

/**
 * Checks if a texture object is bound to this texture target.
 *
 * @param textureObject Texture object to check for
 * @return `true` if the texture object is bound to this texture target
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGet.xml
 */
bool TextureTarget::bound(const TextureObject& textureObject) const {
    return binding() == textureObject;
}

/**
 * Retrieves the comparison operator used when `GL_TEXTURE_COMPARE_MODE` is set to `GL_COMPARE_REF_TO_TEXTURE`.
 *
 * @return Comparison operator used when `GL_TEXTURE_COMPARE_MODE` is set to `GL_COMPARE_REF_TO_TEXTURE`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::compareFunc() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_COMPARE_FUNC);
    assert (isCompareFunc(value));
    return value;
}

/**
 * Changes the comparison operator used when `GL_TEXTURE_COMPARE_MODE` is set to `GL_COMPARE_REF_TO_TEXTURE`.
 *
 * @param compareFunc Comparison operator used when `GL_TEXTURE_COMPARE_MODE` is set to `GL_COMPARE_REF_TO_TEXTURE`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::compareFunc(const GLenum compareFunc) const {
    assert (isCompareFunc(compareFunc));
    texParameteri(GL_TEXTURE_COMPARE_FUNC, compareFunc);
}

/**
 * Retrieves the comparison mode for currently bound depth textures.
 *
 * @return Comparison mode for currently bound depth textures
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::compareMode() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_COMPARE_MODE);
    assert (isCompareMode(value));
    return value;
}

/**
 * Changes the comparison mode for currently bound depth textures.
 *
 * @param compareMode Comparison mode for currently bound depth textures
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::compareMode(const GLenum compareMode) const {
    assert (isCompareMode(compareMode));
    texParameteri(GL_TEXTURE_COMPARE_MODE, compareMode);
}

/**
 * Checks if an image of the texture object currently bound to this texture is compressed.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return `true` if the specified image is compressed
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
bool TextureTarget::compressed(const GLint level) const {
    return getTexLevelParameteri(level, GL_TEXTURE_COMPRESSED);
}

/**
 * Retrieves the compressed size of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Compressed size of the specified image, in bytes
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::compressedImageSize(const GLint level) const {
    assert (compressed());
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
}

/**
 * Retrieves the depth of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Depth of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::depth(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_DEPTH);
}

/**
 * Finds a texture target by its OpenGL enumeration.
 *
 * @param enumeration Enumeration for texture target, e.g. GL_TEXTURE_2D
 * @throws invalid_argument if enumeration is invalid or unsupported
 */
TextureTarget TextureTarget::fromEnum(const GLenum enumeration) {
    switch (enumeration) {
    case GL_TEXTURE_1D:
        return texture1d();
    case GL_TEXTURE_1D_ARRAY:
        return texture1dArray();
    case GL_TEXTURE_2D:
        return texture2d();
    case GL_TEXTURE_2D_ARRAY:
        return texture2dArray();
    case GL_TEXTURE_3D:
        return texture3d();
    case GL_TEXTURE_BUFFER:
        return textureBuffer();
    case GL_TEXTURE_CUBE_MAP:
        return textureCubeMap();
    case GL_TEXTURE_RECTANGLE:
        return textureRectangle();
    default:
        throw invalid_argument("[TextureTarget] Invalid or unsupported enumeration!");
    }
}

/**
 * Generates mipmaps for the texture bound to this target.
 *
 * Note that the target must be one of:
 *  - `GL_TEXTURE_1D`
 *  - `GL_TEXTURE_2D`
 *  - `GL_TEXTURE_3D`
 *  - `GL_TEXTURE_1D_ARRAY`
 *  - `GL_TEXTURE_2D_ARRAY`
 *  - `GL_TEXTURE_CUBE_MAP`
 */
void TextureTarget::generateMipmap() const {
    assert (isAbleToGenerateMipmapFor(_id));
    glGenerateMipmap(_id);
}

/**
 * Retrieves absolute value of the texture level-of-detail bias.
 *
 * @return Absolute value of the texture level-of-detail bias
 */
GLfloat TextureTarget::getMaxTextureLodBias() {
    GLfloat value;
    glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS, &value);
    assert (value >= 2.0f);
    return value;
}

/**
 * Retrieves an estimate of the maximum texture size this OpenGL can handle.
 *
 * @return Estimate of the maximum texture size this OpenGL can handle, at least 1024
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGet.xml
 */
GLsizei TextureTarget::getMaxTextureSize() {
    GLint maxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    return maxTextureSize;
}

/**
 * Retrieves the value of a texture parameter for a specific level of detail.
 *
 * @param level Level of detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @param name Name of the texture parameter to determine value of
 * @return Value of texture parameter for level of detail
 * @pre Level of detail is greater than or equal to zero
 */
GLint TextureTarget::getTexLevelParameteri(const GLint level, const GLenum name) const {
    assert (level >= 0);
    GLint value;
    glGetTexLevelParameteriv(_id, level, name, &value);
    return value;
}

/**
 * Retrieves the value of a texture parameter as an integer.
 *
 * @param name Name of the texture parameter
 * @return Value of the specified texture parameter as an integer
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLint TextureTarget::getTexParameteri(const GLenum name) const {
    GLint value;
    glGetTexParameteriv(_id, name, &value);
    return value;
}

/**
 * Retrieves the value of a texture parameter as a float.
 *
 * @param name Name of the texture parameter
 * @return Value of the specified texture parameter as a float
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLfloat TextureTarget::getTexParameterf(const GLenum name) const {
    GLfloat value;
    glGetTexParameterfv(_id, name, &value);
    return value;
}

/**
 * Retrieves the size of the green component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Size of the green component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::greenSize(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_GREEN_SIZE);
}

/**
 * Retrieves the type of the green component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Type of the green component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLenum TextureTarget::greenType(const GLint level) const {
    const GLenum value = getTexLevelParameteri(level, GL_TEXTURE_GREEN_TYPE);
    assert (isComponentType(value));
    return value;
}

/**
 * Retrieves the height of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Height of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::height(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_HEIGHT);
}

/**
 * Retrieves the internal format of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Internal format of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLenum TextureTarget::internalFormat(const GLint level) const {
    const GLenum value = getTexLevelParameteri(level, GL_TEXTURE_INTERNAL_FORMAT);
    assert (isInternalFormat(value));
    return value;
}

/**
 * Checks if OpenGL is able to generate mipmaps for an enumeration.
 *
 * @param enumeration Enumeration to check
 * @return `true` if OpenGL is able to generate mipmaps for the enumeration
 */
bool TextureTarget::isAbleToGenerateMipmapFor(const GLenum enumeration) {
    switch (enumeration) {
    case GL_TEXTURE_1D:
    case GL_TEXTURE_2D:
    case GL_TEXTURE_3D:
    case GL_TEXTURE_1D_ARRAY:
    case GL_TEXTURE_2D_ARRAY:
    case GL_TEXTURE_CUBE_MAP:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid compare function.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid compare function
 */
bool TextureTarget::isCompareFunc(const GLenum enumeration) {
    switch (enumeration) {
    case GL_LEQUAL:
    case GL_GEQUAL:
    case GL_LESS:
    case GL_GREATER:
    case GL_EQUAL:
    case GL_NOTEQUAL:
    case GL_ALWAYS:
    case GL_NEVER:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid compare mode.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid compare mode
 */
bool TextureTarget::isCompareMode(const GLenum enumeration) {
    switch (enumeration) {
    case GL_COMPARE_REF_TO_TEXTURE:
    case GL_NONE:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid component type.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid component type
 */
bool TextureTarget::isComponentType(const GLenum enumeration) {
    switch (enumeration) {
    case GL_NONE:
    case GL_SIGNED_NORMALIZED:
    case GL_UNSIGNED_NORMALIZED:
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid format for texture data.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid format for texture data
 */
bool TextureTarget::isDataFormat(const GLenum enumeration) {
    switch (enumeration) {
    case GL_RED:
    case GL_RG:
    case GL_RGB:
    case GL_BGR:
    case GL_RGBA:
    case GL_BGRA:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid type for texture data.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid type for texture data
 */
bool TextureTarget::isDataType(const GLenum enumeration) {
    switch (enumeration) {
    case GL_UNSIGNED_BYTE:
    case GL_BYTE:
    case GL_UNSIGNED_SHORT:
    case GL_SHORT:
    case GL_UNSIGNED_INT:
    case GL_INT:
    case GL_FLOAT:
    case GL_UNSIGNED_BYTE_3_3_2:
    case GL_UNSIGNED_BYTE_2_3_3_REV:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_5_6_5_REV:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
    case GL_UNSIGNED_SHORT_5_5_5_1:
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
    case GL_UNSIGNED_INT_8_8_8_8:
    case GL_UNSIGNED_INT_8_8_8_8_REV:
    case GL_UNSIGNED_INT_10_10_10_2:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid internal format.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid internal format
 */
bool TextureTarget::isInternalFormat(const GLenum enumeration) {
    switch (enumeration) {

    /*
     * Base internal formats
     */
    case GL_DEPTH_COMPONENT:
    case GL_DEPTH_STENCIL:
    case GL_RED:
    case GL_RG:
    case GL_RGB:
    case GL_RGBA:

    /*
     * Compressed internal formats
     */
    case GL_COMPRESSED_RED:
    case GL_COMPRESSED_RG:
    case GL_COMPRESSED_RGB:
    case GL_COMPRESSED_RGBA:
    case GL_COMPRESSED_SRGB:
    case GL_COMPRESSED_SRGB_ALPHA:
    case GL_COMPRESSED_RED_RGTC1:
    case GL_COMPRESSED_SIGNED_RED_RGTC1:
//    case GL_COMPRESSED_RG_RGTC1:
    case GL_COMPRESSED_SIGNED_RG_RGTC2:
//    case GL_COMPRESSED_RGBA_BPTC_UNORM:
//    case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
//    case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:
//    case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:

    /*
     * Sized internal formats
     */
    case GL_R8:
    case GL_R8_SNORM:
    case GL_R16:
    case GL_R16_SNORM:
    case GL_RG8:
    case GL_RG8_SNORM:
    case GL_RG16:
    case GL_RG16_SNORM:
    case GL_R3_G3_B2:
    case GL_RGB4:
    case GL_RGB5:
    case GL_RGB8:
    case GL_RGB8_SNORM:
    case GL_RGB10:
    case GL_RGB12:
    case GL_RGB16_SNORM:
    case GL_RGBA2:
    case GL_RGBA4:
    case GL_RGB5_A1:
    case GL_RGBA8:
    case GL_RGBA8_SNORM:
    case GL_RGB10_A2:
//    case GL_RGB10_A2UI:
    case GL_RGBA12:
    case GL_RGBA16:
    case GL_SRGB8:
    case GL_SRGB8_ALPHA8:
    case GL_R16F:
    case GL_RG16F:
    case GL_RGB16F:
    case GL_RGBA16F:
    case GL_R32F:
    case GL_RG32F:
    case GL_RGB32F:
    case GL_RGBA32F:
    case GL_R11F_G11F_B10F:
    case GL_RGB9_E5:
    case GL_R8I:
    case GL_R8UI:
    case GL_R16I:
    case GL_R16UI:
    case GL_R32I:
    case GL_R32UI:
    case GL_RG8I:
    case GL_RG8UI:
    case GL_RG16I:
    case GL_RG16UI:
    case GL_RG32I:
    case GL_RG32UI:
    case GL_RGB8I:
    case GL_RGB8UI:
    case GL_RGB16I:
    case GL_RGB16UI:
    case GL_RGB32I:
    case GL_RGB32UI:
    case GL_RGBA8I:
    case GL_RGBA8UI:
    case GL_RGBA16I:
    case GL_RGBA16UI:
    case GL_RGBA32I:
    case GL_RGBA32UI:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if a value is a valid level-of-detail bias.
 *
 * @param value Value to check
 * @return `true` if value is a valid level-of-detail bias
 */
bool TextureTarget::isLodBias(const GLfloat value) {
    const GLfloat maxTextureLodBias = getMaxTextureLodBias();
    return (value >= -maxTextureLodBias) && (value <= maxTextureLodBias);
}

/**
 * Checks if an enumeration is a valid magnification filter.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid magnification filter
 */
bool TextureTarget::isMagFilter(const GLenum enumeration) {
    switch (enumeration) {
    case GL_NEAREST:
    case GL_LINEAR:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid minification filter.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid minification filter
 */
bool TextureTarget::isMinFilter(const GLenum enumeration) {
    switch (enumeration) {
    case GL_NEAREST:
    case GL_LINEAR:
    case GL_NEAREST_MIPMAP_NEAREST:
    case GL_LINEAR_MIPMAP_NEAREST:
    case GL_NEAREST_MIPMAP_LINEAR:
    case GL_LINEAR_MIPMAP_LINEAR:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid single-valued texture parameter.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid single-valued texture parameter
 */
bool TextureTarget::isSingleValuedTextureParameter(const GLenum enumeration) {
    switch (enumeration) {
    case GL_TEXTURE_BASE_LEVEL:
    case GL_TEXTURE_COMPARE_FUNC:
    case GL_TEXTURE_COMPARE_MODE:
    case GL_TEXTURE_LOD_BIAS:
    case GL_TEXTURE_MIN_FILTER:
    case GL_TEXTURE_MAG_FILTER:
    case GL_TEXTURE_MIN_LOD:
    case GL_TEXTURE_MAX_LOD:
    case GL_TEXTURE_MAX_LEVEL:
    case GL_TEXTURE_WRAP_S:
    case GL_TEXTURE_WRAP_T:
    case GL_TEXTURE_WRAP_R:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid target for _texImage1d_ or _texSubImage1d_.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid target for _texImage1d_ or _texSubImage1d_
 */
bool TextureTarget::isTexImage1dTarget(const GLenum enumeration) {
    return (enumeration == GL_TEXTURE_1D) || (enumeration == GL_PROXY_TEXTURE_1D);
}

/**
 * Checks if an enumeration is a valid target for _texImage2d_ or _texSubImage2d_.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid target for _texImage2d_ or _texSubImage2d_
 */
bool TextureTarget::isTexImage2dTarget(const GLenum enumeration) {
    switch (enumeration) {
    case GL_TEXTURE_2D:
    case GL_PROXY_TEXTURE_2D:
    case GL_TEXTURE_1D_ARRAY:
    case GL_PROXY_TEXTURE_1D_ARRAY:
    case GL_TEXTURE_RECTANGLE:
    case GL_PROXY_TEXTURE_RECTANGLE:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
    case GL_PROXY_TEXTURE_CUBE_MAP:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid target for _texImage3d_ or _texSubImage3d_.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid target for _texImage3d_ or _texSubImage3d_
 */
bool TextureTarget::isTexImage3dTarget(const GLenum enumeration) {
    switch (enumeration) {
    case GL_TEXTURE_3D:
    case GL_PROXY_TEXTURE_3D:
    case GL_TEXTURE_2D_ARRAY:
    case GL_PROXY_TEXTURE_2D_ARRAY:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if an enumeration is a valid value for `GL_TEXTURE_WRAP_S`, `GL_TEXTURE_WRAP_T`, or `GL_TEXTURE_WRAP_R`.
 *
 * @return `true` if enumeration is a valid value for `GL_TEXTURE_WRAP_S`, `GL_TEXTURE_WRAP_T`, or `GL_TEXTURE_WRAP_R`
 */
bool TextureTarget::isWrap(const GLenum enumeration) {
    switch (enumeration) {
    case GL_CLAMP_TO_EDGE:
    case GL_CLAMP_TO_BORDER:
    case GL_MIRRORED_REPEAT:
    case GL_REPEAT:
        return true;
    default:
        return false;
    }
}

/**
 * Retrieves the fixed bias value that is added to the level-of-detail parameter before texture sampling.
 *
 * @return Fixed bias value that is added to the level-of-detail parameter before texture sampling
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLfloat TextureTarget::lodBias() const {
    const GLfloat value = getTexParameterf(GL_TEXTURE_LOD_BIAS);
    assert (isLodBias(value));
    return value;
}

/**
 * Changes the fixed bias value that is added to the level-of-detial parameter before texture sampling.
 *
 * @param lodBias Fixed bias value that is added to the level-of-detail parameter before texture sampling
 * @pre Value is in [-_max_, _max_] where, _max_ is equal to `GL_MAX_TEXTURE_LOD_BIAS`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::lodBias(const GLfloat lodBias) const {
    assert (isLodBias(lodBias));
    texParameterf(GL_TEXTURE_LOD_BIAS, lodBias);
}

/**
 * Retrieves the function used to sample from a texture that needs to be magnified.
 *
 * @return Function used to sample from a texture that needs to be magnified
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::magFilter() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_MAG_FILTER);
    assert (isMagFilter(value));
    return value;
}

/**
 * Changes the function used to sample from a texture that needs to be magnified.
 *
 * @param magFilter Function used to sample from a texture that needs to be magnified
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::magFilter(const GLenum magFilter) const {
    assert (isMagFilter(magFilter));
    texParameteri(GL_TEXTURE_MAG_FILTER, magFilter);
}

/**
 * Retrieves the index of the highest defined mipmap level.
 *
 * @return Index of the highest defined mipmap level
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLint TextureTarget::maxLevel() const {
    return getTexParameteri(GL_TEXTURE_MAX_LEVEL);
}

/**
 * Changes the index of the highest defined mipmap level.
 *
 * @param maxLevel Index of the highest defined mipmap level
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::maxLevel(const GLint maxLevel) const {
    texParameteri(GL_TEXTURE_MAX_LEVEL, maxLevel);
}

/**
 * Retrieves the maximum level-of-detail, which limits the selection of the lowest resolution mipmap.
 *
 * @return Maximum level-of-detail, which limits the selection of the highest resolution mipmap
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLfloat TextureTarget::maxLod() const {
    return getTexParameterf(GL_TEXTURE_MAX_LOD);
}

/**
 * Changes the maximum level-of-detail, which limits the selection of the lowest resolution mipmap.
 *
 * @param maxLod Maximum level-of-detail, which limits the selection of the lowest resolution mipmap
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::maxLod(const GLfloat maxLod) const {
    texParameterf(GL_TEXTURE_MAX_LOD, maxLod);
}

/**
 * Retrieves the function used to sample from a texture that needs to be minified.
 *
 * @return Function used to sample from a texture that needs to be minified
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::minFilter() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_MIN_FILTER);
    assert (isMinFilter(value));
    return value;
}

/**
 * Changes the function used to sample from a texture that needs to be minified.
 *
 *  - `GL_NEAREST`
 *  - `GL_LINEAR`
 *  - `GL_NEAREST_MIPMAP_NEAREST`
 *  - `GL_LINEAR_MIPMAP_NEAREST`
 *  - `GL_NEAREST_MIPMAP_LINEAR`
 *  - `GL_LINEAR_MIPMAP_LINEAR`
 *
 * @param minFilter Function used to sample from a texture that needs to be minified
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::minFilter(const GLenum minFilter) const {
    assert (isMinFilter(minFilter));
    texParameteri(GL_TEXTURE_MIN_FILTER, minFilter);
}

/**
 * Retrieves the minimum level-of-detail, which limits the selection of the highest resolution mipmap.
 *
 * @return Minimum level-of-detail, which limits the selection of the highest resolution mipmap
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLfloat TextureTarget::minLod() const {
    return getTexParameterf(GL_TEXTURE_MIN_LOD);
}

/**
 * Changes the minimum level-of-detail, which limits the selection of the highest resolution mipmap.
 *
 * @param minLod Minimum level-of-detail, which limits the selection of the highest resolution mipmap
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::minLod(const GLfloat minLod) const {
    texParameterf(GL_TEXTURE_MIN_LOD, minLod);
}

/**
 * Checks if this texture target represents a different OpenGL texture target than another one.
 *
 * @param textureTarget Texture target to compare to
 * @return `true` if this texture target represents a different OpenGL texture target than another one
 */
bool TextureTarget::operator!=(const TextureTarget& textureTarget) const {
    return _id != textureTarget._id;
}

/**
 * Compares another texture target to this texture target.
 *
 * @param textureTarget Other texture target to compare
 * @return `true` if this texture target is less than the other one
 */
bool TextureTarget::operator<(const TextureTarget& textureTarget) const {
    return _id < textureTarget._id;
}

/**
 * Inserts the name of a texture target into a stream.
 *
 * @param stream Stream to insert name of a texture target into
 * @param textureTarget Texture target to insert name of into stream
 * @return Reference to the stream to support chaining
 */
std::ostream& operator<<(std::ostream& stream, const TextureTarget& textureTarget) {
    stream << textureTarget._name;
    return stream;
}

/**
 * Changes which OpenGL texture target this instance represents by copying another one.
 *
 * @param textureTarget Texture target to copy
 * @return Reference to this texture target to support chaining
 */
TextureTarget& TextureTarget::operator=(const TextureTarget& textureTarget) {
    this->_id = textureTarget._id;
    this->_key = textureTarget._key;
    this->_name = textureTarget._name;
    return (*this);
}

/**
 * Checks if this texture target is the same as another one.
 *
 * @param textureTarget Other texture target to check
 * @return `true` if this texture target is the same as the other one
 */
bool TextureTarget::operator==(const TextureTarget& textureTarget) const {
    return _id == textureTarget._id;
}

/**
 * Retrieves the size of the red component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Size of the red component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::redSize(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_RED_SIZE);
}

/**
 * Retrieves the type of the red component of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Type of the red component of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLenum TextureTarget::redType(const GLint level) const {
    const GLenum value = getTexLevelParameteri(level, GL_TEXTURE_RED_TYPE);
    assert (isComponentType(value));
    return value;
}

/**
 * Specifies a one-dimensional image for the texture bound to this texture target.
 *
 * @param level Level-of-detail number, with `0` being the base image level, and _n_ being the _nth_ mipmap
 * @param internalFormat Format of the data when it is stored on the graphics card, e.g. `GL_COMPRESSED_RED`
 * @param width Width of the texture image, with all implementations supporting at least `1024`
 * @param format Format of the pixel data, e.g. `GL_RED`
 * @param type Data type of the pixel data, e.g. `GL_UNSIGNED_BYTE`
 * @param data Pointer to the image data in memory
 * @pre Texture target is `GL_TEXTURE_1D`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage1D.xml
 */
void TextureTarget::texImage1d(const GLint level,
                               const GLint internalFormat,
                               const GLsizei width,
                               const GLenum format,
                               const GLenum type,
                               const GLvoid* data) const {
    assert (isTexImage1dTarget(_id));
    assert (level >= 0);
    assert (isInternalFormat(internalFormat));
    assert (width <= getMaxTextureSize());
    assert (isDataFormat(format));
    assert (isDataType(type));
    glTexImage1D(_id, level, internalFormat, width, 0, format, type, data);
}

/**
 * Specifies a two-dimensional image for the texture bound to this texture target.
 *
 * @param level Level-of-detail number, with `0` being the base image level, and _n_ being the _nth_ mipmap
 * @param internalFormat Format of the data when it is stored on the graphics card, e.g. `GL_COMPRESSED_RED`
 * @param width Width of the texture image, with all implementations supporting at least `1024`
 * @param height Height of the texture image, with all implementations supporting at least `1024`
 * @param format Format of the pixel data, e.g. `GL_RED`
 * @param type Data type of the pixel data, e.g. `GL_UNSIGNED_BYTE`
 * @param data Pointer to the image data in memory
 * @pre Texture target is `GL_TEXTURE_2D`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage2D.xml
 */
void TextureTarget::texImage2d(const GLint level,
                               const GLint internalFormat,
                               const GLsizei width,
                               const GLsizei height,
                               const GLenum format,
                               const GLenum type,
                               const GLvoid* data) const {
    assert (isTexImage2dTarget(_id));
    assert (level >= 0);
    assert (isInternalFormat(internalFormat));
    assert (width <= getMaxTextureSize());
    assert (height <= getMaxTextureSize());
    assert (isDataFormat(format));
    assert (isDataType(type));
    glTexImage2D(_id, level, internalFormat, width, height, 0, format, type, data);
}

/**
 * Specifies a three-dimensional image for the texture bound to this texture target.
 *
 * @param level Level-of-detail number, with `0` being the base image level, and _n_ being the _nth_ mipmap
 * @param internalFormat Format of the data when it is stored on the graphics card, e.g. `GL_COMPRESSED_RED`
 * @param width Width of the texture image, with all implementations supporting at least `1024`
 * @param height Height of the texture image, with all implementations supporting at least `1024`
 * @param depth Depth of the texture image, with all implementations supporting at least `1024`
 * @param format Format of the pixel data, e.g. `GL_RED`
 * @param type Data type of the pixel data, e.g. `GL_UNSIGNED_BYTE`
 * @param data Pointer to the image data in memory
 * @pre Texture target is `GL_TEXTURE_3D`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage3D.xml
 */
void TextureTarget::texImage3d(const GLint level,
                               const GLint internalFormat,
                               const GLsizei width,
                               const GLsizei height,
                               const GLsizei depth,
                               const GLenum format,
                               const GLenum type,
                               const GLvoid* data) const {
    assert (isTexImage3dTarget(_id));
    assert (level >= 0);
    assert (isInternalFormat(internalFormat));
    assert (width <= getMaxTextureSize());
    assert (height <= getMaxTextureSize());
    assert (depth <= getMaxTextureSize());
    assert (isDataFormat(format));
    assert (isDataType(type));
    glTexImage3D(_id, level, internalFormat, width, height, depth, 0, format, type, data);
}

/**
 * Sets a texture parameter.
 *
 * @param name Name of the texture parameter
 * @param value Value of the texture parameter
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::texParameteri(const GLenum name, const GLint value) const {
    assert (isSingleValuedTextureParameter(name));
    glTexParameteri(_id, name, value);
}

/**
 * Sets a texture parameter.
 *
 * @param name Name of the texture parameter
 * @param value Value of the texture parameter
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::texParameterf(const GLenum name, const GLfloat value) const {
    assert (isSingleValuedTextureParameter(name));
    glTexParameterf(_id, name, value);
}

/**
 * Replaces part of a one-dimensional texture.
 *
 * @param level Level-of-detail number, with `0` being the base image level, and _n_ being the _nth_ mipmap
 * @param xOffset Texel offset in X direction within texture to start replacing
 * @param width Width of the part being replaced
 * @param format Format of the pixel data, e.g. `GL_RED`
 * @param type Data type of the pixel data, e.g. `GL_UNSIGNED_BYTE`
 * @param data Pointer to the image data in memory
 * @pre Texture target is `GL_TEXTURE_1D`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexSubImage1D.xml
 */
void TextureTarget::texSubImage1d(const GLint level,
                                  const GLint xOffset,
                                  const GLsizei width,
                                  const GLenum format,
                                  const GLenum type,
                                  const GLvoid* data) const {
    assert (isTexImage1dTarget(_id));
    assert (level >= 0);
    assert (width >= 0);
    assert (isDataFormat(format));
    assert (isDataType(type));
    glTexSubImage1D(_id, level, xOffset, width, format, type, data);
}

/**
 * Replaces part of a two-dimensional texture.
 *
 * @param level Level-of-detail number, with `0` being the base image level, and _n_ being the _nth_ mipmap
 * @param xOffset Texel offset in X direction within texture to start replacing
 * @param yOffset Texel offset in Y direction within texture to start replacing
 * @param width Width of the part being replaced
 * @param height Height of the part being replaced
 * @param format Format of the pixel data, e.g. `GL_RED`
 * @param type Data type of the pixel data, e.g. `GL_UNSIGNED_BYTE`
 * @param data Pointer to the image data in memory
 * @pre Texture target is `GL_TEXTURE_2D`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexSubImage2D.xml
 */
void TextureTarget::texSubImage2d(const GLint level,
                                  const GLint xOffset,
                                  const GLint yOffset,
                                  const GLsizei width,
                                  const GLsizei height,
                                  const GLenum format,
                                  const GLenum type,
                                  const GLvoid* data) const {
    assert (isTexImage2dTarget(_id));
    assert (level >= 0);
    assert (width >= 0);
    assert (height >= 0);
    assert (isDataFormat(format));
    assert (isDataType(type));
    glTexSubImage2D(_id, level, xOffset, yOffset, width, height, format, type, data);
}

/**
 * Replaces part of a three-dimensional texture.
 *
 * @param level Level-of-detail number, with `0` being the base image level, and _n_ being the _nth_ mipmap
 * @param xOffset Texel offset in X direction within texture to start replacing
 * @param yOffset Texel offset in Y direction within texture to start replacing
 * @param zOffset Texel offset in Z direction within texture to start replacing
 * @param width Width of the part being replaced
 * @param height Height of the part being replaced
 * @param depth Depth of the part being replaced
 * @param format Format of the pixel data, e.g. `GL_RED`
 * @param type Data type of the pixel data, e.g. `GL_UNSIGNED_BYTE`
 * @param data Pointer to the image data in memory
 * @pre Texture target is `GL_TEXTURE_3D`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexSubImage3D.xml
 */
void TextureTarget::texSubImage3d(const GLint level,
                                  const GLint xOffset,
                                  const GLint yOffset,
                                  const GLint zOffset,
                                  const GLsizei width,
                                  const GLsizei height,
                                  const GLsizei depth,
                                  const GLenum format,
                                  const GLenum type,
                                  const GLvoid* data) const {
    assert (isTexImage3dTarget(_id));
    assert (level >= 0);
    assert (width >= 0);
    assert (height >= 0);
    assert (depth >= 0);
    assert (isDataFormat(format));
    assert (isDataType(type));
    glTexSubImage3D(_id, level, xOffset, yOffset, zOffset, width, height, depth, format, type, data);
}

/**
 * Returns a handle to the one-dimensional texture target.
 *
 * @return Handle to the one-dimensional texture target
 */
TextureTarget TextureTarget::texture1d() {
    return TextureTarget(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, "GL_TEXTURE_1D");
}

/**
 * Returns a handle to the one-dimensional array texture target.
 *
 * @return Handle to the one-dimensional array texture target
 */
TextureTarget TextureTarget::texture1dArray() {
    return TextureTarget(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, "GL_TEXTURE_1D_ARRAY");
}

/**
 * Returns a handle to the two-dimensional texture target.
 *
 * @return Handle to the two-dimensional texture target
 */
TextureTarget TextureTarget::texture2d() {
    return TextureTarget(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, "GL_TEXTURE_2D");
}

/**
 * Returns a handle to the two-dimensional array texture target.
 *
 * @return Handle to the two-dimensional array texture target
 */
TextureTarget TextureTarget::texture2dArray() {
    return TextureTarget(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, "GL_TEXTURE_2D_ARRAY");
}

/**
 * Returns a handle to the three-dimensional texture target.
 *
 * @return Handle to the three-dimensional texture target
 */
TextureTarget TextureTarget::texture3d() {
    return TextureTarget(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, "GL_TEXTURE_3D");
}

/**
 * Returns a handle to the buffer texture target.
 *
 * @return Handle to the buffer texture target
 */
TextureTarget TextureTarget::textureBuffer() {
    return TextureTarget(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, "GL_TEXTURE_BUFFER");
}

/**
 * Returns a handle to the cube map texture target.
 *
 * @return Handle to the cube map texture target
 */
TextureTarget TextureTarget::textureCubeMap() {
    return TextureTarget(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BINDING_CUBE_MAP, "GL_TEXTURE_CUBE_MAP");
}

/**
 * Returns a handle to the rectangular texture target.
 *
 * @return Handle to the rectangular texture target
 */
TextureTarget TextureTarget::textureRectangle() {
    return TextureTarget(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, "GL_TEXTURE_RECTANGLE");
}

/**
 * Converts the texture target to an OpenGL enumeration.
 *
 * @return OpenGL enumeration corresponding to this texture target
 */
GLenum TextureTarget::toEnum() const {
    return _id;
}

/**
 * Retrieves the width of an image in the texture object bound to this texture target.
 *
 * @param level Level-of-detail of image, with `0` being the base level, and _n_ being the _nth_ mipmap
 * @return Width of the specified image
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexLevelParameter.xml
 */
GLsizei TextureTarget::width(const GLint level) const {
    return (GLsizei) getTexLevelParameteri(level, GL_TEXTURE_WIDTH);
}

/**
 * Retrieves the strategy for wrapping texture coordinates in the _r_ direction.
 *
 * @return Strategry for wrapping texture coordinates in the _r_ direction
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::wrapR() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_WRAP_R);
    assert (isWrap(value));
    return value;
}

/**
 * Changes the strategry for wrapping texture coordinates in the _r_ direction.
 *
 * @param wrapR Strategy for wrapping texture coordinates in the _r_ direction
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::wrapR(const GLenum wrapR) const {
    assert (isWrap(wrapR));
    texParameteri(GL_TEXTURE_WRAP_R, wrapR);
}

/**
 * Retrieves the strategy for wrapping texture coordinates in the _s_ direction.
 *
 * @return Strategry for wrapping texture coordinates in the _s_ direction
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::wrapS() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_WRAP_S);
    assert (isWrap(value));
    return value;
}

/**
 * Changes the strategry for wrapping texture coordinates in the _s_ direction.
 *
 * @param wrapS Strategy for wrapping texture coordinates in the _s_ direction
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::wrapS(const GLenum wrapS) const {
    assert (isWrap(wrapS));
    texParameteri(GL_TEXTURE_WRAP_S, wrapS);
}

/**
 * Retrieves the strategy for wrapping texture coordinates in the _t_ direction.
 *
 * @return Strategry for wrapping texture coordinates in the _t_ direction
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGetTexParameter.xml
 */
GLenum TextureTarget::wrapT() const {
    const GLenum value = getTexParameteri(GL_TEXTURE_WRAP_T);
    assert (isWrap(value));
    return value;
}

/**
 * Changes the strategy for wrapping texture coordinates in the _t_ direction.
 *
 * @param wrapT Strategy for wrapping texture coordinates in the _t_ direction
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glTexParameter.xml
 */
void TextureTarget::wrapT(const GLenum wrapT) const {
    assert (isWrap(wrapT));
    texParameteri(GL_TEXTURE_WRAP_T, wrapT);
}

} /* namespace Gloop */

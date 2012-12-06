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
#ifndef GLOOP_TEXTUREUNIT_HXX
#define GLOOP_TEXTUREUNIT_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Part of graphics card that manages a texture.
 *
 * In OpenGL, all textures are managed through a texture unit.  To use a
 * texture, you first create a texture object to hold the texture data, activate
 * a texture unit, then bind that texture object to one of the targets on that
 * texture unit.  See @ref TextureObject and @ref TextureTarget.
 *
 * Each texture unit can only hold one texture at a time, so the number of
 * textures you can access at once is limited to the total number of texture
 * units your graphics card has, which can be queried using `glGetIntegerv` and
 * `GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS`.  It will be at least `48`.
 *
 * By default, the first texture unit, represented as `GL_TEXTURE0`, is active.
 *
 * The example below binds a new texture as a 2D texture on the second texture
 * unit, filling it with data and changing its minification filter.
 *
 * ~~~
 *     // Activate the second texture unit
 *     const TextureUnit unit = TextureUnit::fromEnum(GL_TEXTURE1);
 *     unit.activate();
 *
 *     // Generate a new texture
 *     const TextureObject texture = TextureObject::generate();
 *
 *     // Bind it as a 2D texture
 *     const TextureTarget target = TextureTarget::texture2d();
 *     target.bind(texture);
 *
 *     // Fill it with data and change its minification filter
 *     target.texImage2d(0, GL_RED, 640, 480, GL_RED, GL_UNSIGNED_BYTE, data);
 *     target.minFilter(GL_LINEAR);
 * ~~~
 *
 * Note that when accessing a texture in a shader, the _sampler_ uniform takes
 * the zero-indexed number of the texture unit, not the ID of the texture
 * object.  For example, if you have two textures loaded, one on `GL_TEXTURE0`
 * and one on `GL_TEXTURE1`, the values of the _sampler_ uniforms for each will
 * be `0` and `1` respectively.  To get the zero-indexed number of a texture
 * unit, subtract `GL_TEXTURE0` from the symbolic name of the texture unit, or
 * just call `toOrdinal` on a _TextureUnit_ instance.
 *
 * ~~~
 *     const map<string,Uniform> uniforms = program.activeUniforms();
 *     const Uniform uniform = uniforms["texture"];
 *     uniform.load1i(unit.toOrdinal());
 * ~~~
 */
class TextureUnit {
// Friends
    friend std::ostream& operator<<(std::ostream& stream, const TextureUnit& textureUnit);
public:
// Methods
    TextureUnit(const TextureUnit& textureUnit);
    virtual ~TextureUnit();
    void activate() const;
    static TextureUnit active();
    static TextureUnit fromEnum(GLenum enumeration);
    static TextureUnit fromOrdinal(GLint ordinal);
    bool operator!=(const TextureUnit& textureUnit) const;
    bool operator<(const TextureUnit& textureUnit) const;
    TextureUnit& operator=(const TextureUnit& textureUnit);
    bool operator==(const TextureUnit& textureUnit) const;
    GLenum toEnum() const;
    GLint toOrdinal() const;
private:
// Constants
    static const GLint MIN_COMBINED_TEXTURE_IMAGE_UNITS = 48;
// Attributes
    GLenum _id;
// Methods
    TextureUnit(GLenum id);
    static bool isTextureUnitEnum(GLenum enumeration);
    static bool isTextureUnitOrdinal(GLint ordinal);
    static GLint maxCombinedTextureImageUnits();
};

} /* namespace Gloop */
#endif

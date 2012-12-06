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
#include "gloop/TextureUnit.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs a texture unit from an identifier.
 *
 * @param id OpenGL enumeration uniquely identifying texture unit
 */
TextureUnit::TextureUnit(const GLenum id) : _id(id) {
    // empty
}

/**
 * Constructs a texture unit by copying the identifier of another texture unit.
 *
 * @param textureUnit Texture unit to copy identifier from
 */
TextureUnit::TextureUnit(const TextureUnit& textureUnit) : _id(textureUnit._id) {
    // empty
}

/**
 * Destructs a texture unit handle, leaving the underlying OpenGL texture unit unaffected.
 */
TextureUnit::~TextureUnit() {
    // empty
}

/**
 * Activates this texture unit.
 */
void TextureUnit::activate() const {
    glActiveTexture(_id);
}

/**
 * Returns a handle to the active texture unit.
 *
 * @return Handle to the active texture unit
 */
TextureUnit TextureUnit::active() {
    GLint id;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &id);
    return TextureUnit((GLenum) id);
}

/**
 * Returns a handle to one of the OpenGL texture units given the symbolic name for it.
 *
 * @param enumeration Symbolic name of the desired texture unit, for example `GL_TEXTURE0`
 * @return Handle to the corresponding texture unit
 */
TextureUnit TextureUnit::fromEnum(const GLenum enumeration) {
    assert (isTextureUnitEnum(enumeration));
    return TextureUnit(enumeration);
}

/**
 * Returns a handle to one of the OpenGL texture unit given a number starting from zero.
 *
 * @param ordinal Number of texture unit, for example `0`
 * @return Handle to the corresponding texture unit
 */
TextureUnit TextureUnit::fromOrdinal(const GLint ordinal) {
    assert (isTextureUnitOrdinal(ordinal));
    return TextureUnit(GL_TEXTURE0 + ordinal);
}

/**
 * Checks if an enumeration represents a valid texture unit.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration represents a valid texture unit
 */
bool TextureUnit::isTextureUnitEnum(const GLenum enumeration) {
    return (enumeration >= GL_TEXTURE0) && (enumeration < GL_TEXTURE0 + maxCombinedTextureImageUnits());
}

/**
 * Checks if an ordinal represents a valid texture unit.
 *
 * @param ordinal Ordinal to check
 * @return `true` if ordinal represents a valid texture unit
 */
bool TextureUnit::isTextureUnitOrdinal(const GLint ordinal) {
    return (ordinal >= 0) && (ordinal < maxCombinedTextureImageUnits());
}

/**
 * Returns the number of texture units this implementation supports.
 *
 * @return Number of texture units this implementation supports
 */
GLint TextureUnit::maxCombinedTextureImageUnits() {
    GLint value;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &value);
    assert (value >= MIN_COMBINED_TEXTURE_IMAGE_UNITS);
    return value;
}

/**
 * Checks if this texture unit handle represents a different texture unit than another.
 *
 * @param textureUnit Other texture unit handle to compare against
 * @return `true` if other handle represents a different texture unit than this one
 */
bool TextureUnit::operator!=(const TextureUnit& textureUnit) const {
    return _id != textureUnit._id;
}

/**
 * Compares this texture unit handle to another one.
 *
 * @param textureUnit Other texture unit handle to compare to
 * @return `true` if this texture unit handle is less than the other one
 */
bool TextureUnit::operator<(const TextureUnit& textureUnit) const {
    return _id < textureUnit._id;
}

/**
 * Inserts the human-readable descriptor of a texture unit into a stream.
 *
 * @param stream Stream to insert descriptor into
 * @param textureUnit Texture unit to take descriptor of
 * @return Reference to the stream to support chaining
 */
std::ostream& operator<<(std::ostream& stream, const TextureUnit& textureUnit) {
    stream << "GL_TEXTURE" << textureUnit.toOrdinal();
    return stream;
}

/**
 * Changes which texture unit this handle represents.
 *
 * @param textureUnit Other texture unit for this handle to represent
 * @return Reference to this handle to support chaining
 */
TextureUnit& TextureUnit::operator=(const TextureUnit& textureUnit) {
    _id = textureUnit._id;
    return (*this);
}

/**
 * Checks if this handle represents the same texture unit as another one.
 *
 * @param textureUnit Other texture unit handle to compare to
 * @return `true` if this handle represents the same texture unit as the other one
 */
bool TextureUnit::operator==(const TextureUnit& textureUnit) const {
    return _id == textureUnit._id;
}

/**
 * Returns the symbolic name of this texture unit.
 *
 * @return Symbolic name of this texture unit, as in `GL_TEXTURE0`
 */
GLenum TextureUnit::toEnum() const {
    return _id;
}

/**
 * Returns the number of this texture unit.
 *
 * @return Number of this texture unit, as in `0`
 */
GLint TextureUnit::toOrdinal() const {
    return _id - GL_TEXTURE0;
}

} /* namespace Gloop */

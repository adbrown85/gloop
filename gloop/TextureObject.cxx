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
#include "gloop/TextureObject.hxx"
using namespace std;
namespace Gloop {

/**
 * Constructs a texture object handle from an ID.
 *
 * @param id Identifier of an existing OpenGL texture object
 */
TextureObject::TextureObject(GLuint id) : _id(id) {
    // empty
}

/**
 * Constructs a texture object handle by copying the raw OpenGL identifier from another one.
 *
 * @param textureObject Texture object to copy raw OpenGL identifier from
 */
TextureObject::TextureObject(const TextureObject& textureObject) : _id(textureObject._id) {
    // empty
}

/**
 * Destructs this texture object handle, leaving the underlying OpenGL texture object unaffected.
 */
TextureObject::~TextureObject() {
    // empty
}

/**
 * Deletes the corresponding OpenGL texture object.
 */
void TextureObject::dispose() const {
    glDeleteTextures(1, &_id);
}

/**
 * Creates a texture object handle representing an existing OpenGL texture object.
 *
 * @param id ID of the existing OpenGL texture object
 */
TextureObject TextureObject::fromId(const GLuint id) {
    return TextureObject(id);
}

/**
 * Creates a new texture object.
 *
 * @return Handle for the texture object
 */
TextureObject TextureObject::generate() {

    // Generate the texture
    GLuint id;
    glGenTextures(1, &id);

    // Check ID is valid
    assert (id > 0);
    assert (id != -1);

    // Return the texture object
    return TextureObject(id);
}


/**
 * Returns the raw OpenGL identifier of this texture object handle.
 *
 * @return Raw OpenGL identifier of this texture object handle
 */
GLuint TextureObject::id() const {
    return _id;
}

/**
 * Checks if this texture object has a different identifier than another one.
 *
 * @param textureObject Texture object to compare identifiers with
 * @return `true` if this texture object's identifier is different than the other one
 */
bool TextureObject::operator!=(const TextureObject& textureObject) const {
    return _id != textureObject._id;
}

/**
 * Checks if this texture object has an identifier that is less than the identifier of another one.
 *
 * @param textureObject Texture object to compare identifiers with
 * @return `true` if this texture object's identifier is less than the identifier of the other one
 */
bool TextureObject::operator<(const TextureObject& textureObject) const {
    return _id < textureObject._id;
}

/**
 * Inserts the identifier of a texture object into a stream.
 *
 * @param stream Stream to insert identifier of texture object into
 * @param textureObject Texture object to insert identifier of
 * @return Reference to the stream to support chaining
 */
std::ostream& operator<<(std::ostream& stream, const TextureObject& textureObject) {
    stream << textureObject._id;
    return stream;
}

/**
 * Changes which OpenGL texture object this instance represents by copying the identifier from another one.
 *
 * @param textureObject Texture object to copy identifier from
 * @return Reference to this texture object to support chaining
 */
TextureObject& TextureObject::operator=(const TextureObject& textureObject) {
    _id = textureObject._id;
    return (*this);
}

/**
 * Checks if this texture object has the same identifier as another one.
 *
 * @param textureObject Texture object to compare identifiers with
 * @return `true` if this texture object's identifier is the same as the other one
 */
bool TextureObject::operator==(const TextureObject& textureObject) const {
    return _id == textureObject._id;
}

} /* namespace Gloop */

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
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <GL/glfw.h>
#include "gloop/TextureTarget.hxx"
using namespace std;
using namespace Gloop;


/**
 * Unit test for TextureTarget.
 */
class TextureTargetTest {
public:

    /**
     * Ensures a TextureTarget can be added to an STL map.
     */
    void testAddToStlMap() {
        map<string,TextureTarget> targetsByName;
        targetsByName.insert(pair<string,TextureTarget>("GL_TEXTURE_1D", TextureTarget::texture1d()));
        targetsByName.insert(pair<string,TextureTarget>("GL_TEXTURE_2D", TextureTarget::texture2d()));
        targetsByName.insert(pair<string,TextureTarget>("GL_TEXTURE_3D", TextureTarget::texture3d()));
    }

    /**
     * Ensures a TextureTarget can be added to an STL set.
     */
    void testAddToStlSet() {
        set<TextureTarget> targets;
        targets.insert(TextureTarget::texture1d());
        targets.insert(TextureTarget::texture2d());
        targets.insert(TextureTarget::texture3d());
    }

    /**
     * Ensures a TextureTarget can be added to an STL vector.
     */
    void testAddToStlVector() {
        vector<TextureTarget> targets;
        targets.push_back(TextureTarget::texture1d());
        targets.push_back(TextureTarget::texture2d());
        targets.push_back(TextureTarget::texture3d());
    }

    /**
     * Ensures TextureTarget::alphaSize() return zero for GL_R8.
     */
    void testAlphaSizeWithR8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_R8, 12, GL_RED, GL_UNSIGNED_BYTE, NULL);

        // Check its alpha size
        CPPUNIT_ASSERT_EQUAL(0, target.alphaSize());
    }

    /**
     * Ensures TextureTarget::alphaSize() returns zero for GL_RG8.
     */
    void testAlphaSizeWithRg8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RG8, 12, GL_RG, GL_UNSIGNED_BYTE, NULL);

        // Check its alpha size
        CPPUNIT_ASSERT_EQUAL(0, target.alphaSize());
    }

    /**
     * Ensures TextureTarget::alphaSize() returns zero for GL_RGB8.
     */
    void testAlphaSizeWithRgb8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGB8, 12, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // Check its alpha size
        CPPUNIT_ASSERT_EQUAL(0, target.alphaSize());
    }

    /**
     * Ensures TextureTarget::alphaSize() returns eight for GL_RGBA8.
     */
    void testAlphaSizeWithRgba8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGBA8, 12, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        // Check its alpha size
        CPPUNIT_ASSERT_EQUAL(8, target.alphaSize());
    }

    /**
     * Ensures TextureTarget::alphaType() returns `GL_UNSIGNED_NORMALIZED` for `GL_RGBA8`.
     */
    void testAlphaType() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();

        // Specify a texture image for it
        target.texImage1d(0, GL_RGBA8, 12, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        // Check its alpha type
        const GLenum expected = GL_UNSIGNED_NORMALIZED;
        const GLenum actual = target.alphaType();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures TextureTarget::operator=(TextureTarget) works correctly.
     */
    void testAssignmentOperator() {
        TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::texture2d();
        TextureTarget* ptr = &(t1 = t2);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_2D, t1.toEnum());
        CPPUNIT_ASSERT_EQUAL(&t1, ptr);
    }

    /**
     * Ensures TextureTarget::baseLevel() works correctly.
     */
    void testBaseLevel() {

        // Set the base level manually
        const GLint expected = 2;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, expected);

        // Check the base level
        const TextureTarget target = TextureTarget::texture2d();
        const GLint actual =  target.baseLevel();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    }

    /**
     * Ensures TextureTarget::baseLevel(GLint) works correctly.
     */
    void testBaseLevelInt() {

        // Set the base level
        const GLint expected = 2;
        const TextureTarget target = TextureTarget::texture2d();
        target.baseLevel(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default value
        target.baseLevel(0);
    }

    /**
     * Ensures TextureTarget::binding() works correctly.
     */
    void testBinding() {

        // Generate and bind a new texture
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        // Check binding
        const TextureTarget target = TextureTarget::texture2d();
        const TextureObject texture = target.binding();
        CPPUNIT_ASSERT_EQUAL(id, texture.id());
    }

    /**
     * Ensures TextureTarget::bind(const TextureObject&) works correctly.
     */
    void testBindTextureObject() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Check that it was bound correctly
        GLint binding;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &binding);
        CPPUNIT_ASSERT_EQUAL(texture.id(), (GLuint) binding);
    }

    /**
     * Ensures TextureTarget::blueSize() return zero for GL_R8.
     */
    void testBlueSizeWithR8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_R8, 12, GL_RED, GL_UNSIGNED_BYTE, NULL);

        // Check its blue size
        CPPUNIT_ASSERT_EQUAL(0, target.blueSize());
    }

    /**
     * Ensures TextureTarget::blueSize() returns zero for GL_RG8.
     */
    void testBlueSizeWithRg8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RG8, 12, GL_RG, GL_UNSIGNED_BYTE, NULL);

        // Check its blue size
        CPPUNIT_ASSERT_EQUAL(0, target.blueSize());
    }

    /**
     * Ensures TextureTarget::blueSize() returns eight for GL_RGB8.
     */
    void testBlueSizeWithRgb8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGB8, 12, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // Check its blue size
        CPPUNIT_ASSERT_EQUAL(8, target.blueSize());
    }

    /**
     * Ensures TextureTarget::blueSize() returns eight for GL_RGBA8.
     */
    void testBlueSizeWithRgba8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGBA8, 12, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        // Check its blue size
        CPPUNIT_ASSERT_EQUAL(8, target.blueSize());
    }

    /**
     * Ensures TextureTarget::blueType() returns `GL_UNSIGNED_NORMALIZED` for `GL_RGB8`.
     */
    void testBlueType() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();

        // Specify a texture image for it
        target.texImage1d(0, GL_RGB8, 12, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // Check its blue type
        const GLenum expected = GL_UNSIGNED_NORMALIZED;
        const GLenum actual = target.blueType();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures TextureTarget::bound(const TextureObject&) works with a bound texture object.
     */
    void testBoundTextureObjectWithBound() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Check that it's bound
        CPPUNIT_ASSERT(target.bound(texture));
    }

    /**
     * Ensures TextureTarget::bound(const TextureObject&) works with an unbound texture object.
     */
    void testBoundTextureObjectWithUnbound() {

        // Generate a new texture
        const TextureObject texture = TextureObject::generate();

        // Check that it's not bound
        const TextureTarget target = TextureTarget::texture2d();
        CPPUNIT_ASSERT(!target.bound(texture));
    }

    /**
     * Ensures TextureTarget::compareFunc() works correctly.
     */
    void testCompareFunc() {

        // Set the parameter manually
        const GLenum expected = GL_ALWAYS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, expected);

        // Check the parameter
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.compareFunc();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    }

    /**
     * Ensures TextureTarget::compareFunc(GLenum) works correctly.
     */
    void testCompareFuncEnum() {

        // Set the value
        const GLenum expected = GL_ALWAYS;
        const TextureTarget target = TextureTarget::texture2d();
        target.compareFunc(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, (GLenum) actual);

        // Set it back to the default
        target.compareFunc(GL_LEQUAL);
    }

    /**
     * Ensures TextureTarget::compareMode() works correctly.
     */
    void testCompareMode() {

        // Set the parameter manually
        const GLenum expected = GL_COMPARE_REF_TO_TEXTURE;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, expected);

        // Check the parameter
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.compareMode();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    }

    /**
     * Ensures TextureTarget::compareMode(GLenum) works correctly.
     */
    void testCompareModeEnum() {

        // Set the value
        const GLenum expected = GL_COMPARE_REF_TO_TEXTURE;
        const TextureTarget target = TextureTarget::texture2d();
        target.compareMode(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, (GLenum) actual);

        // Set it back to the default
        target.compareMode(GL_NONE);
    }

    /**
     * Ensures TextureTarget::compressedImageSize(GLint) works with a compressed texture.
     */
    void testCompressedImageSizeWithCompressed() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify compressed texture image
        const GLubyte arr[] = { 255, 255, 0, 0 };
        target.texImage2d(0, GL_COMPRESSED_RED_RGTC1, 2, 2, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check compressed size
        const GLint actual = target.compressedImageSize();
        CPPUNIT_ASSERT(actual > 0);
    }

    /**
     * Ensures TextureTarget::compressed() works with a compressed texture.
     */
    void testCompressedWithCompressed() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify compressed texture image
        const GLubyte arr[] = { 255, 255, 0, 0 };
        target.texImage2d(0, GL_COMPRESSED_RED_RGTC1, 2, 2, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check that it's compressed
        CPPUNIT_ASSERT(target.compressed());
    }

    /**
     * Ensures TextureTarget::compressed() works with an uncompressed texture.
     */
    void testCompressedWithUncompressed() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify uncompressed texture image
        const GLubyte arr[] = { 0, 255, 0, 255, 0, 255, 0, 255 };
        target.texImage1d(0, GL_R8, 8, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check that it's not compressed
        CPPUNIT_ASSERT(!target.compressed());
    }

    /**
     * Ensures TextureTarget::depth() returns one for the depth of a one-dimensional texture image.
     */
    void testDepthWithOneDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = { 0, 0, 0, 0 };
        target.texImage1d(0, GL_R8, 4, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check depth
        CPPUNIT_ASSERT_EQUAL(1, target.depth());
    }

    /**
     * Ensures TextureTarget::depth() returns one for the depth of a two-dimensional texture image.
     */
    void testDepthWithTwoDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0 };
        target.texImage2d(0, GL_R8, 4, 3, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check depth
        CPPUNIT_ASSERT_EQUAL(1, target.depth());
    }

    /**
     * Ensures TextureTarget::depth() returns the correct number for a three-dimensional texture image.
     */
    void testDepthWithThreeDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture3d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255 };
        target.texImage3d(0, GL_R8, 4, 3, 2, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check depth
        CPPUNIT_ASSERT_EQUAL(2, target.depth());
    }

    /**
     * Ensures TextureTarget::operator==(TextureTarget) returns `true` for equal instances.
     */
    void testEqualityOperatorWithEqual() {
        const TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::fromEnum(GL_TEXTURE_1D);
        CPPUNIT_ASSERT(t1 == t2);
    }

    /**
     * Ensures TextureTarget::operator==(TextureTarget) returns `false` for unequal instances.
     */
    void testEqualityOperatorWithUnequal() {
        const TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::texture2d();
        CPPUNIT_ASSERT(!(t1 == t2));
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_1D.
     */
    void testFromEnumWithTexture1d() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_1D);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_1D, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_1D_ARRAY.
     */
    void testFromEnumWithTexture1dArray() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_1D_ARRAY);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_1D_ARRAY, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_2D.
     */
    void testFromEnumWithTexture2d() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_2D);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_2D, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_2D_ARRAY.
     */
    void testFromEnumWithTexture2dArray() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_2D_ARRAY);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_2D_ARRAY, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_3D.
     */
    void testFromEnumWithTexture3d() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_3D);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_3D, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_BUFFER.
     */
    void testFromEnumWithTextureBuffer() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_BUFFER);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_BUFFER, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_CUBE_MAP.
     */
    void testFromEnumWithTextureCubeMap() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_CUBE_MAP);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_CUBE_MAP, target.toEnum());
    }

    /**
     * Ensures TextureTarget::fromEnum(GLenum) returns the correct instance for GL_TEXTURE_RECTANGLE.
     */
    void testFromEnumWithTextureRectangle() {
        const TextureTarget target = TextureTarget::fromEnum(GL_TEXTURE_RECTANGLE);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_RECTANGLE, target.toEnum());
    }

    /**
     * Ensures TextureTarget::greenSize() return zero for GL_R8.
     */
    void testGreenSizeWithR8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_R8, 12, GL_RED, GL_UNSIGNED_BYTE, NULL);

        // Check its green size
        CPPUNIT_ASSERT_EQUAL(0, target.greenSize());
    }

    /**
     * Ensures TextureTarget::greenSize() returns eight for GL_RG8.
     */
    void testGreenSizeWithRg8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RG8, 12, GL_RG, GL_UNSIGNED_BYTE, NULL);

        // Check its green size
        CPPUNIT_ASSERT_EQUAL(8, target.greenSize());
    }

    /**
     * Ensures TextureTarget::greenSize() returns eight for GL_RGB8.
     */
    void testGreenSizeWithRgb8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGB8, 12, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // Check its green size
        CPPUNIT_ASSERT_EQUAL(8, target.greenSize());
    }

    /**
     * Ensures TextureTarget::greenSize() returns eight for GL_RGBA8.
     */
    void testGreenSizeWithRgba8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGBA8, 12, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        // Check its green size
        CPPUNIT_ASSERT_EQUAL(8, target.greenSize());
    }

    /**
     * Ensures TextureTarget::greenType() returns `GL_UNSIGNED_NORMALIZED` for `GL_RG8`.
     */
    void testGreenType() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();

        // Specify a texture image for it
        target.texImage1d(0, GL_RG8, 12, GL_RG, GL_UNSIGNED_BYTE, NULL);

        // Check its green type
        const GLenum expected = GL_UNSIGNED_NORMALIZED;
        const GLenum actual = target.greenType();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures TextureTarget::height() returns one for the height of a one-dimensional texture image.
     */
    void testHeightWithOneDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = { 0, 0, 0, 0 };
        target.texImage1d(0, GL_R8, 4, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check height
        CPPUNIT_ASSERT_EQUAL(1, target.height());
    }

    /**
     * Ensures TextureTarget::height() returns the correct number for the height of a two-dimensional texture image.
     */
    void testHeightWithTwoDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0 };
        target.texImage2d(0, GL_R8, 4, 3, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check height
        CPPUNIT_ASSERT_EQUAL(3, target.height());
    }

    /**
     * Ensures TextureTarget::height() returns the correct number for the height of a three-dimensional texture image.
     */
    void testHeightWithThreeDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture3d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255 };
        target.texImage3d(0, GL_R8, 4, 3, 2, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check height
        CPPUNIT_ASSERT_EQUAL(3, target.height());
    }

    /**
     * Ensures TextureTarget::operator!=(TextureTarget) returns `false` for equal instances.
     */
    void testInequalityOperatorWithEqual() {
        const TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::fromEnum(GL_TEXTURE_1D);
        CPPUNIT_ASSERT(!(t1 != t2));
    }

    /**
     * Ensures TextureTarget::operator!=(TextureTarget) returns `true` for unequal instances.
     */
    void testInequalityOperatorWithUnequal() {
        const TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::texture2d();
        CPPUNIT_ASSERT(t1 != t2);
    }

    /**
     * Ensures TextureTarget::internalFormat works with GL_R8.
     */
    void testInternalFormatWithR8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_R8, 12, GL_RED, GL_UNSIGNED_BYTE, NULL);

        // Check its internal format
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_R8, target.internalFormat());
    }

    /**
     * Ensures TextureTarget::internalFormat works with GL_RG8.
     */
    void testInternalFormatWithRg8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RG8, 12, GL_RG, GL_UNSIGNED_BYTE, NULL);

        // Check its internal format
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_RG8, target.internalFormat());
    }

    /**
     * Ensures TextureTarget::internalFormat works with GL_RGB8.
     */
    void testInternalFormatWithRgb8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGB8, 12, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // Check its internal format
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_RGB8, target.internalFormat());
    }

    /**
     * Ensures TextureTarget::internalFormat works with GL_RGBA8.
     */
    void testInternalFormatWithRgba8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGBA8, 12, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        // Check its internal format
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_RGBA8, target.internalFormat());
    }

    /**
     * Ensures TextureTarget::operator<(TextureTarget) returns `false` for equal instances.
     */
    void testLessThanOperatorWithEqual() {
        const TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::texture1d();
        CPPUNIT_ASSERT(!(t1 < t2));
        CPPUNIT_ASSERT(!(t2 < t1));
    }

    /**
     * Ensures TextureTarget::operator<(TextureTarget) returns `true` for an instance greater than it.
     */
    void testLessThanOperatorWithGreater() {
        const TextureTarget t1 = TextureTarget::texture1d();
        const TextureTarget t2 = TextureTarget::texture2d();
        CPPUNIT_ASSERT(t1 < t2);
    }

    /**
     * Ensures TextureTarget::operator<(TextureTarget) returns `false` for an instance less than it.
     */
    void testLessThanOperatorWithLess() {
        const TextureTarget t1 = TextureTarget::texture2d();
        const TextureTarget t2 = TextureTarget::texture1d();
        CPPUNIT_ASSERT(!(t1 < t2));
    }

    /**
     * Ensures TextureTarget::lodBias() works correctly.
     */
    void testLodBias() {

        // Set the value manually
        const GLfloat expected = 1.0f;
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLfloat actual = target.lodBias();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0f);
    }

    /**
     * Ensures TextureTarget::lodBias(GLfloat) works correctly.
     */
    void testLodBiasFloat() {

        // Set the value
        const GLfloat expected = 1.0f;
        const TextureTarget target = TextureTarget::texture2d();
        target.lodBias(expected);

        // Check the value manually
        GLfloat actual;
        glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        target.lodBias(0.0f);

    }

    /**
     * Ensures TextureTarget::magFilter() works correctly.
     */
    void testMagFilter() {

        // Set the value manually
        const GLenum expected = GL_NEAREST;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.magFilter();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    /**
     * Ensures TextureTarget::magFilter(GLenum) works correctly.
     */
    void testMagFilterEnum() {

        // Set the value
        const GLenum expected = GL_NEAREST;
        const TextureTarget target = TextureTarget::texture2d();
        target.magFilter(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, ((GLenum) actual));

        // Set it back to the default
        target.magFilter(GL_LINEAR);
    }

    /**
     * Ensures TextureTarget::maxLevel() works correctly.
     */
    void testMaxLevel() {

        // Set the value manually
        const GLint expected = 500;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLint actual = target.maxLevel();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
    }

    /**
     * Ensures TextureTarget::maxLevel(GLint) works correctly.
     */
    void testMaxLevelInt() {

        // Set the value
        const GLint expected = 500;
        const TextureTarget target = TextureTarget::texture2d();
        target.maxLevel(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        target.maxLevel(1000);
    }

    /**
     * Ensures TextureTarget::maxLod() works correctly.
     */
    void testMaxLod() {

        // Set the value manually
        const GLfloat expected = 500.0f;
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLfloat actual = target.maxLod();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 1000.0f);
    }

    /**
     * Ensures TextureTarget::maxLod(GLfloat) works correctly.
     */
    void testMaxLodFloat() {

        // Set the value
        const GLfloat expected = 500.0f;
        const TextureTarget target = TextureTarget::texture2d();
        target.maxLod(expected);

        // Check the value manually
        GLfloat actual;
        glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        target.maxLod(1000.0f);
    }

    /**
     * Ensures TextureTarget::minFilter() works correctly.
     */
    void testMinFilter() {

        // Set the value manually
        const GLenum expected = GL_NEAREST;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.minFilter();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    }

    /**
     * Ensures TextureTarget::minFilter(GLenum) works correctly.
     */
    void testMinFilterEnum() {

        // Set the value
        const GLenum expected = GL_NEAREST;
        const TextureTarget target = TextureTarget::texture2d();
        target.minFilter(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, ((GLenum) actual));

        // Set it back to the default
        target.minFilter(GL_NEAREST_MIPMAP_LINEAR);
    }

    /**
     * Ensures TextureTarget::minLod() works correctly.
     */
    void testMinLod() {

        // Set the value manually
        const GLfloat expected = -500.0f;
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLfloat actual = target.minLod();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, -1000.0f);
    }

    /**
     * Ensures TextureTarget::minLod(GLfloat) works correctly.
     */
    void testMinLodFloat() {

        // Set the value
        const GLfloat expected = -500.0f;
        const TextureTarget target = TextureTarget::texture2d();
        target.minLod(expected);

        // Check the value manually
        GLfloat actual;
        glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        target.minLod(expected);
    }

    /**
     * Ensures TextureTarget::redSize() return eight for GL_R8.
     */
    void testRedSizeWithR8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_R8, 12, GL_RED, GL_UNSIGNED_BYTE, NULL);

        // Check its red size
        CPPUNIT_ASSERT_EQUAL(8, target.redSize());
    }

    /**
     * Ensures TextureTarget::redSize() returns eight for GL_RG8.
     */
    void testRedSizeWithRg8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RG8, 12, GL_RG, GL_UNSIGNED_BYTE, NULL);

        // Check its red size
        CPPUNIT_ASSERT_EQUAL(8, target.redSize());
    }

    /**
     * Ensures TextureTarget::redSize() returns eight for GL_RGB8.
     */
    void testRedSizeWithRgb8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGB8, 12, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // Check its red size
        CPPUNIT_ASSERT_EQUAL(8, target.redSize());
    }

    /**
     * Ensures TextureTarget::redSize() returns eight for GL_RGBA8.
     */
    void testRedSizeWithRgba8() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image for it
        target.texImage1d(0, GL_RGBA8, 12, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        // Check its red size
        CPPUNIT_ASSERT_EQUAL(8, target.redSize());
    }

    /**
     * Ensures TextureTarget::redType() returns `GL_UNSIGNED_NORMALIZED` for `GL_R8`.
     */
    void testRedType() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();

        // Specify a texture image for it
        target.texImage1d(0, GL_R8, 12, GL_RED, GL_UNSIGNED_BYTE, NULL);

        // Check its red type
        const GLenum expected = GL_UNSIGNED_NORMALIZED;
        const GLenum actual = target.redType();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures TextureTarget::texImage1d works correctly.
     */
    void testTexImage1d() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify a texture image
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const GLubyte expectedData[] = { 0, 1, 2, 3 };
        target.texImage1d(0, GL_R8, 4, GL_RED, GL_UNSIGNED_BYTE, expectedData);

        // Check internal format
        GLint internalFormat;
        glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
        CPPUNIT_ASSERT_EQUAL(GL_R8, internalFormat);

        // Check width
        GLint width;
        glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
        CPPUNIT_ASSERT_EQUAL(4, width);

        // Check data
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        GLubyte actualData[4];
        glGetTexImage(GL_TEXTURE_1D, 0, GL_RED, GL_UNSIGNED_BYTE, actualData);
        for (int i = 0; i < 4; ++i) {
            CPPUNIT_ASSERT_EQUAL(expectedData[i], actualData[i]);
        }
    }

    /**
     * Ensures TextureTarget::texImage2d works correctly.
     */
    void testTexImage2d() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify a texture image
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const GLubyte expectedData[] = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 12, 14, 15,
            16, 17, 18, 19,
            20, 21, 22, 23 };
        target.texImage2d(0, GL_R8, 4, 3, GL_RED, GL_UNSIGNED_BYTE, expectedData);

        // Check internal format
        GLint internalFormat;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
        CPPUNIT_ASSERT_EQUAL(GL_R8, internalFormat);

        // Check width
        GLint width;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        CPPUNIT_ASSERT_EQUAL(4, width);

        // Check height
        GLint height;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        CPPUNIT_ASSERT_EQUAL(3, height);

        // Check data
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        GLubyte actualData[128];
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, actualData);
        for (int i = 0; i < 12; ++i) {
            CPPUNIT_ASSERT_EQUAL(expectedData[i], actualData[i]);
        }
    }

    /**
     * Ensures TextureTarget::texImage3d works correctly.
     */
    void testTexImage3d() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture3d();
        target.bind(texture);

        // Specify a texture image
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const GLubyte expectedData[24] = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15,
            16, 17, 18, 19,
            20, 21, 22, 23
        };
        target.texImage3d(0, GL_R8, 4, 3, 2, GL_RED, GL_UNSIGNED_BYTE, expectedData);

        // Check internal format
        GLint internalFormat;
        glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
        CPPUNIT_ASSERT_EQUAL(GL_R8, internalFormat);

        // Check width
        GLint width;
        glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_WIDTH, &width);
        CPPUNIT_ASSERT_EQUAL(4, width);

        // Check height
        GLint height;
        glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_HEIGHT, &height);
        CPPUNIT_ASSERT_EQUAL(3, height);

        // Check depth
        GLint depth;
        glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_DEPTH, &depth);
        CPPUNIT_ASSERT_EQUAL(2, depth);

        // Check data
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        GLubyte actualData[24];
        glGetTexImage(GL_TEXTURE_3D, 0, GL_RED, GL_UNSIGNED_BYTE, actualData);
        for (int i = 0; i < 24; ++i) {
            CPPUNIT_ASSERT_EQUAL(expectedData[i], actualData[i]);
        }
    }

    /**
     * Ensures TextureTarget::texSubImage1d works correctly.
     */
    void testTexSubImage1d() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify byte-aligned ata
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);

        // Specify an initial image
        const GLubyte image[] = { 0, 1, 2, 3 };
        target.texImage1d(0, GL_R8, 4, GL_RED, GL_UNSIGNED_BYTE, image);

        // Replace part of it
        const GLubyte subImage[] = { 10, 20 };
        target.texSubImage1d(0, 1, 2, GL_RED, GL_UNSIGNED_BYTE, subImage);

        // Check the data
        const GLubyte expectedData[] = { 0, 10, 20, 3 };
        GLubyte actualData[4];
        glGetTexImage(GL_TEXTURE_1D, 0, GL_RED, GL_UNSIGNED_BYTE, actualData);
        for (int i = 0; i < 4; ++i) {
            CPPUNIT_ASSERT_EQUAL((int) expectedData[i], (int) actualData[i]);
        }
    }

    /**
     * Ensures TextureTarget::texSubImage2d works correctly.
     */
    void testTexSubImage2d() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify byte-aligned data
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);

        // Specify an initial image
        const GLubyte image[] = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11 };
        target.texImage2d(0, GL_R8, 4, 3, GL_RED, GL_UNSIGNED_BYTE, image);

        // Replace part of it
        const GLubyte subImage[] = {
            10, 20,
            50, 60,
            90, 100 };
        target.texSubImage2d(0, 1, 0, 2, 3, GL_RED, GL_UNSIGNED_BYTE, subImage);

        // Check the data
        const GLubyte expectedData[] = {
            0, 10, 20, 3,
            4, 50, 60, 7,
            8, 90, 100, 11 };
        GLubyte actualData[12];
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, actualData);
        for (int i = 0; i < 12; ++i) {
            CPPUNIT_ASSERT_EQUAL((int) expectedData[i], (int) actualData[i]);
        }
    }

    /**
     * Ensures TextureTarget::texSubImage3d works correctly.
     */
    void testTexSubImage3d() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture3d();
        target.bind(texture);

        // Specify byte-aligned data
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);

        // Specify an initial image
        const GLubyte image[] = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,

            12, 13, 14, 15,
            16, 17, 18, 19,
            20, 21, 22, 23 };
        target.texImage3d(0, GL_R8, 4, 3, 2, GL_RED, GL_UNSIGNED_BYTE, image);

        // Replace part of it
        const GLubyte subImage[] = {
            10, 20,
            50, 60,
            90, 100,

            130, 140,
            170, 180,
            210, 220 };
        target.texSubImage3d(0, 1, 0, 0, 2, 3, 2, GL_RED, GL_UNSIGNED_BYTE, subImage);

        // Check the data
        const GLubyte expectedData[] = {
            0, 10, 20, 3,
            4, 50, 60, 7,
            8, 90, 100, 11,

            12, 130, 140, 15,
            16, 170, 180, 19,
            20, 210, 220, 23 };
        GLubyte actualData[24];
        glGetTexImage(GL_TEXTURE_3D, 0, GL_RED, GL_UNSIGNED_BYTE, actualData);
        for (int i = 0; i < 24; ++i) {
            CPPUNIT_ASSERT_EQUAL((int) expectedData[i], (int) actualData[i]);
        }
    }

    /**
     * Ensures TextureTarget::texture1d() returns the texture target for GL_TEXTURE_1D.
     */
    void testTexture1d() {
        const TextureTarget target = TextureTarget::texture1d();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_1D, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_1D"), stream.str());
    }

    /**
     * Ensures TextureTarget::texture1dArray() returns the texture target for GL_TEXTURE_1D_ARRAY.
     */
    void testTexture1dArray() {
        const TextureTarget target = TextureTarget::texture1dArray();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_1D_ARRAY, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_1D_ARRAY"), stream.str());
    }

    /**
     * Ensures TextureTarget::texture2d() returns the texture target for GL_TEXTURE_2D.
     */
    void testTexture2d() {
        const TextureTarget target = TextureTarget::texture2d();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_2D, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_2D"), stream.str());
    }

    /**
     * Ensures TextureTarget::texture2dArray() returns the texture target for GL_TEXTURE_2D_ARRAY.
     */
    void testTexture2dArray() {
        const TextureTarget target = TextureTarget::texture2dArray();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_2D_ARRAY, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_2D_ARRAY"), stream.str());
    }

    /**
     * Ensures TextureTarget::texture3d() returns the texture target for GL_TEXTURE_3D.
     */
    void testTexture3d() {
        const TextureTarget target = TextureTarget::texture3d();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_3D, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_3D"), stream.str());
    }

    /**
     * Ensures TextureTarget::textureBuffer() returns the texture target for GL_TEXTURE_BUFFER.
     */
    void testTextureBuffer() {
        const TextureTarget target = TextureTarget::textureBuffer();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_BUFFER, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_BUFFER"), stream.str());
    }

    /**
     * Ensures TextureTarget::textureCubeMap() returns the texture target for GL_TEXTURE_CUBE_MAP.
     */
    void testTextureCubeMap() {
        const TextureTarget target = TextureTarget::textureCubeMap();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_CUBE_MAP, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_CUBE_MAP"), stream.str());
    }

    /**
     * Ensures TextureTarget::textureRectangle() returns the texture target for GL_TEXTURE_RECTANGLE.
     */
    void testTextureRectangle() {
        const TextureTarget target = TextureTarget::textureRectangle();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_TEXTURE_RECTANGLE, target.toEnum());
        stringstream stream;
        stream << target;
        CPPUNIT_ASSERT_EQUAL(string("GL_TEXTURE_RECTANGLE"), stream.str());
    }

    /**
     * Ensures TextureTarget::width() returns the correct number for the width of a one-dimensional texture image.
     */
    void testWidthWithOneDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture1d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = { 0, 0, 0, 0 };
        target.texImage1d(0, GL_R8, 4, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check width
        CPPUNIT_ASSERT_EQUAL(4, target.width());
    }

    /**
     * Ensures TextureTarget::width() returns the correct number for the width of a two-dimensional texture image.
     */
    void testWidthWithTwoDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture2d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0 };
        target.texImage2d(0, GL_R8, 4, 3, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check width
        CPPUNIT_ASSERT_EQUAL(4, target.width());
    }

    /**
     * Ensures TextureTarget::width() returns the correct number for the width of a three-dimensional texture image.
     */
    void testWidthWithThreeDimensionalTextureImage() {

        // Generate and bind a new texture
        const TextureObject texture = TextureObject::generate();
        const TextureTarget target = TextureTarget::texture3d();
        target.bind(texture);

        // Specify texture
        const GLubyte arr[] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255 };
        target.texImage3d(0, GL_R8, 4, 3, 2, GL_RED, GL_UNSIGNED_BYTE, arr);

        // Check width
        CPPUNIT_ASSERT_EQUAL(4, target.width());
    }

    /**
     * Ensures TextureTarget::wrapR() works correctly.
     */
    void testWrapR() {

        // Set the value manually
        const GLenum expected = GL_CLAMP_TO_EDGE;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.wrapR();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    }

    /**
     * Ensures TextureTarget::wrapR(GLenum) works correctly.
     */
    void testWrapREnum() {

        // Set the value
        const GLenum expected = GL_CLAMP_TO_EDGE;
        const TextureTarget target = TextureTarget::texture2d();
        target.wrapR(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, ((GLenum) actual));

        // Set it back to the default
        target.wrapR(GL_REPEAT);
    }

    /**
     * Ensures TextureTarget::wrapS() works correctly.
     */
    void testWrapS() {

        // Set the value manually
        const GLenum expected = GL_CLAMP_TO_EDGE;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.wrapS();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }

    /**
     * Ensures TextureTarget::wrapS(GLenum) works correctly.
     */
    void testWrapSEnum() {

        // Set the value
        const GLenum expected = GL_CLAMP_TO_EDGE;
        const TextureTarget target = TextureTarget::texture2d();
        target.wrapS(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, ((GLenum) actual));

        // Set it back to the default
        target.wrapS(GL_REPEAT);
    }

    /**
     * Ensures TextureTarget::wrapT() works correctly.
     */
    void testWrapT() {

        // Set the value manually
        const GLenum expected = GL_CLAMP_TO_EDGE;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, expected);

        // Check the value
        const TextureTarget target = TextureTarget::texture2d();
        const GLenum actual = target.wrapT();
        CPPUNIT_ASSERT_EQUAL(expected, actual);

        // Set it back to the default
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    /**
     * Ensures TextureTarget::wrapT(GLenum) works correctly.
     */
    void testWrapTEnum() {

        // Set the value
        const GLenum expected = GL_CLAMP_TO_EDGE;
        const TextureTarget target = TextureTarget::texture2d();
        target.wrapT(expected);

        // Check the value manually
        GLint actual;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &actual);
        CPPUNIT_ASSERT_EQUAL(expected, ((GLenum) actual));

        // Set it back to the default
        target.wrapT(GL_REPEAT);
    }
};


int main(int argc, char* argv[]) {

    // Initialize
    if (!glfwInit()) {
        cerr << "Could not initialize GLFW!" << endl;
        return 1;
    }

    // Open a window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    // Run the test
    TextureTargetTest test;
    try {
        test.testAlphaSizeWithR8();
        test.testAlphaSizeWithRg8();
        test.testAlphaSizeWithRgb8();
        test.testAlphaSizeWithRgba8();
        test.testAlphaType();
        test.testAddToStlMap();
        test.testAddToStlSet();
        test.testAddToStlVector();
        test.testAssignmentOperator();
        test.testBaseLevel();
        test.testBaseLevelInt();
        test.testBinding();
        test.testBindTextureObject();
        test.testBlueSizeWithR8();
        test.testBlueSizeWithRg8();
        test.testBlueSizeWithRgb8();
        test.testBlueSizeWithRgba8();
        test.testBlueType();
        test.testBoundTextureObjectWithBound();
        test.testBoundTextureObjectWithUnbound();
        test.testCompareFunc();
        test.testCompareFuncEnum();
        test.testCompareMode();
        test.testCompareModeEnum();
        test.testCompressedImageSizeWithCompressed();
        test.testCompressedWithCompressed();
        test.testCompressedWithUncompressed();
        test.testDepthWithOneDimensionalTextureImage();
        test.testDepthWithTwoDimensionalTextureImage();
        test.testDepthWithThreeDimensionalTextureImage();
        test.testEqualityOperatorWithEqual();
        test.testEqualityOperatorWithUnequal();
        test.testFromEnumWithTexture1d();
        test.testFromEnumWithTexture1dArray();
        test.testFromEnumWithTexture2d();
        test.testFromEnumWithTexture2dArray();
        test.testFromEnumWithTexture3d();
        test.testFromEnumWithTextureBuffer();
        test.testFromEnumWithTextureCubeMap();
        test.testFromEnumWithTextureRectangle();
        test.testGreenSizeWithR8();
        test.testGreenSizeWithRg8();
        test.testGreenSizeWithRgb8();
        test.testGreenSizeWithRgba8();
        test.testGreenType();
        test.testHeightWithOneDimensionalTextureImage();
        test.testHeightWithTwoDimensionalTextureImage();
        test.testHeightWithThreeDimensionalTextureImage();
        test.testInequalityOperatorWithEqual();
        test.testInequalityOperatorWithUnequal();
        test.testInternalFormatWithR8();
        test.testInternalFormatWithRg8();
        test.testInternalFormatWithRgb8();
        test.testInternalFormatWithRgba8();
        test.testLessThanOperatorWithEqual();
        test.testLessThanOperatorWithGreater();
        test.testLessThanOperatorWithLess();
        test.testLodBias();
        test.testLodBiasFloat();
        test.testMagFilter();
        test.testMagFilterEnum();
        test.testMaxLevel();
        test.testMaxLevelInt();
        test.testMaxLod();
        test.testMaxLodFloat();
        test.testMinFilter();
        test.testMinFilterEnum();
        test.testMinLod();
        test.testMinLodFloat();
        test.testRedSizeWithR8();
        test.testRedSizeWithRg8();
        test.testRedSizeWithRgb8();
        test.testRedSizeWithRgba8();
        test.testRedType();
        test.testTexImage1d();
        test.testTexImage2d();
        test.testTexImage3d();
        test.testTexSubImage1d();
        test.testTexSubImage2d();
        test.testTexSubImage3d();
        test.testTexture1d();
        test.testTexture1dArray();
        test.testTexture2d();
        test.testTexture2dArray();
        test.testTexture3d();
        test.testTextureBuffer();
        test.testTextureCubeMap();
        test.testTextureRectangle();
        test.testWidthWithOneDimensionalTextureImage();
        test.testWidthWithTwoDimensionalTextureImage();
        test.testWidthWithThreeDimensionalTextureImage();
        test.testWrapR();
        test.testWrapREnum();
        test.testWrapS();
        test.testWrapSEnum();
        test.testWrapT();
        test.testWrapTEnum();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

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
#include <cppunit/extensions/HelperMacros.h>
#include <stdexcept>
#include "gloop/Shader.hxx"
#include <GL/glfw.h>
using namespace std;
using namespace Gloop;


/**
 * Unit test for Shader.
 */
class ShaderTest {
public:

    /**
     * Ensures a bad fragment shader does not compile correctly.
     */
    void testCompileWithBadFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "FragColor = vec4(1);\n");
        shader.compile();
        CPPUNIT_ASSERT(!shader.compiled());
    }

    /**
     * Ensures a good fragment shader compiles correctly.
     */
    void testCompileWithGoodFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        shader.compile();
        CPPUNIT_ASSERT(shader.compiled());
    }

    /**
     * Ensures a bad vertex shader does not compile correctly.
     */
    void testCompileWithBadVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "gl_Position = MCVertex;\n");
        shader.compile();
        CPPUNIT_ASSERT(!shader.compiled());
    }

    /**
     * Ensures a good vertex shader compiles correctly.
     */
    void testCompileWithGoodVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");
        shader.compile();
        CPPUNIT_ASSERT(shader.compiled());
    }

    /**
     * Ensures making a new fragment shader works.
     */
    void testCreateWithFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        const GLenum error = glGetError();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NO_ERROR, error);
        shader.dispose();
    }

    /**
     * Ensures making a new geometry shader works.
     */
    void testCreateWithGeometryShader() {
        const Shader shader = Shader::create(GL_GEOMETRY_SHADER);
        const GLenum error = glGetError();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NO_ERROR, error);
        shader.dispose();
    }

    /**
     * Ensures making a new vertex shader works.
     */
    void testCreateWithVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        const GLenum error = glGetError();
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_NO_ERROR, error);
        shader.dispose();
    }

    /**
     * Ensures id returns a valid ID with a fragment shader.
     */
    void testIdWithFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        CPPUNIT_ASSERT(shader.id() > 0);
    }

    /**
     * Ensures id returns a valid ID with a geometry shader.
     */
    void testIdWithGeometryShader() {
        const Shader shader = Shader::create(GL_GEOMETRY_SHADER);
        CPPUNIT_ASSERT(shader.id() > 0);
    }

    /**
     * Ensures id returns a valid ID with a vertex shader.
     */
    void testIdWithVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        CPPUNIT_ASSERT(shader.id() > 0);
    }

    /**
     * Ensures compiling a bad fragment shader generates a log.
     */
    void testLogWithBadFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1)\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        CPPUNIT_ASSERT(!log.empty());
    }

    /**
     * Ensures compiling a good fragment shader generates an empty log.
     */
    void testLogWithGoodFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        CPPUNIT_ASSERT(log.empty());
    }

    /**
     * Ensures compiling a bad vertex shader generates a log.
     */
    void testLogWithBadVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    FragColor = MCVertex;\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        CPPUNIT_ASSERT(!log.empty());
    }

    /**
     * Ensures compiling a good vertex shader generates an empty log.
     */
    void testLogWithGoodVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        CPPUNIT_ASSERT(log.empty());
    }

    /**
     * Ensures equality operator returns true for shaders with the same ID.
     */
    void testOperatorEqualEqualWithEqual() {
        const Shader s1 = Shader::create(GL_VERTEX_SHADER);
        const Shader s2 = Shader::fromId(s1.id());
        CPPUNIT_ASSERT(s1 == s2);
    }

    /**
     * Ensures inequality operator returns true for shaders with different IDs.
     */
    void testOperatorNotEqualWithUnequal() {
        const Shader s1 = Shader::create(GL_VERTEX_SHADER);
        const Shader s2 = Shader::create(GL_VERTEX_SHADER);
        CPPUNIT_ASSERT(s1 != s2);
    }

    /**
     * Ensures both forms of source works correctly.
     */
    void testSource() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        string source =
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n";
        shader.source(source);
        CPPUNIT_ASSERT_EQUAL(source, shader.source());
    }

    /**
     * Ensures a fragment shader's type is GL_FRAGMENT_SHADER.
     */
    void testTypeWithFragmentShader() {
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FRAGMENT_SHADER, shader.type());
    }

    /**
     * Ensures a geometry shader's type is GL_GEOMETRY_SHADER.
     */
    void testTypeWithGeometryShader() {
        const Shader shader = Shader::create(GL_GEOMETRY_SHADER);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_GEOMETRY_SHADER, shader.type());
    }

    /**
     * Ensures a vertex shader's type is GL_VERTEX_SHADER.
     */
    void testTypeWithVertexShader() {
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_VERTEX_SHADER, shader.type());
    }

    /**
     * Ensures wrapping an existing shader works correctly.
     */
    void testFromIdWithGoodId() {
        const GLuint id = glCreateShader(GL_FRAGMENT_SHADER);
        const Shader shader = Shader::fromId(id);
        CPPUNIT_ASSERT_EQUAL(id, shader.id());
    }

    /**
     * Ensures wrapping a non-existent shader throws an exception.
     */
    void testFromIdWithBadId() {
        const GLuint id = -1;
        CPPUNIT_ASSERT_THROW(Shader::fromId(id), invalid_argument);
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
    ShaderTest test;
    try {
        test.testCompileWithBadFragmentShader();
        test.testCompileWithGoodFragmentShader();
        test.testCompileWithBadVertexShader();
        test.testCompileWithGoodVertexShader();
        test.testCreateWithFragmentShader();
        test.testCreateWithGeometryShader();
        test.testCreateWithVertexShader();
        test.testIdWithFragmentShader();
        test.testIdWithGeometryShader();
        test.testIdWithVertexShader();
        test.testLogWithBadFragmentShader();
        test.testLogWithGoodFragmentShader();
        test.testLogWithBadVertexShader();
        test.testLogWithGoodVertexShader();
        test.testOperatorEqualEqualWithEqual();
        test.testOperatorNotEqualWithUnequal();
        test.testSource();
        test.testTypeWithFragmentShader();
        test.testTypeWithGeometryShader();
        test.testTypeWithVertexShader();
        test.testFromIdWithGoodId();
        test.testFromIdWithBadId();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

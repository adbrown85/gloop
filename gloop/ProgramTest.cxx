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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "gloop/common.h"
#include "gloop/Program.hxx"
#include "gloop/VertexArrayObject.hxx"
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
using namespace std;
using namespace Gloop;


const char* BAD_VERTEX_SHADER =
        "#version 140\n"
        "in vec4 MCVertex;\n"
        "void main() {\n"
        "    gl_position = MCVertex;\n"
        "}\n";

const char* BAD_FRAGMENT_SHADER =
        "#version 140\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(1);\n"
        "}\n";

const char* GOOD_VERTEX_SHADER =
        "#version 140\n"
        "uniform mat4 MVPMatrix = mat4(1);\n"
        "in vec4 MCVertex;\n"
        "void main() {\n"
        "    gl_Position = MVPMatrix * MCVertex;\n"
        "}\n";

const char* GOOD_FRAGMENT_SHADER =
        "#version 140\n"
        "uniform vec4 Color = vec4(1);\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = Color;\n"
        "}\n";

/**
 * Unit test for Program.
 */
class ProgramTest {
public:

    /**
     * Ensures the active attributes are returned correctly.
     */
    void testActiveAttributes() {

        const Program p = Program::create();

        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        p.attachShader(vs);
        p.attachShader(fs);

        p.link();
        CPPUNIT_ASSERT(p.linked());

        const map<string,Attribute> attribs = p.activeAttributes();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, attribs.size());
        const Attribute a = attribs.find("MCVertex")->second;
        CPPUNIT_ASSERT_EQUAL(string("MCVertex"), a.name());
        CPPUNIT_ASSERT_EQUAL(1, a.size());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT_VEC4, a.type());
        CPPUNIT_ASSERT(a.location() >= 0);
        CPPUNIT_ASSERT_EQUAL(p.id(), a.program());
    }

    /**
     * Ensures the active uniforms are returned correctly.
     */
    void testActiveUniforms() {

        // Make the program
        const Program p = Program::create();

        // Make the shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach the shaders
        p.attachShader(vs);
        p.attachShader(fs);

        // Link
        p.link();
        CPPUNIT_ASSERT(p.linked());

        // Get uniforms
        const map<string,Uniform> uniforms = p.activeUniforms();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, uniforms.size());
        const Uniform u1 = uniforms.find("MVPMatrix")->second;
        CPPUNIT_ASSERT_EQUAL(string("MVPMatrix"), u1.name());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT_MAT4, u1.type());
        CPPUNIT_ASSERT_EQUAL((GLint) 1, u1.size());
        CPPUNIT_ASSERT(u1.location() >= 0);
        CPPUNIT_ASSERT_EQUAL(p.id(), u1.program());
        const Uniform u2 = uniforms.find("Color")->second;
        CPPUNIT_ASSERT_EQUAL(string("Color"), u2.name());
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_FLOAT_VEC4, u2.type());
        CPPUNIT_ASSERT_EQUAL((GLint) 1, u2.size());
        CPPUNIT_ASSERT(u2.location() >= 0);
        CPPUNIT_ASSERT_EQUAL(p.id(), u2.program());
    }

    /**
     * Ensures attaching a bad shader throws an exception.
     */
    void testAttachShaderWithBadShader() {
        const Program program = Program::create();
        const GLuint shader = -1;
        CPPUNIT_ASSERT_THROW(program.attachShader(shader), invalid_argument);
    }

    /**
     * Ensures a good shader that hasn't been attached yet can be attached.
     */
    void testAttachShaderWithGoodUnattachedShader() {

        // Attach a shader
        const Program program = Program::create();
        const Shader shader = Shader::create(GL_VERTEX_SHADER);
        program.attachShader(shader);

        // Check if it was attached
        GLint num;
        glGetProgramiv(program.id(), GL_ATTACHED_SHADERS, &num);
        CPPUNIT_ASSERT_EQUAL((GLint) 1, num);
    }

    /**
     * Ensures a good shader that has already been attached can't be attached.
     */
    void testAttachShaderWithGoodAttachedShader() {

        // Attach a shader
        const Program program = Program::create();
        const Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        program.attachShader(shader);

        // Try to attach shader
        CPPUNIT_ASSERT_THROW(program.attachShader(shader), logic_error);
    }

    /**
     * Ensures the location of a bad attribute is negative.
     */
    void testAttribLocationWithBadName() {

        // Create program
        const Program program = Program::create();

        // Create shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach shaders
        program.attachShader(vs);
        program.attachShader(fs);

        // Link
        program.link();
        CPPUNIT_ASSERT(program.linked());

        // Check attrib location
        const GLint loc = program.attribLocation("mcVertex");
        CPPUNIT_ASSERT(loc < 0);
    }

    /**
     * Ensures the location of a good attribute is non-negative.
     */
    void testAttribLocationWithGoodName() {

        // Create program
        const Program program = Program::create();

        // Create shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach shaders
        program.attachShader(vs);
        program.attachShader(fs);

        // Link
        program.link();
        CPPUNIT_ASSERT(program.linked());

        // Check attrib location
        const GLint loc = program.attribLocation("MCVertex");
        CPPUNIT_ASSERT(loc >= 0);
    }

    /**
     * Ensures create returns a program with a valid ID.
     */
    void testCreate() {
        const Program program = Program::create();
        CPPUNIT_ASSERT(program.id() > 0);
    }

    /**
     * Ensures `Program::current` throws when there is a current program.
     */
    void testCurrentWhenCurrentProgram() {

        // Create a program
        const Program program = Program::create();

        // Create shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach shaders
        program.attachShader(vs);
        program.attachShader(fs);

        // Link
        program.link();

        // Use the program
        program.use();
        CPPUNIT_ASSERT_EQUAL(program.id(), Program::current().id());
        glUseProgram(0);
    }

    /**
     * Ensures `Program::current` throws when there is no current program.
     */
    void testCurrentWhenNoCurrentProgram() {
        glUseProgram(0);
        CPPUNIT_ASSERT_THROW(Program::current(), std::runtime_error);
    }

    /**
     * Ensures detaching an attached shader works correctly.
     */
    void testDetachShaderWithAttachedShader() {

        const Program program = Program::create();
        const Shader shader = Shader::create(GL_VERTEX_SHADER);

        GLint attached;
        program.attachShader(shader);
        glGetProgramiv(program.id(), GL_ATTACHED_SHADERS, &attached);
        CPPUNIT_ASSERT_EQUAL((GLint) 1, attached);
        program.detachShader(shader);
        glGetProgramiv(program.id(), GL_ATTACHED_SHADERS, &attached);
        CPPUNIT_ASSERT_EQUAL((GLint) 0, attached);
    }

    /**
     * Ensures trying to detach an unattached shader throws an exception.
     */
    void testDetachShaderWithUnattachedShader() {

        const Program program = Program::create();
        const Shader shader = Shader::create(GL_VERTEX_SHADER);

        try {
            program.detachShader(shader);
        } catch (logic_error &e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught!");
    }

    /**
     * Ensures the location of a bad fragment output is negative.
     */
    void testFragDataLocationWithBadName() {

        // Make program
        const Program program = Program::create();

        // Make shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach shaders
        program.attachShader(vs);
        program.attachShader(fs);

        // Link
        program.link();
        CPPUNIT_ASSERT(program.linked());

        // Check location
        GLint location = program.fragDataLocation("fragColor");
        CPPUNIT_ASSERT(location < 0);
    }

    /**
     * Ensures the location of a good fragment output is non-negative.
     */
    void testFragDataLocationWithGoodName() {

        // Make program
        const Program program = Program::create();

        // Make shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach shaders
        program.attachShader(vs);
        program.attachShader(fs);

        // Link
        program.link();
        CPPUNIT_ASSERT(program.linked());

        // Check location
        GLint location = program.fragDataLocation("FragColor");
        CPPUNIT_ASSERT(location >= 0);
    }

    /**
     * Ensures Program links with a vertex and fragment shader.
     */
    void testLinkWithGoodVertexAndFragmentShader() {

        // Create a program
        const Program program = Program::create();
        CPPUNIT_ASSERT(program.id() > 0);

        // Create shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Add the shaders to the program
        program.attachShader(vs);
        program.attachShader(fs);

        // Delete the shaders
        vs.dispose();
        fs.dispose();

        // Link the program
        program.link();
        if (!program.linked()) {
            cerr << program.log() << endl;
            CPPUNIT_FAIL("Could not link program!");
        }

        // Validate it
        const VertexArrayObject vao = VertexArrayObject::generate();
        vao.bind();
        program.validate();
        if (!program.valid()) {
            cerr << program.log() << endl;
            CPPUNIT_FAIL("Could not validate program!");
        }

        // Delete it
        program.dispose();
    }

    /**
     * Ensures Program does not link and validate with a bad vertex and fragment shader.
     */
    void testLinkWithBadVertexAndFragmentShader() {

        // Create a program
        const Program program = Program::create();
        CPPUNIT_ASSERT(program.id() > 0);

        // Create shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(BAD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(BAD_FRAGMENT_SHADER);
        fs.compile();

        // Add the shaders to the program
        program.attachShader(vs);
        program.attachShader(fs);

        // Delete the shaders
        vs.dispose();
        fs.dispose();

        // Link the program
        program.link();
        CPPUNIT_ASSERT(!program.linked());

        // Delete it
        program.dispose();
    }

    /**
     * Ensures the location of a bad uniform is negative.
     */
    void testUniformLocationWithBadName() {

        // Make the program
        const Program p = Program::create();

        // Make the shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach the shaders
        p.attachShader(vs);
        p.attachShader(fs);

        // Link
        p.link();
        CPPUNIT_ASSERT(p.linked());

        // Check uniform location
        GLint loc = p.uniformLocation("mvpMatrix");
        CPPUNIT_ASSERT(loc < 0);
    }

    /**
     * Ensures the location of a good uniform is non-negative.
     */
    void testUniformLocationWithGoodName() {

        // Make the program
        const Program p = Program::create();

        // Make the shaders
        const Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        const Shader fs = Shader::create(GL_FRAGMENT_SHADER);
        fs.source(GOOD_FRAGMENT_SHADER);
        fs.compile();

        // Attach the shaders
        p.attachShader(vs);
        p.attachShader(fs);

        // Link
        p.link();
        CPPUNIT_ASSERT(p.linked());

        // Check uniform location
        GLint loc = p.uniformLocation("MVPMatrix");
        CPPUNIT_ASSERT(loc >= 0);
    }

    /**
     * Ensures fromId does not throw an exception with a good ID.
     */
    void testFromIdWithGoodId() {
        const GLuint id = glCreateProgram();
        CPPUNIT_ASSERT(id > 0);
        const Program program = Program::fromId(id);
    }

    /**
     * Ensures fromId throws an exception with a bad ID.
     */
    void testFromIdWithBadId() {
        const GLuint id = -1;
        CPPUNIT_ASSERT_THROW(Program::fromId(id), invalid_argument);
    }
};

int main(int argc, char *argv[]) {

    // Initialize GLFW
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
    ProgramTest test;
    try {
        test.testCreate();
        test.testAttachShaderWithBadShader();
        test.testAttachShaderWithGoodUnattachedShader();
        test.testAttachShaderWithGoodAttachedShader();
        test.testCurrentWhenCurrentProgram();
        test.testCurrentWhenNoCurrentProgram();
        test.testDetachShaderWithAttachedShader();
        test.testDetachShaderWithUnattachedShader();
        test.testLinkWithGoodVertexAndFragmentShader();
        test.testLinkWithBadVertexAndFragmentShader();
        test.testAttribLocationWithBadName();
        test.testAttribLocationWithGoodName();
        test.testActiveAttributes();
        test.testFragDataLocationWithBadName();
        test.testFragDataLocationWithGoodName();
        test.testUniformLocationWithBadName();
        test.testUniformLocationWithGoodName();
        test.testActiveUniforms();
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

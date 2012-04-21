/*
 * ProgramTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <GL/glfw.h>
#include "glycerin/common.h"
#include "glycerin/shader/Program.hpp"
using namespace std;
using namespace Glycerin;
namespace bfs = boost::filesystem;


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
     * Ensures attaching a bad shader throws an exception.
     */
    void testAttachShaderWithBadShader() {
        Program program = Program::create();
        const GLuint shader = -1;
        try {
            program.attachShader(shader);
        } catch (invalid_argument& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught!");
    }

    /**
     * Ensures a good shader that hasn't been attached yet can be attached.
     */
    void testAttachShaderWithGoodUnattachedShader() {

        // Attach a shader
        Program program = Program::create();
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        program.attachShader(shader);

        // Check if it was attached
        GLint num;
        glGetProgramiv(program.handle(), GL_ATTACHED_SHADERS, &num);
        assert (num == 1);
    }

    /**
     * Ensures a good shader that has already been attached can't be attached.
     */
    void testAttachShaderWithGoodAttachedShader() {

        // Attach a shader
        Program program = Program::create();
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        program.attachShader(shader);

        // Try to attach shader
        try {
            program.attachShader(shader);
        } catch (invalid_argument& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught!");
    }

    /**
     * Ensures create returns a program with a valid handle.
     */
    void testCreate() {
        Program program = Program::create();
        assert (program.handle() > 0);
    }

    /**
     * Ensures Program links with a vertex and fragment shader.
     */
    void testLinkWithGoodVertexAndFragmentShader() {

        // Create a program
        Program program = Program::create();
        assert (program.handle() > 0);

        // Create shaders
        Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(GOOD_VERTEX_SHADER);
        vs.compile();
        Shader fs = Shader::create(GL_FRAGMENT_SHADER);
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
            throw runtime_error("Could not link program!");
        }

        // Validate it
        program.validate();
        if (!program.valid()) {
            cerr << program.log() << endl;
            throw runtime_error("Could not validate program!");
        }

        // Delete it
        program.dispose();
    }

    /**
     * Ensures Program does not link and validate with a bad vertex and fragment shader.
     */
    void testLinkWithBadVertexAndFragmentShader() {

        // Create a program
        Program program = Program::create();
        assert (program.handle() > 0);

        // Create shaders
        Shader vs = Shader::create(GL_VERTEX_SHADER);
        vs.source(BAD_VERTEX_SHADER);
        vs.compile();
        Shader fs = Shader::create(GL_FRAGMENT_SHADER);
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
        if (program.linked()) {
            throw runtime_error("Linked bad program!");
        }

        // Delete it
        program.dispose();
    }

    /**
     * Ensures wrap does not throw an exception with a good handle.
     */
    void testWrapWithGoodHandle() {
        const GLuint handle = glCreateProgram();
        assert (handle > 0);
        Program program = Program::wrap(handle);
    }

    /**
     * Ensures wrap throws an exception with a bad handle.
     */
    void testWrapWithBadHandle() {
        const GLuint handle = -1;
        try {
            Program program = Program::wrap(handle);
        } catch (std::invalid_argument) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught!");
    }
};

int main(int argc, char *argv[]) {

    // Capture the initial working directory before GLFW changes it
    bfs::path dir = bfs::initial_path();

    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Could not initialize GLFW!" << endl;
        return 1;
    }

    // Reset current directory
    bfs::current_path(dir);

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
        test.testLinkWithGoodVertexAndFragmentShader();
        test.testLinkWithBadVertexAndFragmentShader();
        test.testWrapWithGoodHandle();
        test.testWrapWithBadHandle();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

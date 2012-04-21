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
#include "glycerin/shader/ShaderFactory.hpp"
using namespace std;
using namespace Glycerin;
namespace bfs = boost::filesystem;


const char* VERTEX_SHADER =
        "#version 140\n"
        "uniform mat4 MVPMatrix = mat4(1);\n"
        "in vec4 MCVertex;\n"
        "void main() {\n"
        "    gl_Position = MVPMatrix * MCVertex;\n"
        "}\n";

const char* FRAGMENT_SHADER =
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
     * Ensures Program links with a vertex and fragment shader.
     */
    void testLinkWithVertexAndFragmentShader() {

        // Create a program
        Program program = Program::create();
        assert (program.handle() > 0);

        // Create shaders
        ShaderFactory sf;
        Shader vs = sf.createShaderFromString(GL_VERTEX_SHADER, VERTEX_SHADER);
        Shader fs = sf.createShaderFromString(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);

        // Add the shaders to the program
        program.attachShader(vs);
        program.attachShader(fs);

        // Delete the shaders
        vs.dispose();
        fs.dispose();

        // Make the program
        program.link();
        if (!program.linked()) {
            cout << program.log() << endl;
        }

        // Delete it
        program.dispose();
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
        test.testLinkWithVertexAndFragmentShader();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

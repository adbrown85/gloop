/*
 * ShaderTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <stdexcept>
#include <GL/glfw.h>
#include "glycerin/shader/Shader.hpp"
using namespace std;
using namespace Glycerin;


/**
 * Unit test for Shader.
 */
class ShaderTest {
public:

    /**
     * Ensures making a new fragment shader works.
     */
    void testCreateWithFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        if (glGetError() != 0) {
            throw new runtime_error("Could not create fragment shader!");
        }
        shader.dispose();
    }

    /**
     * Ensures making a new geometry shader works.
     */
    void testCreateWithGeometryShader() {
        Shader shader = Shader::create(GL_GEOMETRY_SHADER);
        if (glGetError() != 0) {
            throw new runtime_error("Could not create geometry shader!");
        }
        shader.dispose();
    }

    /**
     * Ensures making a new vertex shader works.
     */
    void testCreateWithVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        if (glGetError() != 0) {
            throw new runtime_error("Could not create vertex shader!");
        }
        shader.dispose();
    }

    /**
     * Ensures setSource works correctly.
     */
    void testSetSource() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");
        cout << shader.source() << endl;
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
        test.testCreateWithFragmentShader();
        test.testCreateWithGeometryShader();
        test.testCreateWithVertexShader();
        test.testSetSource();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw e;
    }

    // Exit
    glfwTerminate();
    return 0;
}

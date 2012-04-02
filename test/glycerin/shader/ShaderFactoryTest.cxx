/*
 * ShaderFactoryTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include <stdexcept>
#include <GL/glfw.h>
#include "glycerin/shader/ShaderFactory.hpp"
using namespace std;
using namespace Glycerin;


/**
 * Unit test for ShaderFactory.
 */
class ShaderFactoryTest {
public:

    /**
     * Ensures createShaderFromString works correctly with a vertex shader.
     */
    void testCreateShaderFromStringWithVertexShader() {
        ShaderFactory sf;
        GLuint shader = sf.createShaderFromString(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "   gl_Position = MCVertex;\n"
                "}\n");
        assert (shader != 0);
    }

    /**
     * Ensures createShaderFromString works correctly with a fragment shader.
     */
    void testCreateShaderFromStringWithFragmentShader() {
        ShaderFactory sf;
        GLuint shader = sf.createShaderFromString(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        assert (shader != 0);
    }
};

int main(int argc, char* argv[]) {

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
    ShaderFactoryTest test;
    try {
        test.testCreateShaderFromStringWithVertexShader();
        test.testCreateShaderFromStringWithFragmentShader();
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    // Exit
    glfwTerminate();
    return 0;
}

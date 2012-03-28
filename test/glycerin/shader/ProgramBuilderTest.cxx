/*
 * ProgramBuilderTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <GL/glfw.h>
#include "glycerin/common.h"
#include "glycerin/shader/ProgramBuilder.hpp"
#include "glycerin/shader/ShaderFactory.hpp"
using namespace std;
using namespace Glycerin;

/**
 * Unit test for ProgramBuilder.
 */
class ProgramBuilderTest {
public:

    /**
     * Ensures toProgram works correctly.
     */
    void testToProgramWithVertexAndFragmentShader() {

        // Create a program builder
        ProgramBuilder pb;

        // Create shaders
        const string dir = "test/glycerin/shader/";
        ShaderFactory sf;
        GLuint vs = sf.createShaderFromFile(GL_VERTEX_SHADER, dir + "ProgramBuilderTest.vert");
        GLuint fs = sf.createShaderFromFile(GL_FRAGMENT_SHADER, dir + "ProgramBuilderTest.frag");

        // Add the shaders to the program
        pb.addShader(vs);
        pb.addShader(fs);

        // Delete the shaders
        glDeleteShader(vs);
        glDeleteShader(fs);

        // Make the program
        GLuint program = pb.toProgram();
        assert(program != 0);
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
    ProgramBuilderTest test;
    try {
        test.testToProgramWithVertexAndFragmentShader();
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    // Exit
    glfwTerminate();
    return 0;
}

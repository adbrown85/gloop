/*
 * ShaderTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
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
     * Ensures a bad fragment shader does not compile correctly.
     */
    void testCompileWithBadFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    gl_Position = vec4(1);\n"
                "}\n");
        shader.compile();
        if (shader.compiled()) {
            throw new runtime_error("Compiled bad fragment shader!");
        }
    }

    /**
     * Ensures a good fragment shader compiles correctly.
     */
    void testCompileWithGoodFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        shader.compile();
        if (!shader.compiled()) {
            throw new runtime_error("Could not compile good fragment shader!");
        }
    }

    /**
     * Ensures a bad vertex shader does not compile correctly.
     */
    void testCompileWithBadVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_FragColor = MCVertex;\n"
                "}\n");
        shader.compile();
        if (shader.compiled()) {
            throw new runtime_error("Compiled bad vertex shader!");
        }
    }

    /**
     * Ensures a good vertex shader compiles correctly.
     */
    void testCompileWithGoodVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");
        shader.compile();
        if (!shader.compiled()) {
            throw new runtime_error("Could not compile good vertex shader!");
        }
    }

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
     * Ensures handle returns a valid handle with a fragment shader.
     */
    void testHandleWithFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        assert (shader.handle() > 0);
    }

    /**
     * Ensures handle returns a valid handle with a geometry shader.
     */
    void testHandleWithGeometryShader() {
        Shader shader = Shader::create(GL_GEOMETRY_SHADER);
        assert (shader.handle() > 0);
    }

    /**
     * Ensures handle returns a valid handle with a vertex shader.
     */
    void testHandleWithVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        assert (shader.handle() > 0);
    }

    /**
     * Ensures compiling a bad fragment shader generates a log.
     */
    void testLogWithBadFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    gl_Position = vec4(1);\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        assert (!log.empty());
    }

    /**
     * Ensures compiling a good fragment shader generates an empty log.
     */
    void testLogWithGoodFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        assert (log.empty());
    }

    /**
     * Ensures compiling a bad vertex shader generates a log.
     */
    void testLogWithBadVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    FragColor = MCVertex;\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        assert (!log.empty());
    }

    /**
     * Ensures compiling a good vertex shader generates an empty log.
     */
    void testLogWithGoodVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        shader.source(
                "#version 140\n"
                "out vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n");
        shader.compile();
        const string log = shader.log();
        assert (log.empty());
    }

    /**
     * Ensures equality operator returns true for shaders with the same handle.
     */
    void testOperatorEqualEqualWithEqual() {
        Shader s1 = Shader::create(GL_VERTEX_SHADER);
        Shader s2 = Shader::wrap(s1.handle());
        assert (s1 == s2);
    }

    /**
     * Ensures inequality operator returns true for shaders with different handles.
     */
    void testOperatorNotEqualWithUnequal() {
        Shader s1 = Shader::create(GL_VERTEX_SHADER);
        Shader s2 = Shader::create(GL_VERTEX_SHADER);
        assert (s1 != s2);
    }

    /**
     * Ensures both forms of source works correctly.
     */
    void testSource() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        string source =
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "    gl_Position = MCVertex;\n"
                "}\n";
        shader.source(source);
        assert (shader.source() == source);
    }

    /**
     * Ensures a fragment shader's type is GL_FRAGMENT_SHADER.
     */
    void testTypeWithFragmentShader() {
        Shader shader = Shader::create(GL_FRAGMENT_SHADER);
        assert(shader.type() == GL_FRAGMENT_SHADER);
    }

    /**
     * Ensures a geometry shader's type is GL_GEOMETRY_SHADER.
     */
    void testTypeWithGeometryShader() {
        Shader shader = Shader::create(GL_GEOMETRY_SHADER);
        assert(shader.type() == GL_GEOMETRY_SHADER);
    }

    /**
     * Ensures a vertex shader's type is GL_VERTEX_SHADER.
     */
    void testTypeWithVertexShader() {
        Shader shader = Shader::create(GL_VERTEX_SHADER);
        assert(shader.type() == GL_VERTEX_SHADER);
    }

    /**
     * Ensures wrapping an existing shader works correctly.
     */
    void testWrap() {
        const GLuint handle = glCreateShader(GL_FRAGMENT_SHADER);
        Shader shader = Shader::wrap(handle);
        assert (shader.handle() == handle);
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
        test.testHandleWithFragmentShader();
        test.testHandleWithGeometryShader();
        test.testHandleWithVertexShader();
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
        test.testWrap();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw e;
    }

    // Exit
    glfwTerminate();
    return 0;
}

/*
 * BufferTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include <stdexcept>
#include <GL/glfw.h>
#include "gloop/Buffer.hxx"
#include "gloop/BufferObject.hxx"
using namespace std;
using namespace Gloop;


/**
 * Unit test for Buffer.
 */
class BufferTest {
public:

    /**
     * Ensures a buffer object can be bound to the buffer target correctly.
     */
    void testBind() {

        // Create data store for buffer
        BufferObject bo = BufferObject::generate();

        // Use as the array buffer
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bo);

        // Check the binding
        GLint id;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
        assert (id == bo.id());

        // Check for OpenGL errors
        const GLuint error = glGetError();
        assert (error == GL_NO_ERROR);
    }

    /**
     * Ensures data works correctly.
     */
    void testData() {

        // Create data store for buffer
        BufferObject bo = BufferObject::generate();

        // Use as the array buffer
        const Buffer buffer = Buffer::arrayBuffer();
        buffer.bind(bo);
        buffer.data(16, NULL, GL_STATIC_DRAW);
        buffer.unbind(bo);

        // Check for OpenGL errors
        const GLuint error = glGetError();
        assert (error == GL_NO_ERROR);
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
    BufferTest test;
    try {
        test.testBind();
        test.testData();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

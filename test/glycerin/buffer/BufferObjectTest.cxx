/*
 * BufferObjectTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cassert>
#include <stdexcept>
#include <GL/glfw.h>
#include "glycerin/buffer/BufferObject.hpp"
using namespace std;
using namespace Glycerin;


/**
 * Unit test for BufferObject.
 */
class BufferObjectTest {
public:

    /**
     * Ensures buffer object returned by generate is valid.
     */
    void testGenerate() {
        const BufferObject bo = BufferObject::generate();
        assert (bo.id() > 0);
    }

    /**
     * Ensures wrapping a bad buffer object ID throws an exception.
     */
    void testWrapWithBadId() {
        const GLuint id = -1;
        try {
            BufferObject::wrap(id);
        } catch (invalid_argument& e) {
            // Exception caught
            return;
        }
        throw runtime_error("Exception not caught!");
    }

    /**
     * Ensures wrapping a good buffer object ID does not throw an exception.
     */
    void testWrapWithGoodId() {
        GLuint id;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        assert (id > 0);
        const BufferObject bo = BufferObject::wrap(id);
        assert (bo.id() == id);
    }

    /**
     * Ensures a buffer object can be a key in an STL map.
     */
    void testAddToStlMap() {
        map<BufferObject,string> m;
        const BufferObject b1 = BufferObject::generate();
        const BufferObject b2 = BufferObject::generate();
        m[b1] = "foo";
        m[b2] = "bar";
    }

    /**
     * Ensures a buffer object can be added to an STL vector.
     */
    void testAddToStlVector() {
        vector<BufferObject> v;
        const BufferObject bo = BufferObject::generate();
        v.push_back(bo);
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
    BufferObjectTest test;
    try {
        test.testGenerate();
        test.testWrapWithBadId();
        test.testWrapWithGoodId();
        test.testAddToStlMap();
        test.testAddToStlVector();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}

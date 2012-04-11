/**
 * Shader.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_SHADER_HPP
#define GLYCERIN_SHADER_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * OpenGL shader.
 */
class Shader {
public:
// Methods
    static Shader* newInstance(GLenum type);
    ~Shader();
    void compile();
    bool compiled() const;
    GLuint handle() const;
    std::string log() const;
    std::string source() const;
    void source(const std::string& source);
    GLenum type() const;
private:
// Attributes
    const GLuint _handle;
// Methods
    Shader(GLuint handle);
    Shader(const Shader& shader);
    Shader& operator=(const Shader& shader);
};

} /* namespace Glycerin */
#endif

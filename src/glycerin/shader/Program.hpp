/*
 * Program.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_PROGRAM_HPP
#define GLYCERIN_PROGRAM_HPP
#include "glycerin/common.h"
#include <vector>
#include "glycerin/shader/Attribute.hpp"
#include "glycerin/shader/Shader.hpp"
#include "glycerin/shader/Uniform.hpp"
namespace Glycerin {


/**
 * Wrapper around an OpenGL shader program.
 */
class Program {
public:
// Methods
    explicit Program();
    explicit Program(GLuint handle);
    Program(const Program& program);
    void attachShader(GLuint shader);
    GLuint attribLocation(const std::string& name) const;
    void attribLocation(const std::string& name, GLuint location);
    std::vector<Attribute> attributes() const;
    void detachShader(GLuint shader);
    void dispose();
    GLint fragDataLocation(const std::string& name) const;
    void fragDataLocation(const std::string& name, GLuint location);
    GLuint handle() const;
    void link();
    bool linked() const;
    std::string log() const;
    Program& operator=(const Program& program);
    bool operator==(const Program& program) const;
    bool operator!=(const Program& program) const;
    std::vector<Shader> shaders() const;
    std::vector<Uniform> uniforms() const;
    void use() const;
    bool valid() const;
    void validate();
private:
// Attributes
    GLuint _handle;
// Methods
    static GLint getMaxDrawBuffers();
};

} /* namespace Glycerin */
#endif


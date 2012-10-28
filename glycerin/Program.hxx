/*
 * Program.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_PROGRAM_HXX
#define GLYCERIN_PROGRAM_HXX
#include "glycerin/common.h"
#include <map>
#include <vector>
#include "glycerin/Attribute.hxx"
#include "glycerin/Shader.hxx"
#include "glycerin/Uniform.hxx"
namespace Glycerin {


/**
 * Wrapper around an OpenGL shader program.
 *
 * @ingroup core
 */
class Program {
public:
// Methods
    Program(const Program& program);
    std::map<std::string,Attribute> activeAttributes() const;
    std::map<std::string,Uniform> activeUniforms() const;
    void attachShader(GLuint shader);
    void attachShader(const Shader& shader);
    GLint attribLocation(const std::string& name) const;
    void attribLocation(const std::string& name, GLuint location);
    static Program create();
    void detachShader(GLuint shader);
    void detachShader(const Shader& shader);
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
    GLint uniformLocation(const std::string& name) const;
    void use() const;
    bool valid() const;
    void validate();
    static Program wrap(GLuint handle);
private:
// Attributes
    GLuint _handle;
// Methods
    explicit Program(GLuint handle);
    Program();
    static GLint getMaxDrawBuffers();
    bool isAttached(const Shader& shader) const;
};

} /* namespace Glycerin */
#endif


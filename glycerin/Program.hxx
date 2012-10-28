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
 * Handle for an OpenGL shader program.
 *
 * @ingroup core
 */
class Program {
public:
// Methods
    Program(const Program& program);
    ~Program();
    std::map<std::string,Attribute> activeAttributes() const;
    std::map<std::string,Uniform> activeUniforms() const;
    void attachShader(GLuint shader) const;
    void attachShader(const Shader& shader) const;
    GLint attribLocation(const std::string& name) const;
    void attribLocation(const std::string& name, GLuint location) const;
    static Program create();
    void detachShader(GLuint shader) const;
    void detachShader(const Shader& shader) const;
    void dispose() const;
    GLint fragDataLocation(const std::string& name) const;
    void fragDataLocation(const std::string& name, GLuint location) const;
    GLuint id() const;
    void link() const;
    bool linked() const;
    std::string log() const;
    Program& operator=(const Program& program);
    bool operator==(const Program& program) const;
    bool operator!=(const Program& program) const;
    bool operator<(const Program& program) const;
    std::vector<Shader> shaders() const;
    GLint uniformLocation(const std::string& name) const;
    void use() const;
    bool valid() const;
    void validate() const;
    static Program wrap(GLuint id);
private:
// Attributes
    GLuint _id;
// Methods
    explicit Program(GLuint id);
    Program();
    static GLint getMaxDrawBuffers();
    bool isAttached(const Shader& shader) const;
};

} /* namespace Glycerin */
#endif


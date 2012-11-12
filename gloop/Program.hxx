/*
 * Program.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_PROGRAM_HXX
#define GLOOP_PROGRAM_HXX
#include "gloop/common.h"
#include <map>
#include <vector>
#include "gloop/Attribute.hxx"
#include "gloop/Shader.hxx"
#include "gloop/Uniform.hxx"
namespace Gloop {


/**
 * Handle for an OpenGL shader program.
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
    static Program fromId(GLuint id);
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
private:
// Attributes
    GLuint _id;
// Methods
    explicit Program(GLuint id);
    Program();
    static GLint getMaxDrawBuffers();
    bool isAttached(const Shader& shader) const;
};

} /* namespace Gloop */
#endif


/**
 * Shader.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_SHADER_HXX
#define GLOOP_SHADER_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * OpenGL shader.
 */
class Shader {
public:
// Methods
    Shader(const Shader& shader);
    ~Shader();
    void compile() const;
    bool compiled() const;
    static Shader create(GLenum type);
    void dispose() const;
    static Shader fromId(GLuint id);
    GLuint id() const;
    std::string log() const;
    Shader& operator=(const Shader& shader);
    bool operator==(const Shader& shader) const;
    bool operator!=(const Shader& shader) const;
    bool operator<(const Shader& shader) const;
    std::string source() const;
    void source(const std::string& source) const;
    GLenum type() const;
private:
// Attributes
    GLuint _id;
// Methods
    explicit Shader(GLuint id);
};

} /* namespace Gloop */
#endif

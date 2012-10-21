/**
 * Shader.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_SHADER_HXX
#define GLYCERIN_SHADER_HXX
#include "glycerin/common.h"
namespace Glycerin {


/**
 * OpenGL shader.
 *
 * @ingroup core
 */
class Shader {
public:
// Methods
    Shader(const Shader& shader);
    ~Shader();
    void compile();
    bool compiled() const;
    static Shader create(GLenum type);
    void dispose();
    GLuint handle() const;
    std::string log() const;
    Shader& operator=(const Shader& shader);
    bool operator==(const Shader& shader) const;
    bool operator!=(const Shader& shader) const;
    std::string source() const;
    void source(const std::string& source);
    GLenum type() const;
    static Shader wrap(GLuint handle);
private:
// Attributes
    GLuint _handle;
// Methods
    explicit Shader(GLuint handle);
};

} /* namespace Glycerin */
#endif

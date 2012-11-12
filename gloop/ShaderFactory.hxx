/*
 * ShaderFactory.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_SHADER_FACTORY_HXX
#define GLOOP_SHADER_FACTORY_HXX
#include "gloop/common.h"
#include "gloop/Shader.hxx"
namespace Gloop {


/**
 * Utility for creating shaders.
 *
 * @ingroup extensions
 */
class ShaderFactory {
public:
    ShaderFactory();
    Shader createShaderFromFile(GLenum type, const std::string& filename);
    Shader createShaderFromStream(GLenum type, std::istream& stream);
    Shader createShaderFromString(GLenum type, const std::string& str);
private:
// Helpers
    static std::string getLog(const GLuint id);
    static bool isCompiled(const GLuint id);
// Operators
    ShaderFactory& operator=(const ShaderFactory&);
};

} /* namespace Gloop */
#endif

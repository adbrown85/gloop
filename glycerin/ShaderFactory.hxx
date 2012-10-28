/*
 * ShaderFactory.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_SHADER_FACTORY_HXX
#define GLYCERIN_SHADER_FACTORY_HXX
#include "glycerin/common.h"
#include "glycerin/Shader.hxx"
namespace Glycerin {


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

} /* namespace Glycerin */
#endif

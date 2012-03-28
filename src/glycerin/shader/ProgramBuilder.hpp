/*
 * ProgramBuilder.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_PROGRAMBUILDER_HPP
#define GLYCERIN_PROGRAMBUILDER_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Utility for building shader programs.
 *
 * @ingroup shader
 */
class ProgramBuilder {
public:
    ProgramBuilder();
    virtual ~ProgramBuilder();
    virtual void addShader(GLuint shader);
    virtual void bindAttribute(GLuint index, const std::string &name);
    virtual void reset();
    virtual GLuint toProgram();
private:
// Attributes
    std::list<GLuint> shaders;
    std::map<GLuint,std::string> locations;
// Helpers
    static std::string getLog(GLuint handle);
    static bool isLinked(GLuint handle);
// Constructors
    ProgramBuilder(const ProgramBuilder&);
    ProgramBuilder& operator=(const ProgramBuilder&);
};

} /* namespace Glycerin */
#endif

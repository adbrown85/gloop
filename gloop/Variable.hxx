/*
 * Variable.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_VARIABLE_HXX
#define GLOOP_VARIABLE_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Input to a shader program.
 *
 * @ingroup core
 */
class Variable {
public:
// Methods
    virtual GLint location() const;
    virtual std::string name() const;
    virtual GLuint program() const;
    virtual GLint size() const;
    virtual GLenum type() const;
protected:
// Methods
    Variable(GLint location, const std::string& name, GLuint program, GLint size, GLenum type);
    virtual ~Variable();
private:
// Attributes
    GLint _location;
    std::string _name;
    GLuint _program;
    GLint _size;
    GLenum _type;
};

} /* namespace Gloop */
#endif

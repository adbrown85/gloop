/*
 * Uniform.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_UNIFORM_HXX
#define GLOOP_UNIFORM_HXX
#include "gloop/common.h"
#include "gloop/Variable.hxx"
namespace Gloop {


/**
 * OpenGL uniform information.
 *
 * @ingroup core
 */
class Uniform : public Variable {
// Friends
    friend class Program;
public:
// Methods
    void load1f(GLfloat x);
    void load2f(GLfloat x, GLfloat y);
    void load3f(GLfloat x, GLfloat y, GLfloat z);
    void load4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void load1i(GLint x);
    void load2i(GLint x, GLint y);
    void load3i(GLint x, GLint y, GLint z);
    void load4i(GLint x, GLint y, GLint z, GLint w);
    void load1ui(GLuint x);
    void load2ui(GLuint x, GLuint y);
    void load3ui(GLuint x, GLuint y, GLuint z);
    void load4ui(GLuint x, GLuint y, GLuint z, GLuint w);
    void load1fv(GLsizei count, const GLfloat* value);
    void load2fv(GLsizei count, const GLfloat* value);
    void load3fv(GLsizei count, const GLfloat* value);
    void load4fv(GLsizei count, const GLfloat* value);
    void load1iv(GLsizei count, const GLint* value);
    void load2iv(GLsizei count, const GLint* value);
    void load3iv(GLsizei count, const GLint* value);
    void load4iv(GLsizei count, const GLint* value);
    void load1uiv(GLsizei count, const GLuint* value);
    void load2uiv(GLsizei count, const GLuint* value);
    void load3uiv(GLsizei count, const GLuint* value);
    void load4uiv(GLsizei count, const GLuint* value);
    void loadMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat* value);
    void loadMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat* value);
    void loadMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat* value);
    void loadMatrix2x3fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix3x2fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix2x4fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix4x2fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix3x4fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    void loadMatrix4x3fv(GLsizei count, GLboolean transpose, const GLfloat *value);
private:
// Methods
    Uniform(GLint location, const std::string& name, GLuint program, GLint size, GLenum type);
    static GLuint currentProgram();
};

} /* namespace Gloop */
#endif

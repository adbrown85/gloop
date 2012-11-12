/*
 * ErrorChecker.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_ERRORCHECKER_HXX
#define GLOOP_ERRORCHECKER_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Utility for checking for OpenGL errors.
 *
 * @ingroup extensions
 */
class ErrorChecker {
public:
    static void checkErrors(const std::string &location);
    static void clearErrors();
private:
    static void report(GLenum error, const std::string &location);
    static std::string toString(GLenum error);
// Constructors
    ErrorChecker();
    ErrorChecker(const ErrorChecker&);
    ErrorChecker& operator=(const ErrorChecker&);
};

} /* namespace Gloop */
#endif

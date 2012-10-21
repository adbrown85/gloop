/*
 * ErrorChecker.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_ERRORCHECKER_HXX
#define GLYCERIN_ERRORCHECKER_HXX
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Utility for checking for OpenGL errors.
 *
 * @ingroup system
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

} /* namespace Glycerin */
#endif

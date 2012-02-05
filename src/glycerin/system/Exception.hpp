/*
 * Exception.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_EXCEPTION_HPP
#define GLYCERIN_EXCEPTION_HPP
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Exception thrown from within Glycerin.
 */
class Exception : public std::exception {
public:
    Exception(const std::string &message) throw();
    virtual ~Exception() throw();
    virtual const char* what() const throw();
private:
    std::string message;
};

} /* namespace Glycerin */
#endif

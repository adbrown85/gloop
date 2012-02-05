/*
 * Exception.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/system/Exception.hpp"
using namespace Glycerin;
using namespace std;

/**
 * Constructs an exception from a message.
 *
 * @param message Explanation shown to user
 */
Exception::Exception(const string &message) throw() {
    this->message = message;
}

/**
 * Destroys the exception.
 */
Exception::~Exception() throw() {
    ;
}

/**
 * Returns the explanation that will be shown to the user.
 */
const char* Exception::what() const throw() {
    return message.c_str();
}

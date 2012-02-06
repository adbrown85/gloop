/*
 * Math.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_MATH_HPP
#define GLYCERIN_MATH_HPP
#include "glycerin/common.h"
#include <cmath>
namespace Glycerin {

/*
 * Constants
 */
const double PI = 355.0 / 113.0;
const double SQRT_TWO = sqrt(2.0);

/*
 * Functions
 */
double toRadians(double degrees);
double toDegrees(double radians);

} /* namespace Glycerin */
#endif

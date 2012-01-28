/*
 * Quat.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_QUAT_HPP
#define GLYCERIN_QUAT_HPP
#include "glycerin/common.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "glycerin/math/Mat3.hpp"
#include "glycerin/math/Mat4.hpp"
#include "glycerin/math/Vec3.hpp"
namespace Glycerin {


/**
 * Encapsulation of an axis/angle rotation.
 *
 * @ingroup math
 */
class Quat {
public:
// Attributes
    double x; ///< First component of quaternion's vector part
    double y; ///< Second component of quaternion's vector part
    double z; ///< Third component of quaternion's vector part
    double w; ///< Scalar part of quaternion
// Methods
    Quat();
    Quat(double x, double y, double z, double w);
    static Quat fromAxisAngle(const Vec3& axis, const double angle);
    static Quat fromMat3(const Mat3& m);
    static Quat fromMat4(const Mat4& m);
    static Quat identity();
    bool isIdentity() const;
    bool isInfinite() const;
    bool isNaN() const;
    bool operator==(const Quat& q) const;
    bool operator!=(const Quat& q) const;
    double operator[](int i) const;
    double& operator[](int i);
    Quat operator+() const;
    Quat operator-() const;
    Quat operator+(const Quat& q) const;
    Quat operator-(const Quat& q) const;
    Quat operator*(const Quat& q) const;
    Mat3 toMat3() const;
    Mat4 toMat4() const;
    std::string toString() const;
// Friends
    friend Quat conjugate(const Quat& q);
    friend double magnitude(const Quat& q);
    friend Quat normalize(const Quat& q);
};

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream& stream, const Glycerin::Quat& q);

#endif

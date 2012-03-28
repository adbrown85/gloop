/*
 * Vec3.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_VEC3_HPP
#define GLYCERIN_VEC3_HPP
#include "glycerin/common.h"
#include <cmath>
#include <iomanip>
namespace Glycerin {


/**
 * Three-component vector for 3D graphics.
 *
 * @ingroup math
 */
class Vec3 {
public:
// Attributes
    double x; ///< X coordinate
    double y; ///< Y coordinate
    double z; ///< Z coordinate
// Methods
    explicit Vec3();
    explicit Vec3(double d);
    explicit Vec3(double x, double y, double z);
    explicit Vec3(double arr[3]);
    explicit Vec3(float arr[3]);
    double operator[](int i) const;
    double& operator[](int i);
    Vec3 operator+() const;
    Vec3 operator-() const;
    bool operator==(const Vec3 &v) const;
    bool operator!=(const Vec3 &v) const;
    Vec3 operator+(double d) const;
    Vec3 operator+(const Vec3 &v) const;
    Vec3& operator+=(double d);
    Vec3& operator+=(const Vec3 &v);
    Vec3 operator-(const Vec3 &v) const;
    Vec3 operator-(double d) const;
    Vec3& operator-=(double d);
    Vec3& operator-=(const Vec3 &v);
    Vec3 operator*(double d) const;
    Vec3 operator*(const Vec3 &v) const;
    Vec3& operator*=(double d);
    Vec3& operator*=(const Vec3 &v);
    Vec3 operator/(double d) const;
    Vec3 operator/(const Vec3 &v) const;
    Vec3& operator/=(double d);
    Vec3& operator/=(const Vec3 &v);
    void toArray(double arr[3]) const;
    void toArray(float arr[3]) const;
    std::string toString() const;
// Friends
    friend Vec3 cross(const Vec3 &u, const Vec3 &v);
    friend double dot(const Vec3 &u, const Vec3 &v);
    friend double length(const Vec3 &v);
    friend Vec3 max(const Vec3 &u, const Vec3 &v);
    friend double max(const Vec3 &v);
    friend Vec3 min(const Vec3 &u, const Vec3 &v);
    friend double min(const Vec3 &v);
    friend Vec3 normalize(const Vec3 &v);
};

} // namespace Glycerin

std::ostream& operator<<(std::ostream &out, const Glycerin::Vec3 &u);
#endif

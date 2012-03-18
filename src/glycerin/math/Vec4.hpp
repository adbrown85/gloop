/*
 * Vec4.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_VEC4_HPP
#define GLYCERIN_VEC4_HPP
#include "glycerin/common.h"
#include "glycerin/math/Vec3.hpp"
#include "glycerin/system/Exception.hpp"
namespace Glycerin {


/**
 * Four-component vector for 3D graphics.
 *
 * @ingroup math
 */
class Vec4 {
public:
    double x; ///< X coordinate
    double y; ///< Y coordinate
    double z; ///< Z coordinate
    double w; ///< Homogeneous coordinate
public:
    explicit Vec4();
    explicit Vec4(double d);
    explicit Vec4(const Vec3& v, double w);
    explicit Vec4(double x, double y, double z, double w);
    explicit Vec4(double arr[4]);
    explicit Vec4(float arr[4]);
    double operator[](int i) const;
    double& operator[](int i);
    bool operator==(const Vec4 &v) const;
    bool operator!=(const Vec4 &v) const;
    Vec4 operator+() const;
    Vec4 operator-() const;
    Vec4 operator+(double f) const;
    Vec4 operator+(const Vec4 &v) const;
    Vec4& operator+=(double f);
    Vec4& operator+=(const Vec4 &v);
    Vec4 operator-(double f) const;
    Vec4 operator-(const Vec4 &v) const;
    Vec4& operator-=(const Vec4 &v);
    Vec4& operator-=(double f);
    Vec4 operator*(const Vec4 &v) const;
    Vec4 operator*(double f) const;
    Vec4& operator*=(double f);
    Vec4& operator*=(const Vec4 &v);
    Vec4 operator/(const Vec4 &v) const;
    Vec4 operator/(double f) const;
    Vec4& operator/=(const Vec4 &v);
    Vec4& operator/=(double f);
    void toArray(double arr[4]);
    void toArray(float arr[4]);
    std::string toString() const;
// Friends
    friend double dot(const Vec4& u, const Vec4 &v);
    friend double length(const Vec4 &v);
    friend double min(const Vec4 &v);
    friend Vec4 min(const Vec4 &u, const Vec4 &v);
    friend double max(const Vec4 &v);
    friend Vec4 max(const Vec4 &u, const Vec4 &v);
    friend Vec4 normalize(const Vec4 &v);
};

} // namespace Glycerin

std::ostream& operator<<(std::ostream& out, const Glycerin::Vec4& u);
#endif

/*
 * Quat.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <algorithm>
#include "glycerin/math/Quat.hpp"
using namespace std;
namespace Glycerin {

/**
 * Constructs a quaternion from all zeros.
 */
Quat::Quat() : x(0), y(0), z(0), w(0) {
    // pass
}

/**
 * Constructs a quaternion from explicit components.
 *
 * @param x X component of vector part of quaternion
 * @param y Y component of vector part of quaternion
 * @param z Z component of vector part of quaternion
 * @param w Scalar component of quaternion
 */
Quat::Quat(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {
    // pass
}

/**
 * Creates a quaternion representing an angle/axis rotation.
 *
 * @param axis Axis of rotation
 * @param angle Angle around axis in radians
 * @return Equivalent quaternion
 */
Quat Quat::fromAxisAngle(const Vec3& axis, const double angle) {

    Quat q;

    // Calculate
    const double halfAngle = 0.5 * angle;
    const double sinHalfAngle = sin(halfAngle);
    q.x = axis.x * sinHalfAngle;
    q.y = axis.y * sinHalfAngle;
    q.z = axis.z * sinHalfAngle;
    q.w = cos(halfAngle);

    // Normalize
    const double xx = q.x * q.x;
    const double yy = q.y * q.y;
    const double zz = q.z * q.z;
    const double ww = q.w * q.w;
    const double mag = sqrt(xx + yy + zz + ww);
    q.x /= mag;
    q.y /= mag;
    q.z /= mag;
    q.w /= mag;

    return q;
}

/**
 * Creates a quaternion from a 3x3 matrix.
 *
 * @param m 3x3 matrix to make quaternion from
 * @return Resulting quaternion
 */
Quat Quat::fromMat3(const Mat3& m) {

    // Fetch diagonal
    const double m00 = m(0,0);
    const double m11 = m(1,1);
    const double m22 = m(2,2);

    // Solve for scalar
    const double trace = m00 + m11 + m22;
    const double w = sqrt(std::max(0.0, trace + 1)) / 2;

    // Solve for vector
    const double ww = w * w;
    const double x = sqrt(std::max(0.0, (m00 + 1 - 2 * ww) / 2));
    const double y = sqrt(std::max(0.0, (m11 + 1 - 2 * ww) / 2));
    const double z = sqrt(std::max(0.0, (m22 + 1 - 2 * ww) / 2));

    // Make quaternion
    return Quat(x, y, z, w);
}

/**
 * Creates a quaternion from a 4x4 matrix.
 *
 * @param m 4x4 matrix to make quaternion from
 * @return Resulting quaternion
 */
Quat Quat::fromMat4(const Mat4& m) {
    return fromMat3(m.toMat3());
}

/**
 * Returns a copy of the identity quaternion.
 */
Quat Quat::identity() {
    return Quat(0, 0, 0, 1);
}

/**
 * Checks if the quaternion is the identity quaternion.
 *
 * @return <tt>true</tt> if exactly equal to the identity quaternion
 */
bool Quat::isIdentity() const {
    return (x == 0) && (y == 0) && (z == 0) && (w == 1);
}

/**
 * Checks if the quaternion has any infinite components.
 *
 * @return <tt>true</tt> if any component is infinite
 */
bool Quat::isInfinite() const {
    return isinf(x) || isinf(y) || isinf(z) || isinf(w);
}

/**
 * Checks if the quaternion has any Not-a-Number (NaN) components.
 *
 * @return <tt>true</tt> if any component is Not-a-Number (NaN)
 */
bool Quat::isNaN() const {
    return isnan(x) || isnan(y) || isnan(z) || isnan(w);
}

/**
 * Checks if a quaternion equals this one.
 *
 * @param q Quaternion to check
 * @return <tt>true</tt> if quaternion is exactly equal
 */
bool Quat::operator==(const Quat &q) const {
    return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w);
}

/**
 * Checks if a quaternion does not equal this one.
 *
 * @param q Quaternion to check
 * @return <tt>true</tt> if quaternion is not exactly equal
 */
bool Quat::operator!=(const Quat &q) const {
    return (x != q.x) || (y != q.y) || (z != q.z) || (w != q.w);
}

/**
 * Accesses a component of the quaternion by index.
 *
 * @param i Index of the component, in [0 .. 3]
 * @return Copy of the component
 * @throws std::exception if index is out of bounds
 */
double Quat::operator[](int i) const {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Quat] Index out of bounds!");
    }
}

/**
 * Accesses a component of the quaternion by index.
 *
 * @param i Index of the component, in [0 .. 3]
 * @return Reference to the component
 * @throws std::exception if index is out of bounds
 */
double& Quat::operator[](int i) {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Quat] Index out of bounds!");
    }
}

/**
 * Returns a copy of the quaternion with the same sign.
 */
Quat Quat::operator+() const {
    return Quat(x, y, z, w);
}

/**
 * Returns the additive inverse of the quaternion.
 */
Quat Quat::operator-() const {
    return Quat(-x, -y, -z, -w);
}

/**
 * Adds a quaternion to this quaternion, making a new quaternion.
 *
 * @param q Quaternion to add
 * @return Copy of the resulting quaternion
 */
Quat Quat::operator+(const Quat& q) const {
    const double rx = x + q.x;
    const double ry = y + q.y;
    const double rz = z + q.z;
    const double rw = w + q.w;
    return Quat(rx, ry, rz, rw);
}

/**
 * Subtracts a quaternion from this quaternion, making a new quaternion.
 *
 * @param q Quaternion to subtract
 * @return Resulting quaternion
 */
Quat Quat::operator-(const Quat& q) const {
    const double rx = x - q.x;
    const double ry = y - q.y;
    const double rz = z - q.z;
    const double rw = w - q.w;
    return Quat(rx, ry, rz, rw);
}

/**
 * Multiplies a quaternion by another quaternion.
 *
 * @param q Quaternion to multiply by
 * @return Result of multiplication
 */
Quat Quat::operator*(const Quat& q) const {
    const double rx = w * q.x + q.w * x + y * q.z - z * q.y;
    const double ry = w * q.y + q.w * y + z * q.x - x * q.z;
    const double rz = w * q.z + q.w * z + x * q.y - y * q.x;
    const double rw = w * q.w - x * q.x - y * q.y - z * q.z;
    return Quat(rx, ry, rz, rw);
}

/**
 * Returns a 3x3 matrix corresponding to the quaternion's rotation.
 */
Mat3 Quat::toMat3() const {

    // Calculate intermediate values
    const double xx2 = x * x * 2;
    const double yy2 = y * y * 2;
    const double zz2 = z * z * 2;
    const double xy2 = x * y * 2;
    const double xz2 = x * z * 2;
    const double yz2 = y * z * 2;
    const double wx2 = w * x * 2;
    const double wy2 = w * y * 2;
    const double wz2 = w * z * 2;

    // Calculate matrix
    double arr[3][3];
    arr[0][0] = 1.0 - yy2 - zz2;
    arr[0][1] = xy2 - wz2;
    arr[0][2] = xz2 + wy2;
    arr[1][0] = xy2 + wz2;
    arr[1][1] = 1.0 - xx2 - zz2;
    arr[1][2] = yz2 - wx2;
    arr[2][0] = xz2 - wy2;
    arr[2][1] = yz2 + wx2;
    arr[2][2] = 1.0 - xx2 - yy2;

    // Return matrix
    return Mat3(arr);
}

/**
 * Returns a 4x4 matrix corresponding to the quaternion's rotation.
 */
Mat4 Quat::toMat4() const {
    return Mat4(toMat3());
}

/**
 * Returns a string representation of the quaternion.
 */
string Quat::toString() const {
    stringstream stream;
    stream << (*this);
    return stream.str();
}

// FRIENDS

/**
 * Computes the conjugate of a quaternion.
 *
 * @param q Quaternion to compute conjugate of
 * @return Conjugate of quaternion
 */
Quat conjugate(const Quat& q) {
    const double x = -q.x;
    const double y = -q.y;
    const double z = -q.z;
    const double w = q.w;
    return Quat(x, y, z, w);
}

/**
 * Computes the magnitude of a quaternion.
 *
 * @param q Quaternion to compute magnitude of
 * @return Magnitude of quaternion
 */
double magnitude(const Quat& q) {
    const double xx = q.x * q.x;
    const double yy = q.y * q.y;
    const double zz = q.z * q.z;
    const double ww = q.w * q.w;
    return sqrt(xx + yy + zz + ww);
}

/**
 * Computes a unit quaternion from another quaternion.
 *
 * @param q Quaternion to compute unit quaternion from
 * @return Resulting unit quaternion
 */
Quat normalize(const Quat& q) {
    const double mag = magnitude(q);
    const double x = q.x / mag;
    const double y = q.y / mag;
    const double z = q.z / mag;
    const double w = q.w / mag;
    return Quat(x, y, z, w);
}

} /* namespace Glycerin */

ostream& operator<<(ostream& stream, const Glycerin::Quat& q) {
    stream << "[";
    stream << q.x << ", ";
    stream << q.y << ", ";
    stream << q.z << ", ";
    stream << q.w;
    stream << "]";
    return stream;
}

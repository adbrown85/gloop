/*
 * Vec3.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <sstream>
#include <stdexcept>
#include "glycerin/math/Vec3.hpp"
using namespace std;
namespace Glycerin {

/**
 * Constructs a vector filled with all zeros.
 */
Vec3::Vec3() : x(0), y(0), z(0) {
    // pass
}

/**
 * Constructs a vector filled with a single value.
 *
 * @param d Value to store in each component
 */
Vec3::Vec3(double d) {
    // pass
}

/**
 * Constructs a vector from three values.
 *
 * @param x Value for X component
 * @param y Value for Y component
 * @param z Value for Z component
 */
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {
    // pass
}

/**
 * Makes a vector from a double array.
 *
 * @param arr Double array to make vector from
 */
Vec3::Vec3(double arr[3]) : x(arr[0]), y(arr[1]), z(arr[2]) {
    // pass
}

/**
 * Makes a vector from a float array.
 *
 * @param arr Float array to make vector from
 */
Vec3::Vec3(float arr[3]) : x(arr[0]), y(arr[1]), z(arr[2]) {
    // pass
}

/**
 * Computes the cross product of two vectors.
 *
 * @param u First vector
 * @param v Second vector
 * @return Vector perpendicular to the plane formed by two vectors
 */
Vec3 cross(const Vec3 &u, const Vec3 &v) {

    const double x = (u.y * v.z) - (u.z * v.y);
    const double y = (u.z * v.x) - (u.x * v.z);
    const double z = (u.x * v.y) - (u.y * v.x);

    return Vec3(x, y, z);
}

/**
 * Computes the dot product of two vectors.
 *
 * @param u First vector
 * @param v Second vector
 * @return Projection of one vector onto another
 */
double dot(const Vec3 &u, const Vec3 &v) {

    const double xx = u.x * v.x;
    const double yy = u.y * v.y;
    const double zz = u.z * v.z;

    return xx + yy + zz;
}

/**
 * Calculates the length of a vector.
 *
 * @param v Vector to calculate length of
 * @return Length of the vector
 */
double length(const Vec3 &v) {

    const double xx = v.x * v.x;
    const double yy = v.y * v.y;
    const double zz = v.z * v.z;

    return sqrt(xx + yy + zz);
}

/**
 * Finds the maximum component of a vector.
 *
 * @param v Vector to find maximum component of
 * @return Maximum component of vector
 */
double max(const Vec3 &v) {
    return std::max(std::max(v.x, v.y), v.z);
}

/**
 * Computes a component-wise maximum of two vectors.
 *
 * @param u First vector
 * @param v Second vector
 * @return Copy of resulting vector
 */
Vec3 max(const Vec3 &u, const Vec3 &v) {

    const double x = std::max(u.x, v.x);
    const double y = std::max(u.y, v.y);
    const double z = std::max(u.z, v.z);

    return Vec3(x, y, z);
}

/**
 * Finds the minimum component of a vector.
 *
 * @param v Vector to find minimum component of
 * @return Minimum component of vector
 */
double min(const Vec3 &v) {
    return std::min(std::min(v.x, v.y), v.z);
}

/**
 * Computes a component-wise minimum of two vectors.
 *
 * @param u First vector
 * @param v Second vector
 * @return Copy of resulting vector
 */
Vec3 min(const Vec3 &u, const Vec3 &v) {

    const double x = std::min(u.x, v.x);
    const double y = std::min(u.y, v.y);
    const double z = std::min(u.z, v.z);

    return Vec3(x, y, z);
}

/**
 * Computes a unit-length direction vector from a vector.
 *
 * @param v Vector to compute direction from
 * @return Copy of resulting vector
 */
Vec3 normalize(const Vec3 &v) {

    const double len = length(v);
    const double x = v.x / len;
    const double y = v.y / len;
    const double z = v.z / len;

    return Vec3(x, y, z);
}

/**
 * Returns a copy of a component in this vector by index.
 *
 * @param i Index of component
 * @return Copy of the component
 * @throw std::out_of_range if the index is out of bounds
 */
double Vec3::operator[](int i) const {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default:
        throw out_of_range("[Vec3] Index out of bounds!");
    }
}

/**
 * Accesses a component in this vector by index.
 *
 * @param i Index of component
 * @return Reference to the component
 * @throw std::out_of_range if the index is out of bounds
 */
double& Vec3::operator[](int i) {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default:
        throw out_of_range("[Vec3] Index out of bounds!");
    }
}

/**
 * Checks if another vector is equal to this one.
 *
 * @param v Vector to check
 * @return `true` if vectors are equal
 */
bool Vec3::operator==(const Vec3 &v) const {
    return (x == v.x) && (y == v.y) && (z == v.z);
}

/**
 * Checks if another vector is not equal to this one.
 *
 * @param v Vector to check
 * @return `true` if vectors are not equal
 */
bool Vec3::operator!=(const Vec3 &v) const {
    return (x != v.x) || (y != v.y) || (z != v.z);
}

/**
 * Returns a copy of the vector with the same sign.
 */
Vec3 Vec3::operator+() const {
    return Vec3(x, y, z);
}

/**
 * Returns the additive inverse of the vector.
 */
Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

/**
 * Adds a value to this vector, making a new vector.
 *
 * @param d Value to add
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator+(double d) const {
    return Vec3((x + d), (y + d), (z + d));
}

/**
 * Adds another vector to this vector, making a new vector.
 *
 * @param v Vector to add
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator+(const Vec3 &v) const {
    return Vec3((x + v.x), (y + v.y), (z + v.z));
}

/**
 * Adds a value to this vector, modifying this vector.
 *
 * @param d Value to add
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator+=(double d) {
    x += d;
    y += d;
    z += d;
    return *this;
}

/**
 * Adds another vector to this vector, modifying this vector.
 *
 * @param v Vector to add
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

/**
 * Subtracts a value from this vector, making a new vector.
 *
 * @param d Value to subtract
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator-(double d) const {
    return Vec3((x - d), (y - d), (z - d));
}

/**
 * Subtracts another vector from this vector, making a new vector.
 *
 * @param v Vector to subtract
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator-(const Vec3 &v) const {
    return Vec3((x - v.x), (y - v.y), (z - v.z));
}

/**
 * Subtracts a value from this vector, modifying this vector.
 *
 * @param d Value to subtract
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator-=(double d) {
    x -= d;
    y -= d;
    z -= d;
    return *this;
}

/**
 * Subtracts another vector from this vector, modifying this vector.
 *
 * @param v Vector to subtract
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator-=(const Vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

/**
 * Multiplies this vector by a value, making a new vector.
 *
 * @param d Value to multiply by
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator*(double d) const {
    return Vec3((x * d), (y * d), (z * d));
}

/**
 * Multiplies this vector by another vector, making a new vector.
 *
 * @param v Vector to multiply by
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator*(const Vec3 &v) const {
    return Vec3((x * v.x), (y * v.y), (z * v.z));
}

/**
 * Multiplies this vector by a value, modifying this vector.
 *
 * @param d Value to multiply by
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator*=(double d) {
    x *= d;
    y *= d;
    z *= d;
    return *this;
}

/**
 * Multiplies this vector by another vector, modifying this vector.
 *
 * @param v Vector to multiply by
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator*=(const Vec3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

/**
 * Divides this vector by a value, making a new vector.
 *
 * @param d Value to divide by
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator/(double d) const {
    return Vec3((x / d), (y / d), (z / d));
}

/**
 * Divides this vector by another vector, making a new vector.
 *
 * @param v Vector to divide by
 * @return Copy of resulting vector
 */
Vec3 Vec3::operator/(const Vec3 &v) const {
    return Vec3((x / v.x), (y / v.y), (z / v.z));
}

/**
 * Divides this vector by a value, modifying this vector.
 *
 * @param d Value to divide by
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator/=(double d) {
    x /= d;
    y /= d;
    z /= d;
    return *this;
}

/**
 * Divides this vector by another vector, modifying this vector.
 *
 * @param v Vector to divide by
 * @return Reference to this vector to support chaining
 */
Vec3& Vec3::operator/=(const Vec3& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

/**
 * Copies the vector's components to a double array.
 *
 * @param arr Double array to store values in
 */
void Vec3::toArray(double arr[3]) const {
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
}

/**
 * Copies the vector's components to a float array.
 *
 * @param arr Float array to store values in
 */
void Vec3::toArray(float arr[3]) const {
    arr[0] = (float) x;
    arr[1] = (float) y;
    arr[2] = (float) z;
}

/**
 * Returns a string represention of this vector.
 */
string Vec3::toString() const {

    stringstream stream;

    stream << (*this);
    return stream.str();
}

} /* namespace Glycerin */

/**
 * Appends a vector to a stream.
 *
 * @param out Stream to append to
 * @param u Vector to append
 * @return Reference to the stream
 */
ostream& operator<<(ostream &out, const Glycerin::Vec3 &u) {
    out << "[";
    out << u.x << ", " << u.y << ", " << u.z;
    out << "]";
    return out;
}

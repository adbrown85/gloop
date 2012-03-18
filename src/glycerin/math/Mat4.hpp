/*
 * Mat4.hpp
 *
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_MAT4_HPP
#define GLYCERIN_MAT4_HPP
#include "glycerin/common.h"
#include "glycerin/math/Mat3.hpp"
#include "glycerin/math/Vec4.hpp"
#include "glycerin/system/Exception.hpp"
namespace Glycerin {


/**
 * Four-by-four matrix for 3D graphics.
 *
 * @ingroup math
 */
class Mat4 {
public:
// Constants
    static const int ORDER = 4; ///< Number of rows and columns
    static const int ORDER_SQUARED = 16; ///< Number of elements in matrix
// Methods
    explicit Mat4();
    explicit Mat4(const double value);
    explicit Mat4(const double arr[4][4]);
    explicit Mat4(const float arr[4][4]);
    explicit Mat4(const double arr[16]);
    explicit Mat4(const float arr[16]);
    explicit Mat4(const Mat3& mat);
    Vec4 getColumn(const int j) const;
    Vec4 getRow(const int i) const;
    void toArray(double arr[4][4]) const;
    void toArray(float arr[4][4]) const;
    void toArray(double arr[16]) const;
    void toArray(float arr[16]) const;
    Mat3 toMat3() const;
    std::string toString() const;
// Operators
    double operator()(const int i, const int j) const;
    double& operator()(const int i, const int j);
    Mat4 operator*(const Mat4& mat) const;
    Vec4 operator*(const Vec4& vec) const;
// Friends
    friend Mat4 inverse(const Mat4& mat);
    friend Mat4 transpose(const Mat4& mat);
    friend class Mat4Test;
private:
// Types
    typedef std::pair<int,int> index_t;
    class MinorChart;
    class SignChart;
// Constants
    static const SignChart SIGN_CHART;
    static const MinorChart MINOR_CHART;
    static const int ORDER_MINUS_ONE = 3;
    static const int ORDER_MINUS_ONE_SQUARED = 9;
// Attributes
    double elements[4][4];
// Helpers
    double findMinor(const int row, const int col) const;
    static double findDeterminant(const double [3][3]);
};


/*
 * Chart containing indices for computing matrix of minors.
 */
class Mat4::MinorChart {
public:
// Methods
    explicit MinorChart();
    const index_t* operator()(const int i, const int j) const;
private:
// Attributes
    index_t indices[4][4][9];
// Helpers
    static void findIndices(index_t *idx, const int row, const int col);
};


/*
 * Chart containing signs for computing matrix of cofactors.
 */
class Mat4::SignChart {
public:
// Methods
    explicit SignChart();
    int operator()(const int i, const int j) const;
private:
// Attributes
    int signs[4][4];
};

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream &stream, const Glycerin::Mat4& mat);

#endif

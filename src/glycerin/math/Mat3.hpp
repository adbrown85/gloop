/*
 * Mat3.hpp
 *
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_MAT3_HPP
#define GLYCERIN_MAT3_HPP
#include <iostream>
#include "glycerin/common.h"
#include "glycerin/math/Vec3.hpp"
#include "glycerin/system/Exception.hpp"
namespace Glycerin {


/**
 * Three-by-three matrix for 3D graphics.
 *
 * @ingroup math
 */
class Mat3 {
public:
// Constants
    static const int ORDER = 3; ///< Number of rows and columns
    static const int ORDER_SQUARED = 9; ///< Number of elements in matrix
// Methods
    explicit Mat3();
    explicit Mat3(const double value);
    static Mat3 fromArrayInColumnMajor(const float arr[9]);
    static Mat3 fromArrayInColumnMajor(const double arr[9]);
    static Mat3 fromArrayInColumnMajor(const double arr[3][3]);
    static Mat3 fromArrayInColumnMajor(const float arr[3][3]);
    static Mat3 fromArrayInRowMajor(const float arr[9]);
    static Mat3 fromArrayInRowMajor(const double arr[9]);
    static Mat3 fromArrayInRowMajor(const float arr[3][3]);
    static Mat3 fromArrayInRowMajor(const double arr[3][3]);
    static Mat3 fromColumns(const Vec3& c1, const Vec3& c2, const Vec3& c3);
    static Mat3 fromRows(const Vec3& r1, const Vec3& r2, const Vec3& r3);
    Vec3 getColumn(const int j) const;
    Vec3 getRow(const int i) const;
    void toArrayInColumnMajor(double arr[3][3]) const;
    void toArrayInColumnMajor(float arr[3][3]) const;
    void toArrayInColumnMajor(double arr[9]) const;
    void toArrayInColumnMajor(float arr[9]) const;
    void toArrayInRowMajor(double arr[9]) const;
    void toArrayInRowMajor(float arr[9]) const;
    void toArrayInRowMajor(double arr[3][3]) const;
    void toArrayInRowMajor(float arr[3][3]) const;
    std::string toString() const;
// Operators
    const Vec3& operator[](int j) const;
    Vec3& operator[](int j);
    Mat3 operator*(const Mat3& mat) const;
    Vec3 operator*(const Vec3& vec) const;
// Friends
    friend Mat3 inverse(const Mat3& mat);
    friend Mat3 transpose(const Mat3& mat);
    friend class Mat3Test;
    friend class Mat4;
private:
// Types
    typedef std::pair<int,int> index_t;
    class SignChart;
    class MinorChart;
// Constants
    static const int ORDER_MINUS_ONE = 2;
    static const int ORDER_MINUS_ONE_SQUARED = 4;
    static const MinorChart MINOR_CHART;
    static const SignChart SIGN_CHART;
// Helpers
    static double findDeterminant(double arr[2][2]);
    double findMinor(const int i, const int j) const;
// Attributes
    Vec3 columns[3];
};


/*
 * Chart containing indices for computing matrix of minors.
 */
class Mat3::MinorChart {
public:
// Methods
    explicit MinorChart();
    const index_t* operator()(const int i, const int j) const;
private:
// Attributes
    index_t indices[ORDER][ORDER][ORDER_MINUS_ONE_SQUARED];
// Helpers
    static void findIndices(index_t* idx, const int row, const int col);
};


/*
 * Chart containing indices for computing matrix of cofactors.
 */
class Mat3::SignChart {
public:
// Methods
    explicit SignChart();
    int operator()(const int i, const int j) const;
private:
// Attributes
    int signs[ORDER][ORDER];
};

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream &stream, const Glycerin::Mat3& mat);
#endif

/*
 * Mat4.hpp
 *
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "glycerin/math/Mat4.hpp"
using namespace std;
namespace Glycerin {

// CONSTANTS
const Mat4::SignChart Mat4::SIGN_CHART;
const Mat4::MinorChart Mat4::MINOR_CHART;

// METHODS

/**
 * Constructs an empty matrix.
 */
Mat4::Mat4() {
    // pass
}

/**
 * Constructs a matrix with a value across the diagonal.
 *
 * @param value Value to copy to each element on diagonal
 */
Mat4::Mat4(const double value) {
    columns[0][0] = value;
    columns[1][1] = value;
    columns[2][2] = value;
    columns[3][3] = value;
}

/**
 * Constructs a matrix from a two-dimensional double array packed in column-major order.
 *
 * @param arr Two-dimensional double array to copy
 */
Mat4::Mat4(const double arr[4][4]) {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            columns[j][i] = arr[j][i];
        }
    }
}

/**
 * Constructs a matrix from a two-dimensional float array packed in column-major order.
 *
 * @param arr Two-dimensional float array to copy
 */
Mat4::Mat4(const float arr[4][4]) {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            columns[j][i] = arr[j][i];
        }
    }
}

/**
 * Constructs a matrix from a double array packed in column-major order.
 *
 * @param arr Double array packed in column-major order to copy
 */
Mat4::Mat4(const double arr[16]) {
    const double* ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            columns[j][i] = (*ptr);
            ++ptr;
        }
    }
}

/**
 * Constructs a matrix from a float array packed in column-major order.
 *
 * @param arr Float array packed in column-major order to copy
 */
Mat4::Mat4(const float arr[16]) {
    const float* ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            columns[j][i] = (*ptr);
            ++ptr;
        }
    }
}

/**
 * Constructs a matrix from a 3x3 matrix, filling in a one on the diagonal, and zeros elsewhere.
 *
 * @param mat 3x3 matrix to copy
 */
Mat4::Mat4(const Mat3& mat) {

    // Copy 3x3 matrix to upper 3x3
    for (int i = 0; i < Mat3::ORDER; ++i) {
        for (int j = 0; j < Mat3::ORDER; ++j) {
            columns[j][i] = mat[j][i];
        }
    }

    // Fill in a one on the diagonal
    columns[ORDER_MINUS_ONE][ORDER_MINUS_ONE] = 1;

    // Fill in zeros elsewhere
    for (int i = 0; i < ORDER_MINUS_ONE; ++i) {
        columns[i][ORDER_MINUS_ONE] = 0;
        columns[ORDER_MINUS_ONE][i] = 0;
    }
}

/**
 * Creates a matrix from a one-dimensional double array in column-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInColumnMajor(const double arr[16]) {
    Mat4 mat;
    const double* ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            mat[j][i] = (*ptr);
            ++ptr;
        }
    }
    return mat;
}

/**
 * Creates a matrix from a one-dimensional float array in column-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInColumnMajor(const float arr[16]) {
    Mat4 mat;
    const float* ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            mat[j][i] = (*ptr);
            ++ptr;
        }
    }
    return mat;
}

/**
 * Creates a matrix from a two-dimensional double array in column-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInColumnMajor(const double arr[4][4]) {
    Mat4 mat;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = arr[j][i];
        }
    }
    return mat;
}

/**
 * Creates a matrix from a two-dimensional float array in column-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInColumnMajor(const float arr[4][4]) {
    Mat4 mat;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = arr[j][i];
        }
    }
    return mat;
}

/**
 * Creates a matrix from a one-dimensional double array in row-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInRowMajor(const double arr[16]) {
    Mat4 mat;
    const double* ptr = arr;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = (*ptr);
            ++ptr;
        }
    }
    return mat;
}

/**
 * Creates a matrix from a one-dimensional float array in row-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInRowMajor(const float arr[16]) {
    Mat4 mat;
    const float* ptr = arr;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = (*ptr);
            ++ptr;
        }
    }
    return mat;
}

/**
 * Creates a matrix from a two-dimensional double array in row-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInRowMajor(const double arr[4][4]) {
    Mat4 mat;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = arr[i][j];
        }
    }
    return mat;
}

/**
 * Creates a matrix from a two-dimensional float array in row-major order.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat4 Mat4::fromArrayInRowMajor(const float arr[4][4]) {
    Mat4 mat;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = arr[i][j];
        }
    }
    return mat;
}

/**
 * Returns a column in the matrix.
 *
 * @param j Index of column to return
 * @return Copy of the column as a vector
 * @throws std::exception if index is not in [0 .. 3]
 */
Vec4 Mat4::getColumn(const int j) const {
    if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Column index out of bounds!");
    } else {
        return columns[j];
    }
}

/**
 * Returns a row in the matrix.
 *
 * @param i Index of row to return
 * @return Copy of the row as a vector
 * @throws std::exception if index is not in [0 .. 3]
 */
Vec4 Mat4::getRow(const int i) const {
    if (((unsigned int) i) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Row index out of bounds!");
    } else {
        const double x = columns[0][i];
        const double y = columns[1][i];
        const double z = columns[2][i];
        const double w = columns[3][i];
        return Vec4(x, y, z, w);
    }
}

/**
 * Copies the matrix into a two-dimensional double array packed in column-major order.
 *
 * @param arr Two-dimensional double array to copy to
 */
void Mat4::toArray(double arr[4][4]) const {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            arr[j][i] = columns[j][i];
        }
    }
}

/**
 * Copies the matrix into a two-dimensional float array packed in column-major order.
 *
 * @param arr Two-dimensional float array to copy to
 */
void Mat4::toArray(float arr[4][4]) const {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            arr[j][i] = (float) columns[j][i];
        }
    }
}

/**
 * Copies the matrix into a double array in column-major order.
 *
 * @param arr Double array to copy to in column-major order
 */
void Mat4::toArray(double arr[16]) const {
    double *ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            (*ptr) = columns[j][i];
            ++ptr;
        }
    }
}

/**
 * Copies the matrix into a float array in column-major order.
 *
 * @param arr Float array to copy to in column-major order
 */
void Mat4::toArray(float arr[16]) const {
    float *ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            (*ptr) = (float) columns[j][i];
            ++ptr;
        }
    }
}

/**
 * Creates a 3x3 matrix from the upper-left part of this matrix.
 *
 * @return 3x3 matrix containing same components as upper-left
 */
Mat3 Mat4::toMat3() const {
    Mat3 m;
    for (int i = 0; i < Mat3::ORDER; ++i) {
        for (int j = 0; j < Mat3::ORDER; ++j) {
            m[j][i] = columns[j][i];
        }
    }
    return m;
}

/**
 * Returns a string representation of the matrix.
 */
string Mat4::toString() const {
    stringstream stream;
    stream << (*this);
    return stream.str();
}

// OPERATORS

/**
 * Retrieves a constant reference to a column in the matrix.
 *
 * @param j Index of column, in the range [0 .. 3]
 * @return Constant reference to the column
 * @throws std::exception if index out of bounds
 */
const Vec4& Mat4::operator[](int j) const {
    if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Index out of bounds!");
    } else {
        return columns[j];
    }
}

/**
 * Retrieves a reference to a column in the matrix.
 *
 * @param j Index of column, in the range [0 .. 3]
 * @return Reference to the column
 * @throws std::exception if index out of bounds
 */
Vec4& Mat4::operator[](int j) {
    if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Index out of bounds!");
    } else {
        return columns[j];
    }
}

/**
 * Multiplies this matrix by another matrix.
 *
 * @param mat Matrix to multiply by
 * @return Copy of resulting matrix
 */
Mat4 Mat4::operator*(const Mat4& mat) const {

    double result[ORDER][ORDER];

    // Multiply rows of this matrix with columns of other matrix
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            result[j][i] = 0;
            for (int k = 0; k < ORDER; ++k) {
                result[j][i] += columns[k][i] * mat.columns[j][k];
            }
        }
    }
    return Mat4(result);
}

/**
 * Multiplies this matrix by a vector.
 *
 * @param vec Vector to multiply by
 * @return Copy of resulting vector
 */
Vec4 Mat4::operator*(const Vec4& vec) const {

    double arr[ORDER];

    // Multiply rows of matrix by column of vector
    for (int i = 0; i < ORDER; ++i) {
        arr[i] = 0.0;
        for (int k = 0; k < ORDER; ++k) {
            arr[i] += columns[k][i] * vec[k];
        }
    }
    return Vec4(arr[0], arr[1], arr[2], arr[3]);
}

// FRIENDS

/**
 * Computes the inverse of a matrix.
 *
 * @param mat Matrix to compute inverse of
 * @return Inverse of matrix
 */
Mat4 inverse(const Mat4& mat) {

    const int ORDER = Mat4::ORDER;

    // Find the matrix of minors
    double minors[ORDER][ORDER];
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            minors[j][i] = mat.findMinor(i, j);
        }
    }

    // Find the matrix of cofactors using minors
    double cofactors[ORDER][ORDER];
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            cofactors[j][i] = minors[j][i] * Mat4::SIGN_CHART(i, j);
        }
    }

    // Find determinant using first row of original matrix and cofactors
    double determinant = 0;
    for (int j = 0; j < ORDER; ++j) {
        determinant += mat.columns[j][0] * cofactors[j][0];
    }

    // Find adjoint by transposing matrix of cofactors
    double adjoint[ORDER][ORDER];
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            adjoint[j][i] = cofactors[i][j];
        }
    }

    // Find inverse by dividing adjoint by determinant
    double inverse[ORDER][ORDER];
    const double oneOverDeterminant = 1.0 / determinant;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            inverse[j][i] = adjoint[j][i] * oneOverDeterminant;
        }
    }

    // Return inverse as a Mat4
    return Mat4(inverse);
}

/**
 * Computes the transpose of a matrix.
 *
 * @param mat Matrix to compute transpose of
 * @return Transpose of matrix
 */
Mat4 transpose(const Mat4& mat) {

    const int ORDER = Mat4::ORDER;
    double transposed[ORDER][ORDER];

    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            transposed[j][i] = mat.columns[i][j];
        }
    }
    return Mat4(transposed);
}

// HELPERS

/**
 * Computes the determinant of a 3x3 matrix.
 *
 * Calculated by aei - afh - bdi + bfg + cdh - ceg, where:
 *
 * | a b c |
 * | d e f |
 * | g h i |
 *
 * a = mat[0][0]
 * b = mat[0][1]
 * c = mat[0][2]
 * d = mat[1][0]
 * e = mat[1][1]
 * f = mat[1][2]
 * g = mat[2][0]
 * h = mat[2][1]
 * i = mat[2][2]
 *
 * @param mat Matrix stored in a 3x3 array
 * @return Determinant of matrix
 */
double Mat4::findDeterminant(const double mat[3][3]) {

    const double aei = mat[0][0] * mat[1][1] * mat[2][2];
    const double afh = mat[0][0] * mat[1][2] * mat[2][1];
    const double bdi = mat[0][1] * mat[1][0] * mat[2][2];
    const double bfg = mat[0][1] * mat[1][2] * mat[2][0];
    const double cdh = mat[0][2] * mat[1][0] * mat[2][1];
    const double ceg = mat[0][2] * mat[1][1] * mat[2][0];

    return aei - afh - bdi + bfg + cdh - ceg;
}

/**
 * Computes the minor of an element.
 *
 * @param row Row of element, assumed in [0 .. 3]
 * @param col Column of element, assumed in [0 .. 3]
 * @return Minor of element at row and column
 */
double Mat4::findMinor(const int row, const int col) const {

    // Make a sub-matrix by removing the elements of row and column
    double arr[ORDER_MINUS_ONE][ORDER_MINUS_ONE];
    const index_t* idx = MINOR_CHART(row, col);
    for (int i = 0; i < ORDER_MINUS_ONE; ++i) {
        for (int j = 0; j < ORDER_MINUS_ONE; ++j) {
            arr[i][j] = columns[idx->second][idx->first];
            ++idx;
        }
    }

    // Calculate determinant of that sub-matrix
    return findDeterminant(arr);
}

// NESTED TYPES

/**
 * Constructs a chart defining the indices needed to create a matrix of minors.
 */
Mat4::MinorChart::MinorChart() {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            findIndices(indices[i][j], i, j);
        }
    }
}

/**
 * Computes the nine indices needed to calculate the minor for an element.
 *
 * @param idx Pointer to an array of nine indices to modify, assumed not NULL
 * @param row Row of element to compute indices for, assumed in [0 .. 3]
 * @param col Column of element to compute indices for, assumed in [0 .. 3]
 */
void Mat4::MinorChart::findIndices(index_t* idx, const int row, const int col) {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            if ((i != row) && (j != col)) {
                idx->first = i;
                idx->second = j;
                ++idx;
            }
        }
    }
}

/**
 * Returns a pointer to the nine indices needed to calculate the minor for an element.
 *
 * @param i Row of element, assumed in [0 .. 3]
 * @param j Column of element, assumed in [0 .. 3]
 * @return Pointer to array of nine indices for element
 */
const Mat4::index_t* Mat4::MinorChart::operator()(const int i, const int j) const {
    return indices[i][j];
}

/**
 * Constructs a sign chart.
 */
Mat4::SignChart::SignChart() {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            signs[i][j] = ((i + j) % 2) ? -1 : +1;
        }
    }
}

/**
 * Returns a copy of a value in the sign chart.
 *
 * @param i Row of value, assumed in [0 .. 3]
 * @param j Column of value, assumed in [0 .. 3]
 * @return Copy of value at location
 */
int Mat4::SignChart::operator()(const int i, const int j) const {
    return signs[i][j];
}

} /* namespace Glycerin */

ostream& operator<<(ostream &stream, const Glycerin::Mat4& mat) {
    stream << '[';
    stream << mat.getRow(0);
    for (int i = 1; i < Glycerin::Mat4::ORDER; ++i) {
        stream << ", " << mat.getRow(i);
    }
    stream << ']';
    return stream;
}

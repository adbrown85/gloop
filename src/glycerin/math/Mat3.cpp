/*
 * Mat3.cpp
 *
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "glycerin/math/Mat3.hpp"
using namespace std;
namespace Glycerin {

// CONSTANTS
const Mat3::MinorChart Mat3::MINOR_CHART;
const Mat3::SignChart Mat3::SIGN_CHART;

// METHODS

/**
 * Constructs an empty matrix.
 */
Mat3::Mat3() {
    // pass
}

/**
 * Constructs a matrix with a value across the diagonal.
 *
 * @param value Value to copy to each element on diagonal
 */
Mat3::Mat3(const double value) {
    columns[0][0] = value;
    columns[1][1] = value;
    columns[2][2] = value;
}

/**
 * Creates a matrix from a one-dimensional double array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInColumnMajor(const double arr[9]) {
    Mat3 mat;
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
 * Creates a matrix from a one-dimensional float array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInColumnMajor(const float arr[9]) {
    Mat3 mat;
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
 * Creates a matrix from a one-dimensional double array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInColumnMajor(const double arr[3][3]) {
    Mat3 mat;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            mat[j][i] = arr[j][i];
        }
    }
    return mat;
}

/**
 * Creates a matrix from a two-dimensional float array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInColumnMajor(const float arr[3][3]) {
    Mat3 mat;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            mat[j][i] = arr[j][i];
        }
    }
    return mat;
}

/**
 * Creates a matrix from a one-dimensional double array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInRowMajor(const double arr[9]) {
    Mat3 mat;
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
 * Creates a matrix from a one-dimensional float array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInRowMajor(const float arr[9]) {
    Mat3 mat;
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
 * Creates a matrix from a two-dimensional double array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInRowMajor(const double arr[3][3]) {
    Mat3 mat;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat[j][i] = arr[i][j];
        }
    }
    return mat;
}

/**
 * Creates a matrix from a two-dimensional float array.
 *
 * @param arr Array to copy
 * @return Matrix with same values as array
 */
Mat3 Mat3::fromArrayInRowMajor(const float arr[3][3]) {
    Mat3 mat;
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
 * @throws std::exception if index is not in [0 .. 2]
 */
Vec3 Mat3::getColumn(const int j) const {
    if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat3] Column index out of bounds!");
    } else {
        return columns[j];
    }
}

/**
 * Returns a row in the matrix.
 *
 * @param i Index of row to return
 * @return Copy of the row as a vector
 * @throws std::exception if index is not in [0 .. 2]
 */
Vec3 Mat3::getRow(const int i) const {
    if (((unsigned int) i) > ORDER_MINUS_ONE) {
        throw Exception("[Mat3] Row index out of bounds!");
    } else {
        const double x = columns[0][i];
        const double y = columns[1][i];
        const double z = columns[2][i];
        return Vec3(x, y, z);
    }
}

/**
 * Copies the matrix into a two-dimensional double array packed in column-major order.
 *
 * @param arr Two-dimensional double array to copy to
 */
void Mat3::toArray(double arr[3][3]) const {
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
void Mat3::toArray(float arr[3][3]) const {
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
void Mat3::toArray(double arr[9]) const {
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
void Mat3::toArray(float arr[9]) const {
    float *ptr = arr;
    for (int j = 0; j < ORDER; ++j) {
        for (int i = 0; i < ORDER; ++i) {
            (*ptr) = (float) columns[j][i];
            ++ptr;
        }
    }
}

/**
 * Returns a string representation of the matrix.
 */
string Mat3::toString() const {
    stringstream stream;
    stream << (*this);
    return stream.str();
}

// OPERATORS

/**
 * Multiplies this matrix by another matrix.
 *
 * @param mat Matrix to multiply by
 * @return Copy of resulting matrix
 */
Mat3 Mat3::operator*(const Mat3& mat) const {

    double result[ORDER][ORDER];

    // Multiply rows of this matrix with columns of other matrix
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            result[j][i] = 0.0;
            for (int k = 0; k < ORDER; ++k) {
                result[j][i] += columns[k][i] * mat.columns[j][k];
            }
        }
    }
    return Mat3::fromArrayInColumnMajor(result);
}

/**
 * Multiplies this matrix by a vector.
 *
 * @param vec Vector to multiply by
 * @return Copy of resulting vector
 */
Vec3 Mat3::operator*(const Vec3& vec) const {

    double arr[ORDER];

    // Multiply rows of matrix by column of vector
    for (int i = 0; i < ORDER; ++i) {
        arr[i] = 0.0;
        for (int k = 0; k < ORDER; ++k) {
            arr[i] += columns[k][i] * vec[k];
        }
    }
    return Vec3(arr[0], arr[1], arr[2]);
}

/**
 * Retrieves a constant reference to a column in the matrix.
 *
 * @param j Index of column, in the range [0 .. 2]
 * @return Constant reference to the column
 * @throws std::exception if index out of bounds
 */
const Vec3& Mat3::operator[](int j) const {
    if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat3] Index out of bounds!");
    } else {
        return columns[j];
    }
}

/**
 * Retrieves a reference to a column in the matrix.
 *
 * @param j Index of column, in the range [0 .. 2]
 * @return Reference to the column
 * @throws std::exception if index out of bounds
 */
Vec3& Mat3::operator[](int j) {
    if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat3] Index out of bounds!");
    } else {
        return columns[j];
    }
}

// FRIENDS

/**
 * Computes the inverse of a matrix.
 *
 * @param mat Matrix to compute inverse of
 * @return Inverse of matrix
 */
Mat3 inverse(const Mat3& mat) {

    const int ORDER = Mat3::ORDER;

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
            cofactors[j][i] = minors[j][i] * Mat3::SIGN_CHART(i, j);
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

    // Return inverse as a Mat3
    return Mat3::fromArrayInColumnMajor(inverse);
}

/**
 * Computes the transpose of a matrix.
 *
 * @param mat Matrix to compute transpose of
 * @return Transpose of matrix
 */
Mat3 transpose(const Mat3& mat) {

    const int ORDER = Mat3::ORDER;
    double transposed[ORDER][ORDER];

    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            transposed[j][i] = mat.columns[i][j];
        }
    }
    return Mat3::fromArrayInColumnMajor(transposed);
}

// HELPERS

/**
 * Computes the determinant of a 2x2 matrix.
 *
 * Calculated by ad - cb, where:
 *
 * | a b |
 * | c b |
 *
 * a = arr[0][0]
 * b = arr[0][1]
 * c = arr[1][0]
 * d = arr[1][1]
 *
 * @param arr Matrix stored in a 2x2 array
 * @return Determinant of matrix
 */
double Mat3::findDeterminant(double arr[2][2]) {
    const double ad = arr[0][0] * arr[1][1];
    const double cb = arr[1][0] * arr[0][1];
    return ad - cb;
}

/**
 * Computes the minor of an element.
 *
 * @param row Row of element, assumed in [0 .. 2]
 * @param col Column of element, assumed in [0 .. 2]
 * @return Minor of element at row and column
 */
double Mat3::findMinor(const int row, const int col) const {

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
Mat3::MinorChart::MinorChart() {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            findIndices(indices[i][j], i, j);
        }
    }
}

/**
 * Returns a pointer to the four indices needed to calculate the minor for an element.
 *
 * @param i Row of element, assumed in [0 .. 2]
 * @param j Column of element, assumed in [0 .. 2]
 * @return Pointer to array of four indices for element
 */
const Mat3::index_t* Mat3::MinorChart::operator()(const int i, const int j) const {
    return indices[i][j];
}

/**
 * Computes the four indices needed to calculate the minor for an element.
 *
 * @param idx Pointer to an array of four indices to modify, assumed not NULL
 * @param row Row of element to compute indices for, assumed in [0 .. 3]
 * @param col Column of element to compute indices for, assumed in [0 .. 3]
 */
void Mat3::MinorChart::findIndices(index_t* idx, const int row, const int col) {
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
 * Constructs a sign chart.
 */
Mat3::SignChart::SignChart() {
    int sign = -1;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            sign *= -1;
            signs[i][j] = sign;
        }
    }
}

/**
 * Returns a copy of a value in the sign chart.
 *
 * @param i Row of value, assumed in [0 .. 2]
 * @param j Column of value, assumed in [0 .. 2]
 * @return Copy of value at location
 */
int Mat3::SignChart::operator()(const int i, const int j) const {
    return signs[i][j];
}

} /* namespace Glycerin */

ostream& operator<<(ostream &stream, const Glycerin::Mat3& mat) {
    stream << '[';
    stream << mat.getRow(0);
    for (int i = 1; i < Glycerin::Mat3::ORDER; ++i) {
        stream << ", " << mat.getRow(i);
    }
    stream << ']';
    return stream;
}

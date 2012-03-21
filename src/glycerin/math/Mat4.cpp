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
    elements[0][0] = 0.0;
    elements[0][1] = 0.0;
    elements[0][2] = 0.0;
    elements[0][3] = 0.0;
    elements[1][0] = 0.0;
    elements[1][1] = 0.0;
    elements[1][2] = 0.0;
    elements[1][3] = 0.0;
    elements[2][0] = 0.0;
    elements[2][1] = 0.0;
    elements[2][2] = 0.0;
    elements[2][3] = 0.0;
    elements[3][0] = 0.0;
    elements[3][1] = 0.0;
    elements[3][2] = 0.0;
    elements[3][3] = 0.0;
}

/**
 * Constructs a matrix with a value across the diagonal.
 *
 * @param value Value to copy to each element on diagonal
 */
Mat4::Mat4(const double value) {
    elements[0][0] = value;
    elements[0][1] = 0.0;
    elements[0][2] = 0.0;
    elements[0][3] = 0.0;
    elements[1][0] = 0.0;
    elements[1][1] = value;
    elements[1][2] = 0.0;
    elements[1][3] = 0.0;
    elements[2][0] = 0.0;
    elements[2][1] = 0.0;
    elements[2][2] = value;
    elements[2][3] = 0.0;
    elements[3][0] = 0.0;
    elements[3][1] = 0.0;
    elements[3][2] = 0.0;
    elements[3][3] = value;
}

/**
 * Constructs a matrix from a two-dimensional double array.
 *
 * @param arr Two-dimensional double array to copy
 */
Mat4::Mat4(const double arr[4][4]) {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            elements[i][j] = arr[i][j];
        }
    }
}

/**
 * Constructs a matrix from a two-dimensional float array.
 *
 * @param arr Two-dimensional float array to copy
 */
Mat4::Mat4(const float arr[4][4]) {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            elements[i][j] = arr[i][j];
        }
    }
}

/**
 * Constructs a matrix from a double array packed in row-major order.
 *
 * @param arr Double array packed in row-major order to copy
 */
Mat4::Mat4(const double arr[16]) {
    const double* ptr = arr;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            elements[i][j] = (*ptr);
            ++ptr;
        }
    }
}

/**
 * Constructs a matrix from a float array packed in row-major order.
 *
 * @param arr Float array packed in row-major order to copy
 */
Mat4::Mat4(const float arr[16]) {
    const float* ptr = arr;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            elements[i][j] = (*ptr);
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
            elements[i][j] = mat.elements[i][j];
        }
    }

    // Fill in a one on the diagonal
    elements[ORDER_MINUS_ONE][ORDER_MINUS_ONE] = 1;

    // Fill in zeros elsewhere
    for (int i = 0; i < ORDER_MINUS_ONE; ++i) {
        elements[i][ORDER_MINUS_ONE] = 0;
        elements[ORDER_MINUS_ONE][i] = 0;
    }
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
        const double x = elements[0][j];
        const double y = elements[1][j];
        const double z = elements[2][j];
        const double w = elements[3][j];
        return Vec4(x, y, z, w);
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
        const double x = elements[i][0];
        const double y = elements[i][1];
        const double z = elements[i][2];
        const double w = elements[i][3];
        return Vec4(x, y, z, w);
    }
}

/**
 * Copies the matrix into a two-dimensional double array.
 *
 * @param arr Two-dimensional double array to copy to
 */
void Mat4::toArray(double arr[4][4]) const {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            arr[i][j] = elements[i][j];
        }
    }
}

/**
 * Copies the matrix into a two-dimensional float array.
 *
 * @param arr Two-dimensional float array to copy to
 */
void Mat4::toArray(float arr[4][4]) const {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            arr[i][j] = (float) elements[i][j];
        }
    }
}

/**
 * Copies the matrix into a double array in row-major order.
 *
 * @param arr Double array to copy to in row-major order
 */
void Mat4::toArray(double arr[16]) const {
    double *ptr = arr;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            (*ptr) = elements[i][j];
            ++ptr;
        }
    }
}

/**
 * Copies the matrix into a float array in row-major order.
 *
 * @param arr Float array to copy to in row-major order
 */
void Mat4::toArray(float arr[16]) const {
    float *ptr = arr;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            (*ptr) = (float) elements[i][j];
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
            m.elements[i][j] = elements[i][j];
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
 * Returns a copy of an element in the matrix.
 *
 * @param i Row of element
 * @param j Column of element
 * @return Copy of element at row and column
 * @throw std::exception if either index is out of bounds
 */
double Mat4::operator()(const int i, const int j) const {
    if (((unsigned int) i) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Index i is out of bounds!");
    } else if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Index j is out of bounds!");
    } else {
        return elements[i][j];
    }
}

/**
 * Returns a reference to an element in the matrix.
 *
 * @param i Row of element
 * @param j Column of element
 * @return Reference to element at row and column
 * @throw std::exception if either index is out of bounds
 */
double& Mat4::operator()(const int i, const int j) {
    if (((unsigned int) i) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Index i is out of bounds!");
    } else if (((unsigned int) j) > ORDER_MINUS_ONE) {
        throw Exception("[Mat4] Index j is out of bounds!");
    } else {
        return elements[i][j];
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
            result[i][j] = 0;
            for (int k = 0; k < ORDER; ++k) {
                result[i][j] += elements[i][k] * mat.elements[k][j];
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
            arr[i] += elements[i][k] * vec[k];
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
            minors[i][j] = mat.findMinor(i, j);
        }
    }

    // Find the matrix of cofactors using minors
    double cofactors[ORDER][ORDER];
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            cofactors[i][j] = minors[i][j] * Mat4::SIGN_CHART(i, j);
        }
    }

    // Find determinant using first row of original matrix and cofactors
    double determinant = 0;
    for (int j = 0; j < ORDER; ++j) {
        determinant += mat.elements[0][j] * cofactors[0][j];
    }

    // Find adjoint by transposing matrix of cofactors
    double adjoint[ORDER][ORDER];
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            adjoint[i][j] = cofactors[j][i];
        }
    }

    // Find inverse by dividing adjoint by determinant
    double inverse[ORDER][ORDER];
    const double oneOverDeterminant = 1.0 / determinant;
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            inverse[i][j] = adjoint[i][j] * oneOverDeterminant;
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
            transposed[i][j] = mat.elements[j][i];
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
            arr[i][j] = elements[idx->first][idx->second];
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

//
// Created by William DeVore on 3/20/16.
//

#ifndef RANGERBETA_MATRIX_H
#define RANGERBETA_MATRIX_H


#include "math.h"
#include "vector3.h"

namespace Ranger {
    // Forward template declaration
    template<typename T>
    class Vector3;

    template<typename T>
    class Matrix4 final {
    public:
        /** XX: Typically the unrotated X component for scaling, also the cosine of the angle when rotated on the Y and/or Z axis. On
         * Vector3 multiplication this value is multiplied with the source X component and added to the target X component. */
        static const int M00 = 0;
        /** XY: Typically the negative sine of the angle when rotated on the Z axis. On Vector3 multiplication this value is multiplied
         * with the source Y component and added to the target X component. */
        static const int M01 = 4;
        /** XZ: Typically the sine of the angle when rotated on the Y axis. On Vector3 multiplication this value is multiplied with the
         * source Z component and added to the target X component. */
        static const int M02 = 8;
        /** XW: Typically the translation of the X component. On Vector3 multiplication this value is added to the target X component. */
        static const int M03 = 12;
        /** YX: Typically the sine of the angle when rotated on the Z axis. On Vector3 multiplication this value is multiplied with the
         * source X component and added to the target Y component. */
        static const int M10 = 1;
        /** YY: Typically the unrotated Y component for scaling, also the cosine of the angle when rotated on the X and/or Z axis. On
         * Vector3 multiplication this value is multiplied with the source Y component and added to the target Y component. */
        static const int M11 = 5;
        /** YZ: Typically the negative sine of the angle when rotated on the X axis. On Vector3 multiplication this value is multiplied
         * with the source Z component and added to the target Y component. */
        static const int M12 = 9;
        /** YW: Typically the translation of the Y component. On Vector3 multiplication this value is added to the target Y component. */
        static const int M13 = 13;
        /** ZX: Typically the negative sine of the angle when rotated on the Y axis. On Vector3 multiplication this value is multiplied
         * with the source X component and added to the target Z component. */
        static const int M20 = 2;
        /** ZY: Typical the sine of the angle when rotated on the X axis. On Vector3 multiplication this value is multiplied with the
         * source Y component and added to the target Z component. */
        static const int M21 = 6;
        /** ZZ: Typically the unrotated Z component for scaling, also the cosine of the angle when rotated on the X and/or Y axis. On
         * Vector3 multiplication this value is multiplied with the source Z component and added to the target Z component. */
        static const int M22 = 10;
        /** ZW: Typically the translation of the Z component. On Vector3 multiplication this value is added to the target Z component. */
        static const int M23 = 14;
        /** WX: Typically the value zero. On Vector3 multiplication this value is ignored. */
        static const int M30 = 3;
        /** WY: Typically the value zero. On Vector3 multiplication this value is ignored. */
        static const int M31 = 7;
        /** WZ: Typically the value zero. On Vector3 multiplication this value is ignored. */
        static const int M32 = 11;
        /** WW: Typically the value one. On Vector3 multiplication this value is ignored. */
        static const int M33 = 15;


        Matrix4() {
            setToIdentity();
        }

        /** Constructs a matrix from the given matrix.
         *
         * @param matrix The matrix to copy. (This matrix is not modified) */
        Matrix4(const Matrix4<T> &matrix) {
            set(matrix);
        }

        Matrix4<T> clone() {
            Matrix4<T> c;
            return c.set(val);
        }

        /** Sets the matrix to the given matrix.
         *
         * @param matrix The matrix that is to be copied. (The given matrix is not modified)
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &set(const Matrix4<T> &matrix) {
            return set(matrix.val);
        }

        /** Sets the matrix to the given matrix as a T array. The T array must have at least 16 elements; the first 16 will be
         * copied.
         *
         * @param values The matrix, in T form, that is to be copied. Remember that this matrix is in <a
         *           href="http://en.wikipedia.org/wiki/Row-major_order">column major</a> order.
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &set(const T values[]) {
            val[M00] = values[M00];
            val[M01] = values[M01];
            val[M02] = values[M02];
            val[M03] = values[M03];

            val[M10] = values[M10];
            val[M11] = values[M11];
            val[M12] = values[M12];
            val[M13] = values[M13];

            val[M20] = values[M20];
            val[M21] = values[M21];
            val[M22] = values[M22];
            val[M23] = values[M23];

            val[M30] = values[M30];
            val[M31] = values[M31];
            val[M32] = values[M32];
            val[M33] = values[M33];
            return *this;
        }

        /** Sets the four columns of the matrix which correspond to the x-, y- and z-axis of the vector space this matrix creates as
         * well as the 4th column representing the translation of any point that is multiplied by this matrix.
         *
         * @param xAxis The x-axis.
         * @param yAxis The y-axis.
         * @param zAxis The z-axis.
         * @param pos The translation vector. */
        Matrix4<T> &set(const Vector3<T> &xAxis, const Vector3<T> &yAxis, const Vector3<T> &zAxis,
                        const Vector3<T> &pos) {
            val[M00] = xAxis.x;
            val[M01] = xAxis.y;
            val[M02] = xAxis.z;
            val[M10] = yAxis.x;
            val[M11] = yAxis.y;
            val[M12] = yAxis.z;
            val[M20] = zAxis.x;
            val[M21] = zAxis.y;
            val[M22] = zAxis.z;
            val[M03] = pos.x;
            val[M13] = pos.y;
            val[M23] = pos.z;
            val[M30] = 0;
            val[M31] = 0;
            val[M32] = 0;
            val[M33] = 1;
            return *this;
        }

        /** Adds a translational component to the matrix in the 4th column. The other columns are untouched.
         *
         * @param vector The translation vector to add to the current matrix. (This vector is not modified)
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &translate(const Vector3<T> &vector) {
            val[M03] += vector.x;
            val[M13] += vector.y;
            val[M23] += vector.z;
            return *this;
        }

        /** Adds a translational component to the matrix in the 4th column. The other columns are untouched.
         *
         * @param x The x-component of the translation vector.
         * @param y The y-component of the translation vector.
         * @param z The z-component of the translation vector.
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &translate(T x, T y, T z) {
            val[M03] += x;
            val[M13] += y;
            val[M23] += z;
            return *this;
        }

        /** Postmultiplies this matrix with the given matrix, storing the result in this matrix. For example:
         *
         * <pre>
         * A.mul(B) results in A := AB.
         * </pre>
         *
         * @param matrix The other matrix to multiply by.
         * @return This matrix for the purpose of chaining operations together. */
        Matrix4<T> &mul(const Matrix4<T> &matrix) {
            mul(val, matrix.val);
            return *this;
        }

        /** Premultiplies this matrix with the given matrix, storing the result in this matrix. For example:
         *
         * <pre>
         * A.mulLeft(B) results in A := BA.
         * </pre>
         *
         * @param matrix The other matrix to multiply by.
         * @return This matrix for the purpose of chaining operations together. */
        Matrix4<T> &mulLeft(const Matrix4<T> &matrix) {
            mul(matrix.val, val, _tmp);

            // Place results in A
            val[M00] = _tmp[M00];
            val[M01] = _tmp[M01];
            val[M02] = _tmp[M02];
            val[M03] = _tmp[M03];

            val[M10] = _tmp[M10];
            val[M11] = _tmp[M11];
            val[M12] = _tmp[M12];
            val[M13] = _tmp[M13];

            val[M20] = _tmp[M20];
            val[M21] = _tmp[M21];
            val[M22] = _tmp[M22];
            val[M23] = _tmp[M23];

            val[M30] = _tmp[M30];
            val[M31] = _tmp[M31];
            val[M32] = _tmp[M32];
            val[M33] = _tmp[M33];

            return *this;
        }

        /** Transposes the matrix.
         *
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &transpose() {
            _tmp[M00] = val[M00];
            _tmp[M01] = val[M10];
            _tmp[M02] = val[M20];
            _tmp[M03] = val[M30];
            _tmp[M10] = val[M01];
            _tmp[M11] = val[M11];
            _tmp[M12] = val[M21];
            _tmp[M13] = val[M31];
            _tmp[M20] = val[M02];
            _tmp[M21] = val[M12];
            _tmp[M22] = val[M22];
            _tmp[M23] = val[M32];
            _tmp[M30] = val[M03];
            _tmp[M31] = val[M13];
            _tmp[M32] = val[M23];
            _tmp[M33] = val[M33];
            return set(_tmp);
        }

        /** Sets the matrix to an identity matrix.
         *
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToIdentity() {
            val[M00] = 1;
            val[M01] = 0;
            val[M02] = 0;
            val[M03] = 0;
            val[M10] = 0;
            val[M11] = 1;
            val[M12] = 0;
            val[M13] = 0;
            val[M20] = 0;
            val[M21] = 0;
            val[M22] = 1;
            val[M23] = 0;
            val[M30] = 0;
            val[M31] = 0;
            val[M32] = 0;
            val[M33] = 1;
            return *this;
        }

        /** Inverts the matrix. Stores the result in this matrix.
         *
         * @return This matrix for the purpose of chaining methods together.
         * @throws RuntimeException if the matrix is singular (not invertible) */
        Matrix4<T> &invert() {
            T l_det = val[M30] * val[M21] * val[M12] * val[M03] - val[M20] * val[M31] * val[M12] * val[M03] -
                      val[M30] * val[M11]
                      * val[M22] * val[M03] + val[M10] * val[M31] * val[M22] * val[M03] +
                      val[M20] * val[M11] * val[M32] * val[M03] - val[M10]
                                                                  * val[M21] * val[M32] * val[M03] -
                      val[M30] * val[M21] * val[M02] * val[M13] + val[M20] * val[M31] * val[M02] * val[M13]
                      + val[M30] * val[M01] * val[M22] * val[M13] - val[M00] * val[M31] * val[M22] * val[M13] -
                      val[M20] * val[M01] * val[M32]
                      * val[M13] + val[M00] * val[M21] * val[M32] * val[M13] +
                      val[M30] * val[M11] * val[M02] * val[M23] - val[M10] * val[M31]
                                                                  * val[M02] * val[M23] -
                      val[M30] * val[M01] * val[M12] * val[M23] + val[M00] * val[M31] * val[M12] * val[M23] +
                      val[M10]
                      * val[M01] * val[M32] * val[M23] - val[M00] * val[M11] * val[M32] * val[M23] -
                      val[M20] * val[M11] * val[M02] * val[M33]
                      + val[M10] * val[M21] * val[M02] * val[M33] + val[M20] * val[M01] * val[M12] * val[M33] -
                      val[M00] * val[M21] * val[M12]
                      * val[M33] - val[M10] * val[M01] * val[M22] * val[M33] +
                      val[M00] * val[M11] * val[M22] * val[M33];

            if (l_det == 0.0f) throw std::domain_error("non-invertible matrix");

            T inv_det = 1.0f / l_det;

            _tmp[M00] =
                    val[M12] * val[M23] * val[M31] - val[M13] * val[M22] * val[M31] + val[M13] * val[M21] * val[M32] -
                    val[M11]
                    * val[M23] * val[M32] - val[M12] * val[M21] * val[M33] + val[M11] * val[M22] * val[M33];
            _tmp[M01] =
                    val[M03] * val[M22] * val[M31] - val[M02] * val[M23] * val[M31] - val[M03] * val[M21] * val[M32] +
                    val[M01]
                    * val[M23] * val[M32] + val[M02] * val[M21] * val[M33] - val[M01] * val[M22] * val[M33];
            _tmp[M02] =
                    val[M02] * val[M13] * val[M31] - val[M03] * val[M12] * val[M31] + val[M03] * val[M11] * val[M32] -
                    val[M01]
                    * val[M13] * val[M32] - val[M02] * val[M11] * val[M33] + val[M01] * val[M12] * val[M33];
            _tmp[M03] =
                    val[M03] * val[M12] * val[M21] - val[M02] * val[M13] * val[M21] - val[M03] * val[M11] * val[M22] +
                    val[M01]
                    * val[M13] * val[M22] + val[M02] * val[M11] * val[M23] - val[M01] * val[M12] * val[M23];
            _tmp[M10] =
                    val[M13] * val[M22] * val[M30] - val[M12] * val[M23] * val[M30] - val[M13] * val[M20] * val[M32] +
                    val[M10]
                    * val[M23] * val[M32] + val[M12] * val[M20] * val[M33] - val[M10] * val[M22] * val[M33];
            _tmp[M11] =
                    val[M02] * val[M23] * val[M30] - val[M03] * val[M22] * val[M30] + val[M03] * val[M20] * val[M32] -
                    val[M00]
                    * val[M23] * val[M32] - val[M02] * val[M20] * val[M33] + val[M00] * val[M22] * val[M33];
            _tmp[M12] =
                    val[M03] * val[M12] * val[M30] - val[M02] * val[M13] * val[M30] - val[M03] * val[M10] * val[M32] +
                    val[M00]
                    * val[M13] * val[M32] + val[M02] * val[M10] * val[M33] - val[M00] * val[M12] * val[M33];
            _tmp[M13] =
                    val[M02] * val[M13] * val[M20] - val[M03] * val[M12] * val[M20] + val[M03] * val[M10] * val[M22] -
                    val[M00]
                    * val[M13] * val[M22] - val[M02] * val[M10] * val[M23] + val[M00] * val[M12] * val[M23];
            _tmp[M20] =
                    val[M11] * val[M23] * val[M30] - val[M13] * val[M21] * val[M30] + val[M13] * val[M20] * val[M31] -
                    val[M10]
                    * val[M23] * val[M31] - val[M11] * val[M20] * val[M33] + val[M10] * val[M21] * val[M33];
            _tmp[M21] =
                    val[M03] * val[M21] * val[M30] - val[M01] * val[M23] * val[M30] - val[M03] * val[M20] * val[M31] +
                    val[M00]
                    * val[M23] * val[M31] + val[M01] * val[M20] * val[M33] - val[M00] * val[M21] * val[M33];
            _tmp[M22] =
                    val[M01] * val[M13] * val[M30] - val[M03] * val[M11] * val[M30] + val[M03] * val[M10] * val[M31] -
                    val[M00]
                    * val[M13] * val[M31] - val[M01] * val[M10] * val[M33] + val[M00] * val[M11] * val[M33];
            _tmp[M23] =
                    val[M03] * val[M11] * val[M20] - val[M01] * val[M13] * val[M20] - val[M03] * val[M10] * val[M21] +
                    val[M00]
                    * val[M13] * val[M21] + val[M01] * val[M10] * val[M23] - val[M00] * val[M11] * val[M23];
            _tmp[M30] =
                    val[M12] * val[M21] * val[M30] - val[M11] * val[M22] * val[M30] - val[M12] * val[M20] * val[M31] +
                    val[M10]
                    * val[M22] * val[M31] + val[M11] * val[M20] * val[M32] - val[M10] * val[M21] * val[M32];
            _tmp[M31] =
                    val[M01] * val[M22] * val[M30] - val[M02] * val[M21] * val[M30] + val[M02] * val[M20] * val[M31] -
                    val[M00]
                    * val[M22] * val[M31] - val[M01] * val[M20] * val[M32] + val[M00] * val[M21] * val[M32];
            _tmp[M32] =
                    val[M02] * val[M11] * val[M30] - val[M01] * val[M12] * val[M30] - val[M02] * val[M10] * val[M31] +
                    val[M00]
                    * val[M12] * val[M31] + val[M01] * val[M10] * val[M32] - val[M00] * val[M11] * val[M32];
            _tmp[M33] =
                    val[M01] * val[M12] * val[M20] - val[M02] * val[M11] * val[M20] + val[M02] * val[M10] * val[M21] -
                    val[M00]
                    * val[M12] * val[M21] - val[M01] * val[M10] * val[M22] + val[M00] * val[M11] * val[M22];
            val[M00] = _tmp[M00] * inv_det;
            val[M01] = _tmp[M01] * inv_det;
            val[M02] = _tmp[M02] * inv_det;
            val[M03] = _tmp[M03] * inv_det;
            val[M10] = _tmp[M10] * inv_det;
            val[M11] = _tmp[M11] * inv_det;
            val[M12] = _tmp[M12] * inv_det;
            val[M13] = _tmp[M13] * inv_det;
            val[M20] = _tmp[M20] * inv_det;
            val[M21] = _tmp[M21] * inv_det;
            val[M22] = _tmp[M22] * inv_det;
            val[M23] = _tmp[M23] * inv_det;
            val[M30] = _tmp[M30] * inv_det;
            val[M31] = _tmp[M31] * inv_det;
            val[M32] = _tmp[M32] * inv_det;
            val[M33] = _tmp[M33] * inv_det;
            return *this;
        }

        /** @return The determinant of this matrix */
        T determinant() {
            return val[M30] * val[M21] * val[M12] * val[M03] - val[M20] * val[M31] * val[M12] * val[M03] -
                   val[M30] * val[M11]
                   * val[M22] * val[M03] + val[M10] * val[M31] * val[M22] * val[M03] +
                   val[M20] * val[M11] * val[M32] * val[M03] - val[M10]
                                                               * val[M21] * val[M32] * val[M03] -
                   val[M30] * val[M21] * val[M02] * val[M13] + val[M20] * val[M31] * val[M02] * val[M13]
                   + val[M30] * val[M01] * val[M22] * val[M13] - val[M00] * val[M31] * val[M22] * val[M13] -
                   val[M20] * val[M01] * val[M32]
                   * val[M13] + val[M00] * val[M21] * val[M32] * val[M13] + val[M30] * val[M11] * val[M02] * val[M23] -
                   val[M10] * val[M31]
                   * val[M02] * val[M23] - val[M30] * val[M01] * val[M12] * val[M23] +
                   val[M00] * val[M31] * val[M12] * val[M23] + val[M10]
                                                               * val[M01] * val[M32] * val[M23] -
                   val[M00] * val[M11] * val[M32] * val[M23] - val[M20] * val[M11] * val[M02] * val[M33]
                   + val[M10] * val[M21] * val[M02] * val[M33] + val[M20] * val[M01] * val[M12] * val[M33] -
                   val[M00] * val[M21] * val[M12]
                   * val[M33] - val[M10] * val[M01] * val[M22] * val[M33] + val[M00] * val[M11] * val[M22] * val[M33];
        }

        /** @return The determinant of the 3x3 upper left matrix */
        T det3x3() {
            return val[M00] * val[M11] * val[M22] + val[M01] * val[M12] * val[M20] + val[M02] * val[M10] * val[M21] -
                   val[M00]
                   * val[M12] * val[M21] - val[M01] * val[M10] * val[M22] - val[M02] * val[M11] * val[M20];
        }

        /// O = A * B
        void mul(const T mata[], const T matb[], T mato[]) {
            mato[M00] = mata[M00] * matb[M00] + mata[M01] * matb[M10] + mata[M02] * matb[M20] + mata[M03] * matb[M30];
            mato[M01] = mata[M00] * matb[M01] + mata[M01] * matb[M11] + mata[M02] * matb[M21] + mata[M03] * matb[M31];
            mato[M02] = mata[M00] * matb[M02] + mata[M01] * matb[M12] + mata[M02] * matb[M22] + mata[M03] * matb[M32];
            mato[M03] = mata[M00] * matb[M03] + mata[M01] * matb[M13] + mata[M02] * matb[M23] + mata[M03] * matb[M33];
            mato[M10] = mata[M10] * matb[M00] + mata[M11] * matb[M10] + mata[M12] * matb[M20] + mata[M13] * matb[M30];
            mato[M11] = mata[M10] * matb[M01] + mata[M11] * matb[M11] + mata[M12] * matb[M21] + mata[M13] * matb[M31];
            mato[M12] = mata[M10] * matb[M02] + mata[M11] * matb[M12] + mata[M12] * matb[M22] + mata[M13] * matb[M32];
            mato[M13] = mata[M10] * matb[M03] + mata[M11] * matb[M13] + mata[M12] * matb[M23] + mata[M13] * matb[M33];
            mato[M20] = mata[M20] * matb[M00] + mata[M21] * matb[M10] + mata[M22] * matb[M20] + mata[M23] * matb[M30];
            mato[M21] = mata[M20] * matb[M01] + mata[M21] * matb[M11] + mata[M22] * matb[M21] + mata[M23] * matb[M31];
            mato[M22] = mata[M20] * matb[M02] + mata[M21] * matb[M12] + mata[M22] * matb[M22] + mata[M23] * matb[M32];
            mato[M23] = mata[M20] * matb[M03] + mata[M21] * matb[M13] + mata[M22] * matb[M23] + mata[M23] * matb[M33];
            mato[M30] = mata[M30] * matb[M00] + mata[M31] * matb[M10] + mata[M32] * matb[M20] + mata[M33] * matb[M30];
            mato[M31] = mata[M30] * matb[M01] + mata[M31] * matb[M11] + mata[M32] * matb[M21] + mata[M33] * matb[M31];
            mato[M32] = mata[M30] * matb[M02] + mata[M31] * matb[M12] + mata[M32] * matb[M22] + mata[M33] * matb[M32];
            mato[M33] = mata[M30] * matb[M03] + mata[M31] * matb[M13] + mata[M32] * matb[M23] + mata[M33] * matb[M33];
        }

        void mul(T mata[], const T matb[]) {
            _tmp[M00] = mata[M00] * matb[M00] + mata[M01] * matb[M10] + mata[M02] * matb[M20] + mata[M03] * matb[M30];
            _tmp[M01] = mata[M00] * matb[M01] + mata[M01] * matb[M11] + mata[M02] * matb[M21] + mata[M03] * matb[M31];
            _tmp[M02] = mata[M00] * matb[M02] + mata[M01] * matb[M12] + mata[M02] * matb[M22] + mata[M03] * matb[M32];
            _tmp[M03] = mata[M00] * matb[M03] + mata[M01] * matb[M13] + mata[M02] * matb[M23] + mata[M03] * matb[M33];
            _tmp[M10] = mata[M10] * matb[M00] + mata[M11] * matb[M10] + mata[M12] * matb[M20] + mata[M13] * matb[M30];
            _tmp[M11] = mata[M10] * matb[M01] + mata[M11] * matb[M11] + mata[M12] * matb[M21] + mata[M13] * matb[M31];
            _tmp[M12] = mata[M10] * matb[M02] + mata[M11] * matb[M12] + mata[M12] * matb[M22] + mata[M13] * matb[M32];
            _tmp[M13] = mata[M10] * matb[M03] + mata[M11] * matb[M13] + mata[M12] * matb[M23] + mata[M13] * matb[M33];
            _tmp[M20] = mata[M20] * matb[M00] + mata[M21] * matb[M10] + mata[M22] * matb[M20] + mata[M23] * matb[M30];
            _tmp[M21] = mata[M20] * matb[M01] + mata[M21] * matb[M11] + mata[M22] * matb[M21] + mata[M23] * matb[M31];
            _tmp[M22] = mata[M20] * matb[M02] + mata[M21] * matb[M12] + mata[M22] * matb[M22] + mata[M23] * matb[M32];
            _tmp[M23] = mata[M20] * matb[M03] + mata[M21] * matb[M13] + mata[M22] * matb[M23] + mata[M23] * matb[M33];
            _tmp[M30] = mata[M30] * matb[M00] + mata[M31] * matb[M10] + mata[M32] * matb[M20] + mata[M33] * matb[M30];
            _tmp[M31] = mata[M30] * matb[M01] + mata[M31] * matb[M11] + mata[M32] * matb[M21] + mata[M33] * matb[M31];
            _tmp[M32] = mata[M30] * matb[M02] + mata[M31] * matb[M12] + mata[M32] * matb[M22] + mata[M33] * matb[M32];
            _tmp[M33] = mata[M30] * matb[M03] + mata[M31] * matb[M13] + mata[M32] * matb[M23] + mata[M33] * matb[M33];

            mata[M00] = _tmp[M00];
            mata[M01] = _tmp[M01];
            mata[M02] = _tmp[M02];
            mata[M03] = _tmp[M03];

            mata[M10] = _tmp[M10];
            mata[M11] = _tmp[M11];
            mata[M12] = _tmp[M12];
            mata[M13] = _tmp[M13];

            mata[M20] = _tmp[M20];
            mata[M21] = _tmp[M21];
            mata[M22] = _tmp[M22];
            mata[M23] = _tmp[M23];

            mata[M30] = _tmp[M30];
            mata[M31] = _tmp[M31];
            mata[M32] = _tmp[M32];
            mata[M33] = _tmp[M33];
        }

        /** Sets this matrix to an orthographic projection matrix with the origin at (x,y) extending by width and height. The near plane
         * is set to 0, the far plane is set to 1.
         *
         * @param x The x-coordinate of the origin
         * @param y The y-coordinate of the origin
         * @param width The width
         * @param height The height
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToOrtho2D(T x, T y, T width, T height) {
            setToOrtho(x, x + width, y, y + height, 0, 1);
            return *this;
        }

        /** Sets this matrix to an orthographic projection matrix with the origin at (x,y) extending by width and height, having a near
         * and far plane.
         *
         * @param x The x-coordinate of the origin
         * @param y The y-coordinate of the origin
         * @param width The width
         * @param height The height
         * @param near The near plane
         * @param far The far plane
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToOrtho2D(T x, T y, T width, T height, T near, T far) {
            setToOrtho(x, x + width, y, y + height, near, far);
            return *this;
        }

        /** Sets the matrix to an orthographic projection like glOrtho (http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml) following
         * the OpenGL equivalent
         *
         * @param left The left clipping plane
         * @param right The right clipping plane
         * @param bottom The bottom clipping plane
         * @param top The top clipping plane
         * @param near The near clipping plane
         * @param far The far clipping plane
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToOrtho(T left, T right, T bottom, T top, T near, T far) {

            setToIdentity();
            T x_orth = 2 / (right - left);
            T y_orth = 2 / (top - bottom);
            T z_orth = -2 / (far - near);

            T tx = -(right + left) / (right - left);
            T ty = -(top + bottom) / (top - bottom);
            T tz = -(far + near) / (far - near);

            val[M00] = x_orth;
            val[M10] = 0;
            val[M20] = 0;
            val[M30] = 0;
            val[M01] = 0;
            val[M11] = y_orth;
            val[M21] = 0;
            val[M31] = 0;
            val[M02] = 0;
            val[M12] = 0;
            val[M22] = z_orth;
            val[M32] = 0;
            val[M03] = tx;
            val[M13] = ty;
            val[M23] = tz;
            val[M33] = 1;

            return *this;
        }

        /** Sets the 4th column to the translation vector.
         *
         * @param vector The translation vector
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setTranslation(const Vector3<T> &vector) {
            val[M03] = vector.x;
            val[M13] = vector.y;
            val[M23] = vector.z;
            return *this;
        }

        /** Sets the 4th column to the translation vector.
         *
         * @param x The X coordinate of the translation vector
         * @param y The Y coordinate of the translation vector
         * @param z The Z coordinate of the translation vector
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setTranslation(T x, T y, T z) {
            val[M03] = x;
            val[M13] = y;
            val[M23] = z;
            return *this;
        }

        /** Sets this matrix to a translation matrix, overwriting it first by an identity matrix and then setting the 4th column to the
         * translation vector.
         *
         * @param vector The translation vector
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToTranslation(const Vector3<T> &vector) {
            setToIdentity();
            val[M03] = vector.x;
            val[M13] = vector.y;
            val[M23] = vector.z;
            return *this;
        }

        /** Sets this matrix to a translation matrix, overwriting it first by an identity matrix and then setting the 4th column to the
         * translation vector.
         *
         * @param x The x-component of the translation vector.
         * @param y The y-component of the translation vector.
         * @param z The z-component of the translation vector.
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToTranslation(T x, T y, T z) {
            setToIdentity();
            val[M03] = x;
            val[M13] = y;
            val[M23] = z;
            return *this;
        }

        /** Sets the matrix to a rotation matrix about Z axis.
         *
         * <pre>
         *      [  M00  M01   _   M03  ]
         *      [  M10  M11   _   M13  ]
         *      [   _    _    _    _   ]
         *      [   _    _    _    _   ]
         * </pre>
         * @param radians The angle in radians
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &setToRotationRad(T radians) {
            setToIdentity();

            if (radians == 0) {
                return *this;
            }

            _rotation = radians;

            // Column major
            T c = cos(radians);
            T s = sin(radians);
            val[M00] = c;
            val[M01] = -s;
            val[M10] = s;
            val[M11] = c;
            return *this;
        }

        Matrix4<T> &setToScale(T x, T y, T z) {
            _scaleX = x;
            _scaleY = y;
            _scaleZ = z;
            setToIdentity();
            val[M00] = x;
            val[M11] = y;
            val[M22] = z;
            return *this;
        }

        Matrix4<T> &setToScale(T s) {
            _scaleX = s;
            _scaleY = s;
            _scaleZ = s;
            setToIdentity();
            val[M00] = s;
            val[M11] = s;
            val[M22] = s;
            return *this;
        }

        Matrix4<T> &scale(const Vector3<T> &scale) {
            _scaleX = scale.x;
            _scaleY = scale.y;
            _scaleZ = scale.z;

            val[M00] *= scale.x;
            val[M11] *= scale.y;
            val[M22] *= scale.z;
            return *this;
        }

        Matrix4<T> &scale(T x, T y, T z) {
            _scaleX = x;
            _scaleY = y;
            _scaleZ = z;
            val[M00] *= x;
            val[M11] *= y;
            val[M22] *= z;
            return *this;
        }

        Matrix4<T> &scale(T scale) {
            _scaleX = scale;
            _scaleY = scale;
            _scaleZ = scale;
            val[M00] *= scale;
            val[M11] *= scale;
            val[M22] *= scale;
            return *this;
        }

        Vector3<T> &getTranslation(const Vector3<T> &position) {
            position.x = val[M03];
            position.y = val[M13];
            position.z = val[M23];
            return position;
        }

        T getRotation() const {
            return _rotation;
        }

        const Vector3<T> &getScale(const Vector3<T> &scale) {
            scale.x = _scaleX;
            scale.y = _scaleY;
            scale.z = _scaleZ;
            return scale;
        }

        /** @return the squared scale factor on the X axis */
        T getScaleXSquared() {
            return val[Matrix4::M00] * val[Matrix4::M00] + val[Matrix4::M01] * val[Matrix4::M01] +
                   val[Matrix4::M02] * val[Matrix4::M02];
        }

        /** @return the squared scale factor on the Y axis */
        T getScaleYSquared() {
            return val[Matrix4::M10] * val[Matrix4::M10] + val[Matrix4::M11] * val[Matrix4::M11] +
                   val[Matrix4::M12] * val[Matrix4::M12];
        }

        /** @return the squared scale factor on the Z axis */
        T getScaleZSquared() {
            return val[Matrix4::M20] * val[Matrix4::M20] + val[Matrix4::M21] * val[Matrix4::M21] +
                   val[Matrix4::M22] * val[Matrix4::M22];
        }

        /** @return the scale factor on the X axis (non-negative) */
        T getScaleX() {
            return (Math::isZero(val[Matrix4::M01]) && Math::isZero(val[Matrix4::M02])) ? fabsf(val[Matrix4::M00])
                                                                                        : sqrt(getScaleXSquared());
        }

        /** @return the scale factor on the Y axis (non-negative) */
        T getScaleY() {
            return (Math::isZero(val[Matrix4::M10]) && Math::isZero(val[Matrix4::M12])) ? fabsf(val[Matrix4::M11])
                                                                                        : sqrt(getScaleYSquared());
        }

        /** @return the scale factor on the X axis (non-negative) */
        T getScaleZ() {
            return (Math::isZero(val[Matrix4::M20]) && Math::isZero(val[Matrix4::M21])) ? fabsf(val[Matrix4::M22])
                                                                                        : sqrt(getScaleZSquared());
        }

        /** removes the translational part and transposes the matrix. */
        Matrix4<T> &toNormalMatrix() {
            val[M03] = 0;
            val[M13] = 0;
            val[M23] = 0;
            return invert().transpose();
        }

        /** Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param x Translation in the x-axis.
         * @param y Translation in the y-axis.
         * @param z Translation in the z-axis.
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &postTranslate(T x, T y, T z) {
            _tmp[M00] = 1;
            _tmp[M01] = 0;
            _tmp[M02] = 0;
            _tmp[M03] = x;
            _tmp[M10] = 0;
            _tmp[M11] = 1;
            _tmp[M12] = 0;
            _tmp[M13] = y;
            _tmp[M20] = 0;
            _tmp[M21] = 0;
            _tmp[M22] = 1;
            _tmp[M23] = z;
            _tmp[M30] = 0;
            _tmp[M31] = 0;
            _tmp[M32] = 0;
            _tmp[M33] = 1;

            mul(val, _tmp);
            return *this;
        }

        /** Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         *
         * @param axis The vector axis to rotate around.
         * @param degrees The angle in degrees.
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &rotate(T radians) {
            if (radians == 0) return *this;

            _rotation += radians;

            // Column major
            T c = cos(radians);
            T s = sin(radians);

            _tmp[M00] = c;
            _tmp[M01] = -s;
            _tmp[M02] = 0;
            _tmp[M03] = 0;
            _tmp[M10] = s;
            _tmp[M11] = c;
            _tmp[M12] = 0;
            _tmp[M13] = 0;
            _tmp[M20] = 0;
            _tmp[M21] = 0;
            _tmp[M22] = 1;
            _tmp[M23] = 0;
            _tmp[M30] = 0;
            _tmp[M31] = 0;
            _tmp[M32] = 0;
            _tmp[M33] = 1;

            mul(val, _tmp);

            return *this;
        }

        /** Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' 1.x
         * glTranslate/glRotate/glScale.
         * @param scaleX The scale in the x-axis.
         * @param scaleY The scale in the y-axis.
         * @param scaleZ The scale in the z-axis.
         * @return This matrix for the purpose of chaining methods together. */
        Matrix4<T> &postScale(T scaleX, T scaleY, T scaleZ) {
            _tmp[M00] = scaleX;
            _tmp[M01] = 0;
            _tmp[M02] = 0;
            _tmp[M03] = 0;
            _tmp[M10] = 0;
            _tmp[M11] = scaleY;
            _tmp[M12] = 0;
            _tmp[M13] = 0;
            _tmp[M20] = 0;
            _tmp[M21] = 0;
            _tmp[M22] = scaleZ;
            _tmp[M23] = 0;
            _tmp[M30] = 0;
            _tmp[M31] = 0;
            _tmp[M32] = 0;
            _tmp[M33] = 1;

            mul(val, _tmp);
            return *this;
        }

        // ------------------------------------------------------------
        // Matrix values
        T val[16];

    private:
        T _rotation;
        T _scaleX;
        T _scaleY;
        T _scaleZ;

        T _tmp[16];
        //Matrix4<T> _tmpMat;

        //! toString
        friend std::ostream &operator<<(std::ostream &os, const Matrix4<T> &t) {
            std::cout << std::fixed << std::setw(11) << std::setprecision(6);
            return os << "Matrix4:" << std::endl <<
                   "[" << t.val[M00] << "|" << t.val[M01] << "|" << t.val[M02] << "|" << t.val[M03] << "]" <<
                   std::endl <<
                   "[" << t.val[M10] << "|" << t.val[M11] << "|" << t.val[M12] << "|" << t.val[M13] << "]" <<
                   std::endl <<
                   "[" << t.val[M20] << "|" << t.val[M21] << "|" << t.val[M22] << "|" << t.val[M23] << "]" <<
                   std::endl <<
                   "[" << t.val[M30] << "|" << t.val[M31] << "|" << t.val[M32] << "|" << t.val[M33] << "]" << std::endl;
        }
    };
}

#endif //RANGERBETA_MATRIX_H

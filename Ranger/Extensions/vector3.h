//
// Created by William DeVore on 3/20/16.
//

#ifndef RANGERBETA_VECTOR3_H
#define RANGERBETA_VECTOR3_H


#include <iostream>
#include <cmath>
#include <iomanip>
#include "math.h"
#include "matrix4.h"

namespace Ranger {
    template <typename T>
    class Interpolation;

    template<typename T>
    class Vector3 final {
    public:
        /** the x-component of this vector **/
        T x;
        /** the y-component of this vector **/
        T y;
        /** the z-component of this vector **/
        T z;


        Vector3() : x(0), y(0), z(0) { }

        Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) { }

        Vector3(T x, T y, T z) : x(x), y(y), z(z) { }

        virtual ~Vector3() = default;

        Vector3<T> clone() {
            return Vector3<T>(x, y, z);
        }

        /** Sets the vector to the given components
         *
         * @param x The x-component
         * @param y The y-component
         * @param z The z-component
         * @return this vector for chaining */
        Vector3<T> &set(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
            return *this;
        }

        /** Sets the vector to the given components
         *
         * @param x The x-component
         * @param y The y-component
         * @param z The z-component
         * @return this vector for chaining */
        Vector3<T> &set(const Vector3<T> &v) {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        /** Sets the components from the given spherical coordinate
         * @param azimuthalAngle The angle between x-axis in radians [0, 2pi]
         * @param polarAngle The angle between z-axis in radians [0, pi]
         * @return This vector for chaining */
        Vector3<T> &setFromSpherical(T azimuthalAngle, T polarAngle) {
            T cosPolar = cos(polarAngle);
            T sinPolar = sin(polarAngle);

            T cosAzim = cos(azimuthalAngle);
            T sinAzim = sin(azimuthalAngle);

            return set(cosAzim * sinPolar, sinAzim * sinPolar, cosPolar);
        }

        Vector3<T> &genRandomDirection() {
            T u = Math::genFloat();
            T v = Math::genFloat();

            T theta = Math::PI2 * u; // azimuthal angle
            T phi = (float) acos(2.0f * v - 1.0f); // polar angle

            return setFromSpherical(theta, phi);
        }

        /** Adds the given vector to this component
         * @param x The x-component of the other vector
         * @param y The y-component of the other vector
         * @param z The z-component of the other vector
         * @return This vector for chaining. */
        Vector3<T> &add(T x, T y, T z) {
            return set(this->x + x, this->y + y, this->z + z);
        }

        /** Adds the given vector to this component
         * @param x The x-component of the other vector
         * @param y The y-component of the other vector
         * @param z The z-component of the other vector
         * @return This vector for chaining. */
        Vector3<T> &add(const Vector3<T> &v) {
            return set(x + v.x, y + v.y, z + v.z);
        }

        Vector3<T> &add(T v) {
            return set(this->x + v, this->y + v, this->z + v);
        }

        Vector3<T> &sub(T x, T y, T z) {
            return set(this->x - x, this->y - y, this->z - z);
        }

        Vector3<T> &sub(const Vector3<T> &v) {
            return set(x - v.x, y - v.y, z - v.z);
        }

        Vector3<T> &sub(T v) {
            return set(this->x - v, this->y - v, this->z - v);
        }

        Vector3<T> &scale(T x, T y, T z) {
            return set(this->x * x, this->y * y, this->z * z);
        }

        Vector3<T> &scale(const Vector3<T> &v) {
            return set(x * v.x, y * v.y, z * v.z);
        }

        Vector3<T> &scale(T v) {
            return set(this->x * v, this->y * v, this->z * v);
        }

        Vector3<T> &mulAdd(const Vector3<T> &vec, T scalar) {
            x += vec.x * scalar;
            y += vec.y * scalar;
            z += vec.z * scalar;
            return *this;
        }

        Vector3<T> &mulAdd(const Vector3<T> &vec, const Vector3<T> &mulVec) {
            x += vec.x * mulVec.x;
            y += vec.y * mulVec.y;
            z += vec.z * mulVec.z;
            return *this;
        }

        /** @return The euclidean length */
        static T len(T x, T y, T z) {
            return sqrt(x * x + y * y + z * z);
        }

        /** @return The euclidean length */
        T len() {
            return sqrt(x * x + y * y + z * z);
        }

        /** @return The euclidean length squared */
        T lenSqr() {
            return x * x + y * y + z * z;
        }

        static T lenSqr(T x, T y, T z) {
            return x * x + y * y + z * z;
        }

        /** @param vector The other vector. Use eqEps for approximate check.
         * @return Whether this and the other vector are equal */
        bool eq(const Vector3<T> &vector) {
            return x == vector.x && y == vector.y && z == vector.z;
        }

        /** @param vector The other vector. Preferred usage.
         * @return Whether this and the other vector are equal  with an Epsilon */
        bool eqEps(const Vector3<T> &vector) {
            return (x - vector.x) < Math::Epsilon && (y - vector.y) < Math::Epsilon && (z - vector.z) < Math::Epsilon;
        }

        /** @return The euclidean distance between the two specified vectors */
        static T distance(T x1, T y1, T z1, T x2, T y2, T z2) {
            T a = x2 - x1;
            T b = y2 - y1;
            T c = z2 - z1;
            return sqrt(a * a + b * b + c * c);
        }

        T distance(const Vector3<T> &vector) {
            T a = vector.x - x;
            T b = vector.y - y;
            T c = vector.z - z;
            return sqrt(a * a + b * b + c * c);
        }

        /** @return the distance squared between this point and the given point */
        T distance(T x, T y, T z) {
            T a = x - this->x;
            T b = y - this->y;
            T c = z - this->z;
            return sqrt(a * a + b * b + c * c);
        }

        /** @return The euclidean distance squared between the two specified vectors */
        static T distanceSqr(T x1, T y1, T z1, T x2, T y2, T z2) {
            T a = x2 - x1;
            T b = y2 - y1;
            T c = z2 - z1;
            return (a * a + b * b + c * c);
        }

        T distanceSqr(const Vector3<T> &vector) {
            T a = vector.x - x;
            T b = vector.y - y;
            T c = vector.z - z;
            return (a * a + b * b + c * c);
        }

        /** @return the distance squared between this point and the given point */
        T distanceSqr(T x, T y, T z) {
            T a = x - this->x;
            T b = y - this->y;
            T c = z - this->z;
            return (a * a + b * b + c * c);
        }

        /** @return The dot product between the two vectors */
        static T dot(T x1, T y1, T z1, T x2, T y2, T z2) {
            return x1 * x2 + y1 * y2 + z1 * z2;
        }

        T dot(const Vector3<T> &vector) {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        /** Returns the dot product between this and the given vector.
         * @param x The x-component of the other vector
         * @param y The y-component of the other vector
         * @param z The z-component of the other vector
         * @return The dot product */
        T dot(T x, T y, T z) {
            return this->x * x + this->y * y + this->z * z;
        }

        /** Sets this vector to the cross product between it and the other vector.
         * @param vector The other vector
         * @return This vector for chaining */
        Vector3<T> &cross(const Vector3<T> &vector) {
            return set(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
        }

        /** Sets this vector to the cross product between it and the other vector.
         * @param x The x-component of the other vector
         * @param y The y-component of the other vector
         * @param z The z-component of the other vector
         * @return This vector for chaining */
        Vector3<T> &cross(T x, T y, T z) {
            return set(this->y * z - this->z * y, this->z * x - this->x * z, this->x * y - this->y * x);
        }

        /** Left-multiplies the vector by the given matrix, assuming the fourth (w) component of the vector is 1.
         * @param matrix The matrix
         * @return This vector for chaining */
        Vector3<T> &leftMul(const Matrix4<T> &matrix) {
            const T *l_mat = matrix.val;
            return set(x * l_mat[Matrix4<T>::M00] + y * l_mat[Matrix4<T>::M01] + z * l_mat[Matrix4<T>::M02] +
                       l_mat[Matrix4<T>::M03],
                       x * l_mat[Matrix4<T>::M10] + y * l_mat[Matrix4<T>::M11] + z * l_mat[Matrix4<T>::M12] +
                       l_mat[Matrix4<T>::M13],
                       x * l_mat[Matrix4<T>::M20] + y * l_mat[Matrix4<T>::M21] + z * l_mat[Matrix4<T>::M22] +
                       l_mat[Matrix4<T>::M23]);
        }

        /** Multiplies the vector by the transpose of the given matrix, assuming the fourth (w) component of the vector is 1.
         * @param matrix The matrix
         * @return This vector for chaining */
        Vector3<T> &transposeMul(const Matrix4<T> &matrix) {
            T *l_mat = matrix.val;
            return set(
                    x * l_mat[Matrix4<T>::M00] + y * l_mat[Matrix4<T>::M10] + z * l_mat[Matrix4<T>::M20] +
                    l_mat[Matrix4<T>::M30],
                    x * l_mat[Matrix4<T>::M01] + y * l_mat[Matrix4<T>::M11] + z * l_mat[Matrix4<T>::M21] +
                    l_mat[Matrix4<T>::M31],
                    x * l_mat[Matrix4<T>::M02] + y * l_mat[Matrix4<T>::M12] + z * l_mat[Matrix4<T>::M22] +
                    l_mat[Matrix4<T>::M32]);
        }

        /** Multiplies this vector by the given matrix dividing by w, assuming the fourth (w) component of the vector is 1. This is
         * mostly used to project/unproject vectors via a perspective projection matrix.
         *
         * @param matrix The matrix.
         * @return This vector for chaining */
        Vector3<T> &project(const Matrix4<T> &matrix) {
            T l_mat = matrix.val;
            T l_w = 1.0f /
                    (x * l_mat[Matrix4<T>::M30] + y * l_mat[Matrix4<T>::M31] + z * l_mat[Matrix4<T>::M32] +
                     l_mat[Matrix4<T>::M33]);
            return set((x * l_mat[Matrix4<T>::M00] + y * l_mat[Matrix4<T>::M01] + z * l_mat[Matrix4<T>::M02] +
                        l_mat[Matrix4<T>::M03]) * l_w,
                       (x * l_mat[Matrix4<T>::M10] + y * l_mat[Matrix4<T>::M11] + z * l_mat[Matrix4<T>::M12] +
                        l_mat[Matrix4<T>::M13]) * l_w,
                       (x * l_mat[Matrix4<T>::M20] + y * l_mat[Matrix4<T>::M21] + z * l_mat[Matrix4<T>::M22] +
                        l_mat[Matrix4<T>::M23]) * l_w);
        }

        /** Multiplies this vector by the first three columns of the matrix, essentially only applying rotation and scaling.
         *
         * @param matrix The matrix
         * @return This vector for chaining */
        Vector3<T> &rotation(const Matrix4<T> &matrix) {
            T *l_mat = matrix.val;
            return set(x * l_mat[Matrix4<T>::M00] + y * l_mat[Matrix4<T>::M01] + z * l_mat[Matrix4<T>::M02],
                       x * l_mat[Matrix4<T>::M10] + y * l_mat[Matrix4<T>::M11] + z * l_mat[Matrix4<T>::M12],
                       x * l_mat[Matrix4<T>::M20] + y * l_mat[Matrix4<T>::M21] + z * l_mat[Matrix4<T>::M22]);
        }

        /** Multiplies this vector by the transpose of the first three columns of the matrix. Note: only works for translation and
         * rotation, does not work for scaling. For those, use {@link #rot(Matrix4)} with {@link Matrix4#inv()}.
         * @param matrix The transformation matrix
         * @return The vector for chaining */
        Vector3<T> &unrotate(const Matrix4<T> &matrix) {
            T l_mat = matrix.val;
            return set(x * l_mat[Matrix4<T>::M00] + y * l_mat[Matrix4<T>::M10] + z * l_mat[Matrix4<T>::M20],
                       x * l_mat[Matrix4<T>::M01] + y * l_mat[Matrix4<T>::M11] + z * l_mat[Matrix4<T>::M21],
                       x * l_mat[Matrix4<T>::M02] + y * l_mat[Matrix4<T>::M12] + z * l_mat[Matrix4<T>::M22]);
        }

        /** Translates this vector in the direction opposite to the translation of the matrix and then multiplies this vector by the
         * transpose of the first three columns of the matrix. Note: only works for translation and rotation, does not work for
         * scaling. For those, use {@link #mul(Matrix4)} with {@link Matrix4#inv()}.
         * @param matrix The transformation matrix
         * @return The vector for chaining */
        Vector3<T> &invTranslate(const Matrix4<T> &matrix) {
            T *l_mat = matrix.val;
            x -= l_mat[Matrix4<T>::M03];
            y -= l_mat[Matrix4<T>::M03];
            z -= l_mat[Matrix4<T>::M03];
            return set(x * l_mat[Matrix4<T>::M00] + y * l_mat[Matrix4<T>::M10] + z * l_mat[Matrix4<T>::M20],
                       x * l_mat[Matrix4<T>::M01] + y * l_mat[Matrix4<T>::M11] + z * l_mat[Matrix4<T>::M21],
                       x * l_mat[Matrix4<T>::M02] + y * l_mat[Matrix4<T>::M12] + z * l_mat[Matrix4<T>::M22]);
        }

        /** Rotates this vector by the given angle in degrees around the given axis.
         *
         * @param degrees the angle in degrees
         * @param axisX the x-component of the axis
         * @param axisY the y-component of the axis
         * @param axisZ the z-component of the axis
         * @return This vector for chaining */
//        Vector3 &rotate(T degrees, T axisX, T axisY, T axisZ) {
//            return leftMul(Math::mat4f.setToRotation(axisX, axisY, axisZ, degrees));
//        }
//
//        /** Rotates this vector by the given angle in radians around the given axis.
//         *
//         * @param radians the angle in radians
//         * @param axisX the x-component of the axis
//         * @param axisY the y-component of the axis
//         * @param axisZ the z-component of the axis
//         * @return This vector for chaining */
//        Vector3 &rotateRad(T radians, T axisX, T axisY, T axisZ) {
//            return leftMul(Math::mat4f.setToRotationRad(axisX, axisY, axisZ, radians));
//        }
//
//        /** Rotates this vector by the given angle in degrees around the given axis.
//         *
//         * @param axis the axis
//         * @param degrees the angle in degrees
//         * @return This vector for chaining */
//        Vector3 &rotate(const Vector3 &axis, T degrees) {
//            Math::mat4f.setToRotation(axis, degrees);
//            return leftMul(Math::mat4f);
//        }
//
//        /** Rotates this vector by the given angle in radians around the given axis.
//         *
//         * @param axis the axis
//         * @param radians the angle in radians
//         * @return This vector for chaining */
//        Vector3 &rotateRad(const Vector3 &axis, T radians) {
//            Math::mat4f.setToRotationRad(axis, radians);
//            return leftMul(Math::mat4f);
//        }

        bool isUnit() {
            return isUnit(0.000000001f);
        }

        bool isUnit(T margin) {
            return abs(lenSqr() - 1.0f) < margin;
        }

        bool isZero() {
            return x == 0 && y == 0 && z == 0;
        }

        bool isZero(T margin) {
            return lenSqr() < margin;
        }

        bool isOnLine(const Vector3<T> &other, T epsilon) {
            return lenSqr(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x) <= epsilon;
        }

        bool isOnLine(const Vector3<T> &other) {
            return lenSqr(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x) <=
                   Math::FLOAT_ROUNDING_ERROR;
        }

        bool isCollinear(const Vector3<T> &other, T epsilon) {
            return isOnLine(other, epsilon) && hasSameDirection(other);
        }

        bool isCollinear(const Vector3<T> &other) {
            return isOnLine(other) && hasSameDirection(other);
        }

        bool isCollinearOpposite(const Vector3<T> &other, T epsilon) {
            return isOnLine(other, epsilon) && hasOppositeDirection(other);
        }

        bool isCollinearOpposite(const Vector3<T> &other) {
            return isOnLine(other) && hasOppositeDirection(other);
        }

        bool isPerpendicular(const Vector3<T> &vector) {
            return Math::isZero(dot(vector));
        }

        bool isPerpendicular(const Vector3<T> &vector, T epsilon) {
            return Math::isZero(dot(vector), epsilon);
        }

        bool hasSameDirection(const Vector3<T> &vector) {
            return dot(vector) > 0;
        }

        bool hasOppositeDirection(const Vector3<T> &vector) {
            return dot(vector) < 0;
        }

        Vector3 &lerp(const Vector3<T> &target, T alpha) {
            x += alpha * (target.x - x);
            y += alpha * (target.y - y);
            z += alpha * (target.z - z);
            return *this;
        }

        Vector3 &interpolate(const Vector3 &target, T alpha, Interpolation<T> interpolator) {
            return lerp(target, interpolator.apply(0.0f, 1.0f, alpha));
        }

        Vector3<T> &setLength(T len) {
            return setLength2(len * len);
        }

        Vector3<T> &setLength2(T len2) {
            float oldLen2 = lenSqr();
            return (oldLen2 == 0 || oldLen2 == len2) ? this : scale(sqrt(len2 / oldLen2));
        }

        Vector3<T> &clamp(T min, T max) {
            T len2 = lenSqr();
            if (len2 == 0.0f) return *this;
            T max2 = max * max;
            if (len2 > max2) return scale(sqrt(max2 / len2));
            T min2 = min * min;
            if (len2 < min2) return scale(sqrt(min2 / len2));
            return *this;
        }

        bool epsilonEquals(const Vector3<T> &other, T epsilon) {
            if (abs(other.x - x) > epsilon) return false;
            if (abs(other.y - y) > epsilon) return false;
            if (abs(other.z - z) > epsilon) return false;
            return true;
        }

        /** Compares this vector with the other vector, using the supplied epsilon for fuzzy equality testing.
         * @return whether the vectors are the same. */
        bool epsilonEquals(T x, T y, T z, T epsilon) {
            if (abs(x - this->x) > epsilon) return false;
            if (abs(y - this->y) > epsilon) return false;
            if (abs(z - this->z) > epsilon) return false;
            return true;
        }

        Vector3<T> &setZero() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
            return *this;
        }

    private:

        //! toString
        friend std::ostream &operator<<(std::ostream &os, const Vector3<T> &t) {
            std::cout << std::fixed << std::setw(11) << std::setprecision(6);
            return os << "Vector3: (" << t.x << ", " << t.y << ", " << t.z << ")";
        }
    };
}

#endif //RANGERBETA_VECTOR3_H

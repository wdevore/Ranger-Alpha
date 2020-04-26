//
// Created by William DeVore on 3/20/16.
//

#ifndef RANGERBETA_MATH_H
#define RANGERBETA_MATH_H


#include <cstdlib>
#include <math.h>

namespace Ranger {
    template<typename T>
    class Matrix4;

    class Math {
    public:

        static constexpr float PI = 3.1415927f;
        static constexpr float PI2 = PI * 2;

        static constexpr float FLOAT_ROUNDING_ERROR = 0.000001f; // 32 bits

        static constexpr float E = 2.7182818f;
        static constexpr float Epsilon = 0.000001f;

        /** multiply by this to convert from radians to degrees */
        static constexpr float radiansToDegrees = 180.0f / PI;
        /** multiply by this to convert from degrees to radians */
        static constexpr float degreesToRadians = PI / 180.0f;

        static Matrix4<float> mat4f;

        static double toRadians(double degrees) { return degrees * degreesToRadians; }

        static double toDegrees(double radians) { return radians * radiansToDegrees; }

        static float clamp(float value, float min, float max) {
            if (value < min) return min;
            if (value > max) return max;
            return value;
        }

        static float genFloat() {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            return r;
        }

        /** Returns true if the value is zero (using the default tolerance as upper bound) */
        static bool isZero(float value) {
            return fabsf(value) <= FLOAT_ROUNDING_ERROR;
        }

        /** Returns true if the value is zero.
         * @param tolerance represent an upper bound below which the value is considered zero. */
        static bool isZero(float value, float tolerance) {
            return fabsf(value) <= tolerance;
        }

        /** Returns true if a is nearly equal to b. The function uses the default floating error tolerance.
         * @param a the first value.
         * @param b the second value. */
        static bool isEqual(float a, float b) {
            return fabsf(a - b) <= FLOAT_ROUNDING_ERROR;
        }

    };
}

#endif //RANGERBETA_MATH_H

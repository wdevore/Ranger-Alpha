//
// Created by William DeVore on 3/22/16.
//

#include <vector>

#ifndef RANGERBETA_INTERPOLATION_H
#define RANGERBETA_INTERPOLATION_H

#endif //RANGERBETA_INTERPOLATION_H
namespace Ranger {
    template<typename T>
    class Interpolation {
    public:
        /** @param a Alpha value between 0 and 1. */
        virtual T apply(T a) = 0;

        /** @param a Alpha value between 0 and 1. */
        T apply(T start, T end, T a) {
            return start + (end - start) * apply(a);
        }
    };

    //------------------------------------------------------------
    // Linear interpolation
    //------------------------------------------------------------
    template<typename T>
    class Linear final : public Interpolation<T> {
    public:
        Linear(T scale) {
            this->scale = scale;
        }

        T apply(T a) override {
            return a * scale;
        }

    private:
        T scale;
    };

    //------------------------------------------------------------
    // Fade interpolation
    //------------------------------------------------------------
    template<typename T>
    class Fade final : public Interpolation<T> {
    public:
        T apply(T a) override {
            return Math::clamp(a * a * a * (a * (a * 6 - 15) + 10), 0, 1);
        }
    };

    //------------------------------------------------------------
    // Power interpolations
    //------------------------------------------------------------
    template<typename T>
    class Pow : public Interpolation<T> {
    public:
        Pow() = default;

        Pow(int power) {
            _power = power;
        }

        T apply(T a) override {
            if (a <= 0.5) return (T) pow(a * 2, _power) / 2;
            return (T) pow((a - 1) * 2, _power) / (_power % 2 == 0 ? -2 : 2) + 1;
        }

    protected:
        int _power;
    };

    template<typename T>
    class PowIn final : public Pow<T> {
    public:
        PowIn(int power) : Pow<T>(power) { }

        T apply(T a) override {
            return (T) pow(a, Pow<T>::_power);
        }
    };

    template<typename T>
    class PowOut final : public Pow<T> {
    public:
        PowOut(int power) : Pow<T>(power) { }

        T apply(T a) override {
            return (T) pow(a - 1, Pow<T>::_power) * (Pow<T>::_power % 2 == 0 ? -1 : 1) + 1;
        }
    };

    //------------------------------------------------------------
    // Exponential interpolations
    // Typical configuration usages and for (In/Out):
    // Exp<float> exp(2.0f, 10.0f); // exp10
    // Exp<float> exp(2.0f, 5.0f); // exp5
    //------------------------------------------------------------
    template<typename T>
    class Exp : public Interpolation<T> {
    public:
        Exp() = default;

        Exp(T value, T power) {
            _value = value;
            _power = power;
            _min = pow(value, -power);
            _scale = 1 / (1 - _min);
        }

        T apply(T a) override {
            if (a <= 0.5) return (pow(_value, _power * (a * 2 - 1)) - _min) * _scale / 2;
            return (2 - (pow(_value, -_power * (a * 2 - 1)) - _min) * _scale) / 2;
        }

    protected:
        T _value, _power, _min, _scale;
    };

    template<typename T>
    class ExpIn final : public Exp<T> {
    public:
        ExpIn(T value, T power) : Exp<T>(value, power) { }

        T apply(T a) override {
            return (pow(Exp<T>::_value, Exp<T>::_power * (a - 1)) - Exp<T>::_min) * Exp<T>::_scale;
        }
    };

    template<typename T>
    class ExpOut final : public Exp<T> {
    public:
        ExpOut(T value, T power) : Exp<T>(value, power) { }

        T apply(T a) override {
            return 1 - (pow(Exp<T>::_value, -Exp<T>::_power * a) - Exp<T>::_min) * Exp<T>::_scale;
        }
    };

    //------------------------------------------------------------
    // Elastic interpolations
    // Typical configuration usages:
    // Elastic<float> ela(2, 10, 7, 1);
    // ElasticIn<float> ela(2, 10, 6, 1);
    // ElasticOut<float> ela(2, 10, 7, 1);
    //------------------------------------------------------------
    template<typename T>
    class Elastic : public Interpolation<T> {

    public:

        Elastic() = default;

        Elastic(T value, T power, int bounces, T scale) {
            _value = value;
            _power = power;
            _scale = scale;
            _bounces = bounces * Math::PI * (bounces % 2 == 0 ? 1 : -1);
        }

        T apply(T a) override {
            if (a <= 0.5) {
                a *= 2;
                return pow(_value, _power * (a - 1)) * sin(a * _bounces) * _scale / 2;
            }
            a = 1 - a;
            a *= 2;
            return 1 - pow(_value, _power * (a - 1)) * sin((a) * _bounces) * _scale / 2;
        }

    protected:
        int _bounces;
        T _value, _power, _scale;
    };

    template<typename T>
    class ElasticIn final : public Elastic<T> {
    public:
        ElasticIn(T value, T power, int bounces, T scale) : Elastic<T>(value, power, bounces, scale) { }

        T apply(T a) override {
            if (a >= 0.99) return 1;
            return pow(Elastic<T>::_value, Elastic<T>::_power * (a - 1)) * sin(a * Elastic<T>::_bounces) *
                   Elastic<T>::_scale;
        }
    };

    template<typename T>
    class ElasticOut final : public Elastic<T> {
    public:
        ElasticOut(T value, T power, int bounces, T scale) : Elastic<T>(value, power, bounces, scale) { }

        T apply(T a) override {
            a = 1 - a;
            return (1 - pow(Elastic<T>::_value, Elastic<T>::_power * (a - 1)) * sin(a * Elastic<T>::_bounces) *
                        Elastic<T>::_scale);
        }
    };

    //------------------------------------------------------------
    // Bounce interpolations
    // Typical configuration usages:
    // Bounce<float> bou(4);
    // BounceIn<float> bou(4);
    // BounceOut<float> bou(4);
    //------------------------------------------------------------
    template<typename T>
    class BounceOut : public Interpolation<T> {
    public:
        BounceOut(const std::vector<T> &widths, const std::vector<T> &heights) {
            if (widths.size() != heights.size())
                throw std::invalid_argument("Must be the same number of widths and heights.");
            _widths = widths;
            _heights = heights;
        }

        BounceOut(int bounces) {
            if (bounces < 2 || bounces > 5)
                throw std::invalid_argument("bounces cannot be < 2 or > 5");

            _heights.push_back(1);

            switch (bounces) {
                case 2:
                    _widths.push_back(0.6);
                    _widths.push_back(0.4);
                    _heights.push_back(0.33);
                    break;
                case 3:
                    _widths.push_back(0.4);
                    _widths.push_back(0.4);
                    _widths.push_back(0.2);
                    _heights.push_back(0.33);
                    _heights.push_back(0.1);
                    break;
                case 4:
                    _widths.push_back(0.34);
                    _widths.push_back(0.34);
                    _widths.push_back(0.2);
                    _widths.push_back(0.15);
                    _heights.push_back(0.26);
                    _heights.push_back(0.11);
                    _heights.push_back(0.03);
                    break;
                case 5:
                    _widths.push_back(0.3);
                    _widths.push_back(0.3);
                    _widths.push_back(0.2);
                    _widths.push_back(0.1);
                    _widths.push_back(0.1);
                    _heights.push_back(0.45);
                    _heights.push_back(0.3);
                    _heights.push_back(0.15);
                    _heights.push_back(0.06);
                    break;
            }

            _widths[0] *= 2;
        }

        T apply(T a) override {
            a += _widths[0] / 2;
            T width = 0, height = 0;
            for (int i = 0, n = _widths.size(); i < n; i++) {
                width = _widths[i];
                if (a <= width) {
                    height = _heights[i];
                    break;
                }
                a -= width;
            }
            a /= width;
            T z = 4 / width * height * a;
            return 1 - (z - z * a) * width;
        }

    protected:
        std::vector<T> _widths;
        std::vector<T> _heights;
    };

    template<typename T>
    class Bounce final : public BounceOut<T> {
    public:
        Bounce(const std::vector<T> &widths, const std::vector<T> &heights) : BounceOut<T>(widths, heights) { }

        Bounce(int bounces) : BounceOut<T>(bounces) { }

        T apply(T a) override {
            if (a <= 0.5) return (1 - out(1 - a * 2)) / 2;
            return out(a * 2 - 1) / 2 + 0.5f;
        }

    private:
        T out(T a) {
            T test = a + BounceOut<T>::_widths[0] / 2;
            if (test < BounceOut<T>::_widths[0]) return test / (BounceOut<T>::_widths[0] / 2) - 1;
            return BounceOut<T>::apply(a);
        }

    };

    template<typename T>
    class BounceIn final : public BounceOut<T> {
    public:
        BounceIn(const std::vector<T> &widths, const std::vector<T> &heights) : BounceOut<T>(widths, heights) { }

        BounceIn(int bounces) : BounceOut<T>(bounces) { }

        T apply(T a) override {
            return 1 - BounceOut<T>::apply(1 - a);
        }
    };

    //------------------------------------------------------------
    // Swing interpolations
    // Typical configuration usages:
    // Swing<float> swi(1.5f);
    // SwingIn<float> swi(2.0f);
    // SwingOut<float> swi(2.0f);
    //------------------------------------------------------------
    template<typename T>
    class Swing : public Interpolation<T> {
    public:

        Swing() = default;

        Swing(T scale) {
            _scale = scale * 2;
        }

        T apply(T a) {
            if (a <= 0.5f) {
                a *= 2;
                return a * a * ((_scale + 1) * a - _scale) / 2;
            }
            a--;
            a *= 2;
            return a * a * ((_scale + 1) * a + _scale) / 2 + 1;
        }

    protected:
        T _scale;
    };

    template<typename T>
    class SwingOut final : public Swing<T> {
    public:
        SwingOut(T scale) : Swing<T>(scale) { }

        T apply(T a) override {
            a--;
            return a * a * ((Swing<T>::_scale + 1) * a + Swing<T>::_scale) + 1;
        }
    };

    template<typename T>
    class SwingIn final : public Swing<T> {
    public:
        SwingIn(T scale) : Swing<T>(scale) { }

        T apply(T a) override {
            return a * a * ((Swing<T>::_scale + 1) * a - Swing<T>::_scale);
        }
    };

    //------------------------------------------------------------
    // Sine interpolations
    //------------------------------------------------------------
    template<typename T>
    class Sine : public Interpolation<T> {
    public:

        Sine() = default;

        Sine(T scale) {
            _scale = scale;
        }

        T apply(T a) {
            return ((1 - cos(a * Math::PI)) / 2) * _scale;
        }

    protected:
        T _scale = 1;
    };

    template<typename T>
    class SineIn final : public Sine<T> {
    public:
        SineIn(T scale) : Sine<T>(scale) { }

        T apply(T a) override {
            return (1 - cos(a * Math::PI / 2)) * Sine<T>::_scale;
        }
    };

    template<typename T>
    class SineOut final : public Sine<T> {
    public:
        SineOut(T scale) : Sine<T>(scale) { }

        T apply(T a) override {
            return sin(a * Math::PI / 2) * Sine<T>::_scale;
        }
    };

    //------------------------------------------------------------
    // Circle interpolations
    //------------------------------------------------------------
    template<typename T>
    class Circle : public Interpolation<T> {
    public:

        Circle() = default;

        Circle(T scale) {
            _scale = scale;
        }

        T apply(T a) {
            if (a <= 0.5f) {
                a *= 2;
                return ((1 - sqrt(1 - a * a)) / 2) * _scale;
            }
            a--;
            a *= 2;
            return (((1 - a * a) + 1) / 2) * _scale;
        }

    protected:
        T _scale = 1;
    };

    template<typename T>
    class CircleIn final : public Circle<T> {
    public:
        CircleIn(T scale) : Circle<T>(scale) { }

        T apply(T a) override {
            // TODO adding a-- eradicates the NAN condition at 1.0
            // but it changes the results
            //a--;
            T s = sqrt(1 - a * a);
            if (isnan(s))
                return sqrt(Circle<T>::_scale);
            return (1 - s) * Circle<T>::_scale;
        }
    };

    template<typename T>
    class CircleOut final : public Circle<T> {
    public:
        CircleOut(T scale) : Circle<T>(scale) { }

        T apply(T a) override {
            a--;
            T s = sqrt(1 - a * a);
            if (isnan(s))
                return sqrt(Circle<T>::_scale);
            return s * Circle<T>::_scale;
        }
    };

}
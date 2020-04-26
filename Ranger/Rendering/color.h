//
// Created by William DeVore on 11/10/15.
//

#ifndef RANGERALPHA_COLORS_H
#define RANGERALPHA_COLORS_H

#include <iosfwd>
#include <string>

namespace Ranger {
    class Color final {

    public:

        Color() = default;

        Color(float r, float g, float b, float a) : _r(r), _g(g), _b(b), _a(a) {}

        Color(const std::string& hex) { set(hex); }

        Color(int r, int g, int b, int a);

        void set(float r, float g, float b, float a);

        void set(const Color& c);

        void set(const std::string& hex);

        static Color hexToColor(const std::string& hex);

        float r() const {
            return _r;
        }

        void r(float _r) {
            Color::_r = _r;
        }

        float g() const {
            return _g;
        }

        void g(float _g) {
            Color::_g = _g;
        }

        float b() const {
            return _b;
        }

        void b(float _b) {
            Color::_b = _b;
        }

        float a() const {
            return _a;
        }

        void a(float _a) {
            Color::_a = _a;
        }

        static Color Transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }

        static Color White() { return Color(255, 255, 255, 255); }

        static Color Black() { return Color(0, 0, 0, 255); }

        static Color Grey() { return Color(128, 128, 128, 255); }

        static Color Red() { return Color(255, 0, 0, 255); }

        static Color Green() { return Color(0, 255, 0, 255); }

        static Color Blue() { return Color(0, 0, 255, 255); }

        static Color Yellow() { return Color(255, 255, 0, 255); }

        static Color NavyBlue() { return Color(10, 20, 100, 255); }

        static Color LightBlue() { return Color(128, 128, 255, 255); }

        static Color GreyBlue() { return Color(72, 100, 180, 255); }

        static Color DarkBlue() { return Color(10, 50, 100, 255); }

        static Color DartBlue() { return Color(109, 157, 235, 255); }

        static Color Orange() { return Color(255, 127, 0, 255); }

        static Color GoldYellow() { return Color(255, 200, 0, 255); }

        static Color GreenYellow() { return Color(173, 255, 47, 255); }

        static Color YellowGreen() { return Color(154, 205, 50, 255); }

        // Pantone colors
        // http://damonbauer.github.io/Pantone-Sass/
        static Color Skin() { return Color("#fcc89bff"); }

        static Color Purple() { return Color("#8031a7ff"); } //527-C

        std::string toString();

        std::string toStringInt();

    private:
        static std::string cutHex(const std::string& h);

        static float hexToR(const std::string& h);

        static float hexToG(const std::string& h);

        static float hexToB(const std::string& h);

        static float hexToA(const std::string& h);

    private:
        float _r{};
        float _g{};
        float _b{};
        float _a{};
    };
}


#endif //RANGERALPHA_COLORS_H

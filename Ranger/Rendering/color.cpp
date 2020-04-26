//
// Created by William DeVore on 11/10/15.
//

#include <sstream>
#include "color.h"

namespace Ranger {

    Color::Color(int r, int g, int b, int a) {
        _r = r / 255.0f;
        _g = g / 255.0f;
        _b = b / 255.0f;
        _a = a / 255.0f;
    }

    void Color::set(float r, float g, float b, float a) {
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }

    void Color::set(const Color& c) {
        set(c.r(), c.g(), c.b(), c.a());
    }

    void Color::set(const std::string& hex) {
        set(Color::hexToColor(hex));
    }

    //! format #aabbccdd = HTML format.
    Color Color::hexToColor(const std::string& hex) {
        return Ranger::Color(hexToR(hex), hexToG(hex), hexToB(hex), hexToA(hex));
    }

    std::string Color::cutHex(const std::string& h) {
        if (h.find("#") != std::string::npos) {
            return h.substr(1, h.length());
        } else if (h.find("0x") != std::string::npos) {
            return h.substr(2, h.length());
        }

        return h;
    }

    float Color::hexToR(const std::string& h) {
        std::string ch = "0x" + cutHex(h).substr(0, 2);
        float d = std::stold(ch);
        return d / 255.0f;
    }

    float Color::hexToG(const std::string& h) {
        std::string ch = "0x" + cutHex(h).substr(2, 2);
        float d = std::stold(ch);
        return d / 255.0f;
    }

    float Color::hexToB(const std::string& h) {
        std::string ch = "0x" + cutHex(h).substr(4, 2);
        float d = std::stold(ch);
        return d / 255.0f;
    }

    float Color::hexToA(const std::string& h) {
        std::string ch = "0x" + cutHex(h).substr(6, 2);
        float d = std::stold(ch);
        return d / 255.0f;
    }

    std::string Color::toString() {
        std::stringstream ss;
        ss << "(" << _r << ", " << _g << ", " << _b << ", " << _a << ")";
        return move(ss.str());
    }

    std::string Color::toStringInt() {
        std::stringstream ss;
        ss << "(" << (int) (_r * 255.0f) << ", " << (int) (_g * 255.0f) << ", " << (int) (_b * 255.0f) << ", "
           << (int) (_a * 255.0f) << ")";
        return move(ss.str());
    }
}
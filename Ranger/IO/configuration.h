//
// Created by William DeVore on 10/25/15.
//

#ifndef RANGERALPHA_CONFIGURATION_H
#define RANGERALPHA_CONFIGURATION_H

/*!
 * This configuration object is only used for the desktop. Mobiles provide tis
 * information through their respective framework.
 */

#include "../Rendering/color.h"
#include "../ranger.h"
#include "json11.hpp"
#include <string>
#include <vector>

namespace Ranger {
using namespace std;

using jO = json11::Json::object;

class Configuration {

public:
    Configuration() = default;

    Configuration(const std::string& file);

    //~configuration() { std::cout << "~configuration" << std::endl; }

    void configure(const std::string& file);

    void flush();

    const string& title() const
    {
        return _title;
    }

    void title(const string& title)
    {
        _title = title;
    }

    bool is_fullscreen() const
    {
        return _fullscreen;
    }

    void fullscreen(bool fullscreen)
    {
        _fullscreen = fullscreen;
    }

    const Orientation& orientation() const
    {
        return _orientation;
    }

    void orientation(const Orientation& orientation)
    {
        _orientation = orientation;
    }

    int bitsPerPixel() const
    {
        return _bitsPerPixel;
    }

    void bitsPerPixel(int bitsPerPixel)
    {
        _bitsPerPixel = bitsPerPixel;
    }

    int windowPositionX() const
    {
        return _windowPositionX;
    }

    void windowPositionX(int windowPositionX)
    {
        _windowPositionX = windowPositionX;
    }

    int windowPositionY() const
    {
        return _windowPositionY;
    }

    void windowPositionY(int windowPositionY)
    {
        _windowPositionY = windowPositionY;
    }

    int deviceResolutionWidth() const
    {
        return _deviceWidth;
    }

    void deviceResolutionWidth(int deviceResolutionWidth)
    {
        _deviceWidth = deviceResolutionWidth;
    }

    int deviceResolutionHeight() const
    {
        return _deviceHeight;
    }

    void deviceResolutionHeight(int deviceResolutionHeight)
    {
        _deviceHeight = deviceResolutionHeight;
    }

    int virtualWidth() const
    {
        return _virtualWidth;
    }

    int virtualHeight() const
    {
        return _virtualHeight;
    }

    const std::vector<float>& view() const
    {
        return _view;
    }

    bool is_ViewCentered() const
    {
        return _viewCentered;
    }

    bool is_lockToVSync() const
    {
        return _lockToVsync;
    }

    bool is_configured() const
    {
        return _configured;
    }

    int loopFor() const
    {
        return _loopFor;
    }

    void loopFor(int loopFor)
    {
        _loopFor = loopFor;
    }

    bool isEngineEnabled() const
    {
        return _engineEnabled;
    }

    bool isShowConfig() const
    {
        return _showConfig;
    }

    bool isShowGLInfo() const
    {
        return _showGLInfo;
    }

    bool isShowMonitorInfo() const
    {
        return _showMonitorInfo;
    }

    bool isShowTimingInfo() const
    {
        return _showTimingInfo;
    }

    bool isShowJoystickInfo() const
    {
        return _showJoystickInfo;
    }

    int GLMajorVersion() const
    {
        return _GLMajorVersion;
    }

    int GLMinorVersion() const
    {
        return _GLMinorVersion;
    }

    double FPSRefreshRate() const
    {
        return _FPSRefreshRate;
    }

    const Color& clearColor() const
    {
        return _clearColor;
    }

    void clearColor(const Color& _clearColor)
    {
        Configuration::_clearColor = _clearColor;
    }

    const std::string& fontPath() const
    {
        return _fontPath;
    }

    const std::string& fontName() const
    {
        return _fontName;
    }

    int fontSize()
    {
        return _fontSize;
    }

    float fontScale()
    {
        return _fontScale;
    }

    int fontCharsFromSet()
    {
        return _fontCharsFromSet;
    }

private:
    jO _setToDefault();

private:
    bool _configured = false;

    string _configFile{};

    string _title{};
    bool _fullscreen{ false };
    Orientation _orientation;
    int _bitsPerPixel{};

    int _GLMajorVersion{};
    int _GLMinorVersion{};

    int _windowPositionX{};
    int _windowPositionY{};

    std::vector<float> _view{ 0.0f, 0.0f, 0.0f };
    bool _viewCentered{ true };

    int _deviceWidth{};
    int _deviceHeight{};

    int _virtualWidth{};
    int _virtualHeight{};

    std::string _fontPath;
    std::string _fontName;
    int _fontSize{ 16 };
    int _fontCharsFromSet{ 128 };
    float _fontScale{1.0f};
    
    bool _lockToVsync{ true };
    double _FPSRefreshRate{};

    //! toString
    friend std::ostream& operator<<(std::ostream&, const Configuration&);

    int _loopFor{ -1 };
    bool _engineEnabled{ true };
    bool _showConfig{ false };
    bool _showGLInfo{ false };
    bool _showMonitorInfo{ false };
    bool _showTimingInfo{ false };
    bool _showJoystickInfo{ false };

    Color _clearColor;
};
}

#endif //RANGERALPHA_CONFIGURATION_H

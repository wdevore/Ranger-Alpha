//
// Created by William DeVore on 10/25/15.
//

#include "configuration.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

namespace Ranger {

Configuration::Configuration(const std::string& file)
    : _configFile(file)
{
}

void Configuration::configure(const std::string& file)
{
    _configFile = file;

    // open input file
    std::ifstream ifFile(_configFile);

    // file opened?
    if (!ifFile) {
        std::stringstream ss;
        ss << __FILE__ << "::" << __func__ << ": Couldn't open '" << _configFile << "'";
        throw std::invalid_argument(ss.str());
    }

    // http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::stringstream strStream;
    strStream << ifFile.rdbuf(); //read the file
    std::string rawJson = strStream.str();

    // OR
    //        ifFile.seekg(0, std::ios::end);
    //        _json.reserve(ifFile.tellg());
    //        ifFile.seekg(0, std::ios::beg);
    //
    //        _json.assign((std::istreambuf_iterator<char>(ifFile)),
    //                   std::istreambuf_iterator<char>());

    std::string errors;

    //std::cout << rawJson << std::endl;

    json11::Json jsonObj = json11::Json::parse(rawJson, errors);

    // Transfer values into properties
    json11::Json window = jsonObj["Window"];

    _title = window["Title"].string_value();
    _fullscreen = window["FullScreen"].bool_value();
    _lockToVsync = window["LockToVSync"].bool_value();

    std::string orientation = window["Orientation"].string_value();
    if (orientation == "Landscape")
        _orientation = Orientation::LANDSCAPE;
    else
        _orientation = Orientation::PORTRAIT;

    _bitsPerPixel = window["BitsPerPixel"].int_value();

    json11::Json clearColor = window["ClearColor"];
    _clearColor.r(clearColor["R"].number_value());
    _clearColor.g(clearColor["G"].number_value());
    _clearColor.b(clearColor["B"].number_value());
    _clearColor.a(clearColor["A"].number_value());

    json11::Json windowPos = window["Position"];
    _windowPositionX = windowPos["X"].int_value();
    _windowPositionY = windowPos["Y"].int_value();

    json11::Json deviceRes = window["DeviceRes"];
    _deviceWidth = deviceRes["Width"].int_value();
    _deviceHeight = deviceRes["Height"].int_value();

    json11::Json designRes = window["VirtualRes"];
    _virtualWidth = designRes["Width"].int_value();
    _virtualHeight = designRes["Height"].int_value();

    json11::Json engine = jsonObj["Engine"];
    _loopFor = engine["LoopFor"].int_value();
    _engineEnabled = engine["Enabled"].bool_value();
    _showConfig = engine["ShowConfig"].bool_value();
    _showGLInfo = engine["ShowGLInfo"].bool_value();
    _showMonitorInfo = engine["ShowMonitorInfo"].bool_value();
    _showTimingInfo = engine["ShowTimingInfo"].bool_value();
    _GLMajorVersion = engine["GLMajorVersion"].int_value();
    _GLMinorVersion = engine["GLMinorVersion"].int_value();

    json11::Json camera = jsonObj["Camera"];
    json11::Json view = camera["View"];
    _view = {
        static_cast<float>(view["X"].number_value()),
        static_cast<float>(view["Y"].number_value()),
        static_cast<float>(view["Z"].number_value())
    };
    _viewCentered = camera["Centered"].bool_value();

    _FPSRefreshRate = engine["FPSRefreshRate"].number_value();

    json11::Json font = jsonObj["Font"];
    _fontPath = font["Path"].string_value();
    _fontName = font["Name"].string_value();
    _fontSize = font["Size"].int_value();
    _fontScale = font["Scale"].number_value();
    _fontCharsFromSet = font["CharsFromSet"].int_value();

    //std::cout << *this << std::endl;

    _configured = true;
}

void Configuration::flush()
{
    std::ofstream o(_configFile);

    using namespace json11;
    using jO = Json::object;

    Json json;

    if (_deviceWidth == 0 || _deviceHeight == 0) {
        std::cerr << "configuration: "
                  << "Device resolution was bad, using defaults" << std::endl;
        json = _setToDefault();
    } else {
        json = jO{
            { "Window", jO{
                            { "FullScreen", _fullscreen },
                            { "LockToVSync", _lockToVsync },
                            { "Title", _title },
                            { "Orientation", _orientation == Orientation::LANDSCAPE ? "Landscape" : "Portrait" },
                            { "ClearColor", jO{ { "R", _clearColor.r() }, { "G", _clearColor.g() }, { "B", _clearColor.b() }, { "A", _clearColor.a() } } },
                            { "BitsPerPixel", _bitsPerPixel },
                            { "Position", jO{ { "X", _windowPositionX }, { "Y", _windowPositionY } } },
                            { "DeviceRes", jO{ { "Width", _deviceWidth }, { "Height", _deviceHeight } } },
                            { "VirtualRes", jO{ { "Width", _virtualWidth }, { "Height", _virtualHeight } } },
                        } },
            { "Engine", jO{ { "LoopFor", _loopFor }, { "Enabled", _engineEnabled }, { "ShowGLInfo", _showGLInfo }, { "ShowConfig", _showConfig } } }
        };
    }

    o << json.dump();

    o.flush();
}

jO Configuration::_setToDefault()
{
    jO json = jO{
        {
            "Window", jO{
                          { "FullScreen", false }, //
                          { "LockToVSync", true }, //
                          { "Title", "Default title" }, //
                          { "Orientation", "Landscape" }, //
                          { "BitsPerPixel", 24 }, //
                          { "ClearColor", jO{ { "R", 1.0 }, { "G", 0.5 }, { "B", 0.0 }, { "A", 1.0 } } }, //
                          { "Position", jO{ { "X", 0 }, { "Y", 0 } } }, //
                          { "DeviceRes", jO{ { "Width", 1500 }, { "Height", 900 } } }, //
                          { "VirtualRes", jO{ { "Width", 1000 }, { "Height", 600 } } } //
                      } //
        }, //
        {
            "Engine", jO{ //
                          { "LoopFor", -1 }, //
                          { "Enabled", true }, //
                          { "ShowGLInfo", false }, //
                          { "ShowConfig", false } } //
        } //
    };

    return json;
}

//! toString()
std::ostream& operator<<(std::ostream& os, const Configuration& t)
{
    os << endl
       << "configuration: " << endl
       << "-----------------------------------------------------------------" << endl
       << "Engine= " << (t.isEngineEnabled() ? "Enabled" : "Disabled") << endl
       << "FullScreen= " << t.is_fullscreen() << endl
       << "Title= " << t.title() << endl
       << "Orientation= " << (t.orientation() == Orientation::LANDSCAPE ? "Landscape" : "Portrait") << endl
       << "BitsPerPixel= " << t.bitsPerPixel() << endl
       << "Window position= " << t.windowPositionX() << "," << t.windowPositionY() << endl
       << "Device resolution= " << t.deviceResolutionWidth() << " x " << t.deviceResolutionHeight() << endl
       << "Virtual resolution= " << t.virtualWidth() << " x " << t.virtualHeight() << endl
       << "-----------------------------------------------------------------" << endl;

    return os;
}
}
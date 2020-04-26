//
// Created by William DeVore on 3/23/16.
//

#ifndef RANGERALPHA_VIEWPORT_H
#define RANGERALPHA_VIEWPORT_H

#include "../../ranger.h"

namespace Ranger {
class Viewport final {

public:
    void apply();

    void setDimensions(const ConfigurationPtr& config);

    float screenX{ 0.0f };
    float screenY{ 0.0f };

    int width() const
    {
        return _width;
    }

    int height() const
    {
        return _height;
    }

    int screenWidth{};
    int screenHeight{};

protected:
    float _targetAspectRatio{ 1.0f };
    int _x{};
    int _y{};
    int _width{};
    int _height{};
};
}

#endif //RANGERALPHA_VIEWPORT_H

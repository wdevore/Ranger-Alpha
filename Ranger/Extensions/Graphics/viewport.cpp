//
// Created by William DeVore on 3/23/16.
//
#include "viewport.h"
#include <iostream>

#include <GL/glew.h>

#include "../../IO/configuration.h"

namespace Ranger {
void Viewport::apply()
{
    glViewport(_x, _y, _width, _height);
}

void Viewport::setDimensions(const ConfigurationPtr& config)
{
    // These are the physical window size.
    _x = 0.0f;
    _y = 0.0f;
    _width = config->deviceResolutionWidth();
    _height = config->deviceResolutionHeight();
}
}
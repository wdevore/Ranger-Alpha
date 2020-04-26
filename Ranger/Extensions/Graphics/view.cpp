//
// Created by William DeVore on 3/23/16.
//

#include "view.h"

// For: translate
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Ranger {

void View::initialize(float xOffset, float yOffset, float zOffset)
{
    this->xOffset = xOffset;
    this->yOffset = yOffset;
    this->zOffset = zOffset;

    // For this engine x and y are always zero and z is a small negative number like -1.0
    _matrix = glm::translate(_matrix, glm::vec3(xOffset, yOffset, zOffset));

    // We could optionally center the view instead of the projection. But this
    // is not typically done, and it would require design dimensions.
    // Note: if you use this approach then you should not center the projection.
    // _matrix = glm::translate(_matrix, glm::vec3(width/2, height/2, zOffset));
}

void View::initialize(const std::vector<float>& offsets)
{
    initialize(offsets[0], offsets[1], offsets[2]);
}
}
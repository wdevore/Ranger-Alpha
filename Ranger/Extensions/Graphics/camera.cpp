//
// Created by William DeVore on 3/23/16.
//

// For: ortho
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "../../ranger.h"
#include "camera.h"
#include "../../IO/configuration.h"

namespace Ranger {

void Camera::initialize(float ratioCorrection, float bottom, float left, float top, float right)
{
    _ratioCorrection = ratioCorrection;
    this->bottom = bottom;
    this->left = left;
    this->top = top;
    this->right = right;
    this->width = right - left;
    this->height = top - bottom;

    // https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/
    // https://stackoverflow.com/questions/35810782/opengl-view-projections-and-orthographic-aspect-ratio
    //https://stackoverflow.com/questions/10891977/aspect-ratio-stretching-in-opengl
    // https://www.reddit.com/r/opengl/comments/3smigz/having_trouble_with_orthographic_projection/
    //http://www.david-amador.com/2013/04/opengl-2d-independent-resolution-rendering/
    //        _aspectRatio = width / height;
    //        right = right * _aspectRatio;
    //        std::cout << "Camera ratio: " << _aspectRatio << std::endl;
    //        std::cout << "Camera right: " << right << std::endl;
    //        std::cout << "Camera top: " << top << std::endl;

    _matrix = glm::ortho(0.0f, this->width, 0.0f, this->height, 0.1f, 100.0f);
}

// If you choose to center the view then don't call setCentered otherwise you get
// double centering.
void Camera::setCentered()
{
    // _matrix = glm::ortho(-this->width / 2.0f, this->width / 2.0f, -this->height / 2.0f, this->height / 2.0f, 0.1f, 100.0f);

    float left = -width / 2.0f / _ratioCorrection;
    float right = width / 2.0f / _ratioCorrection;
    float bottom = -height / 2.0f / _ratioCorrection;
    float top = height / 2.0f / _ratioCorrection;

    _matrix = glm::ortho(left, right, bottom, top, 0.1f, 100.0f);
}
}
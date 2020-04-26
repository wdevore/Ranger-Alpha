//
// Created by William DeVore on 3/23/16.
//

#ifndef RANGERALPHA_CAMERA_H
#define RANGERALPHA_CAMERA_H

#include <glm/glm.hpp>

// Contains the ortho projection matrix that will be
// sent to shaders. It should only be sent once because shaders
// are stateful.
namespace Ranger {
class Camera {
public:
    void initialize(float ratioCorrection, float bottom, float left, float top, float right);

    void setCentered();

    /** the near clipping plane distance, has to be positive **/
    float near{ 0.1f };
    /** the far clipping plane distance, has to be positive **/
    float far{ 100.0f };

    float left{};
    float right{};
    float bottom{};
    float top{};

    /** the viewport width **/
    float width{};
    /** the viewport height **/
    float height{};

    const glm::mat4& matrix() const
    {
        return _matrix;
    }

    float ratioCorrection() const
    {
        return _ratioCorrection;
    }

private:
    float _ratioCorrection{};
    bool _centered{ true };

    glm::mat4 _matrix;
};
}

#endif //RANGERALPHA_CAMERA_H

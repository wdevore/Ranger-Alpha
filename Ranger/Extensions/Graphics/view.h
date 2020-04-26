//
// Created by William DeVore on 11/11/17.
//

#ifndef RANGERALPHA_VIEW_H
#define RANGERALPHA_VIEW_H

#include <vector>
#include <glm/glm.hpp>

// Contains the ortho projection matrix that will be
// sent to shaders. It should only be sent once because shaders
// are stateful.
namespace Ranger {
    class View {
    public:
        void initialize(float xOffset, float yOffset, float zOffset);
        void initialize(const std::vector<float>& offsets);

        float xOffset{};
        float yOffset{};
        float zOffset{};

        const glm::tmat4x4<float>& matrix() const {
            return _matrix;
        }

    private:
        glm::tmat4x4<float> _matrix;

    };
}

#endif //RANGERALPHA_VIEW_H

//
// Created by William DeVore on 3/19/16.
//

#ifndef RANGERBETA_TRANSFORM_H
#define RANGERBETA_TRANSFORM_H

#include "../Extensions/matrix4.h"

namespace Ranger {
    class Transform {


    public:
        Transform();

        virtual ~Transform() = default;


        const Matrix4<float> &transform() const {
            return _transform;
        }

        const Matrix4<float> &invTransform() const {
            return _invTransform;
        }

    protected:
        Matrix4<float> _transform;
        Matrix4<float> _invTransform;
    };
}

#endif //RANGERBETA_TRANSFORM_H

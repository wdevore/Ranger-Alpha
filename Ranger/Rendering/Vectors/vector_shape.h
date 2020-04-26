//
// Created by William DeVore on 3/9/16.
//

#ifndef RANGERBETA_VECTOR_SHAPE_H
#define RANGERBETA_VECTOR_SHAPE_H


#include <string>

//#include <glm/glm.hpp>

// For some reason CLion isn't passing the include directive for GLM.
// Yet the IDE analyzer sees it. See https://youtrack.jetbrains.com/issue/CPP-6060
#include "../GLObjects/vao.h"
#include "../../Extensions/vector3.h"

namespace Ranger {
    class VectorShape final {

    public:
        VectorShape() = default;

        virtual ~VectorShape() = default;

        std::string name;
        int primitiveType;


        int offset() const {
            return _offset;
        }

        void setOffset(int offset) {
            _offset = offset * sizeof(unsigned int);
        }

        int count;

        // AABBox information
        Vector3<float> minPoint;
        Vector3<float> maxPoint;

        double width() { return maxPoint.x - minPoint.x; }

        double height() { return maxPoint.y - minPoint.y; }

    private:
        // Offset is multiplied by the size of an Unsigned Int in preparation for
        // drawing.
        int _offset;
    };
}

#endif //RANGERBETA_VECTOR_SHAPE_H

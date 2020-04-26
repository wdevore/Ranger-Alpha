//
// Created by William DeVore on 3/24/16.
//

#ifndef RANGERBETA_VECTOR_OBJECT_H
#define RANGERBETA_VECTOR_OBJECT_H

#include "../GLObjects/vao.h"

namespace Ranger {
class VectorObject {
public:
    VectorObject();

    virtual ~VectorObject();

    void construct();

    void use();

    void unUse();

    void release();

    void bind();

    void draw(const VectorShapeSPtr& shape);

    VectorUniformAtlasPtr uAtlas;
    VAO vao;
};
}

#endif //RANGERBETA_VECTOR_OBJECT_H

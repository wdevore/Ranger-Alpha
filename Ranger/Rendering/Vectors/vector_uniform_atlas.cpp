//
// Created by William DeVore on 3/9/16.
//

#include "vector_uniform_atlas.h"

namespace Ranger {
    VectorUniformAtlas::VectorUniformAtlas(bool isStatic) {
        _hasColors = false;
        _isStatic = isStatic;
    }

    void VectorUniformAtlas::add(float x, float y) {
        addVertex(x, y, 0.0f);
        addIndex(_Idx);
    }

    void VectorUniformAtlas::add(float x, float y, float z) {
        addVertex(x, y, z);
        addIndex(_Idx);
    }

    void VectorUniformAtlas::addWithIndex(float x, float y, float z, int i) {
        addVertex(x, y, z);
        addIndex(i);
    }

}
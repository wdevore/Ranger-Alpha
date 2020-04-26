//
// Created by William DeVore on 3/9/16.
//

#include "vector_atlas.h"
#include "../GLObjects/mesh.h"
#include "vector_shape.h"

namespace Ranger {
    VectorAtlas::VectorAtlas() {
    }

    VectorAtlas::~VectorAtlas() {
        std::cout << "~VectorAtlas" << std::endl;
    }

    void VectorAtlas::construct() {
        _mesh = std::make_shared<Mesh>();
        _mesh->construct();
    }

    int VectorAtlas::addVertex(float x, float y, float z) {
        _mesh->vertices.push_back(x);
        _mesh->vertices.push_back(y);
        _mesh->vertices.push_back(z);

        _vertexIdx += _vertexSize;
        int c = _componentCount++;
        return c;
    }

    void VectorAtlas::addIndex(int i) {
        _mesh->indices.push_back(i);
        // TODO this ++ should really find the max index and assign to _Idx.
        _Idx++;
    }

    int VectorAtlas::begin() {
        _prevComponentCount = _componentCount;
        _prevIndexCount = _Idx;
        return _prevIndexCount;
    }

    int VectorAtlas::end() {
        //int count = _componentCount - _prevComponentCount;
        int count = _Idx - _prevIndexCount;
        return count;
    }
}
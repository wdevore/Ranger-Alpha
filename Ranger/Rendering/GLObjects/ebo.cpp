//
// Created by William DeVore on 3/13/16.
//

#include "ebo.h"

#include "mesh.h"

namespace Ranger {
    void EBO::construct() {
    }

    void EBO::gen() {
        if (!_genBound) {
            glGenBuffers(1, &_eboId);
            _genBound = true;
        }
    }

    void EBO::bind(const MeshSPtr &mesh) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), &mesh->indices[0], GL_STATIC_DRAW);
    }
}

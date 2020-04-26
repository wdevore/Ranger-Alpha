//
// Created by William DeVore on 3/13/16.
//

#include "vbo.h"
#include "mesh.h"

namespace Ranger {
void VBO::construct()
{
}

void VBO::gen()
{
    if (!_genBound) {
        glGenBuffers(1, &_vboId);
        _genBound = true;
    }
}

void VBO::bind(const MeshSPtr& mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(GLfloat), &mesh->vertices[0], GL_STATIC_DRAW);
}
}

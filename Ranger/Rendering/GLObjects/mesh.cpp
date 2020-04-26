//
// Created by William DeVore on 3/11/16.
//

#include "mesh.h"
#include "../Vectors/vector_shape.h"

namespace Ranger {
    void Mesh::construct() {
        vbo.construct();
        ebo.construct();

    }

    void Mesh::bind() {
        vbo.bind(shared_from_this());
        ebo.bind(shared_from_this());
    }

    void Mesh::gen() {
        vbo.gen();
        ebo.gen();
    }
}


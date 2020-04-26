//
// Created by William DeVore on 3/11/16.
//

#ifndef RANGERBETA_MESH_H
#define RANGERBETA_MESH_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <vector>
#include "vbo.h"
#include "ebo.h"

namespace Ranger {
    class Mesh final : public std::enable_shared_from_this<Mesh> {

    public:
        Mesh() = default;

        virtual ~Mesh() {
            std::cout << "~Mesh" << std::endl;
        };

        void construct();

        void gen();

        void bind();

        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        VBO vbo;
        EBO ebo;
    };
}

#endif //RANGERBETA_MESH_H

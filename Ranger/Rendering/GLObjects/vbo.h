//
// Created by William DeVore on 3/13/16.
//

#ifndef RANGERBETA_VBO_H
#define RANGERBETA_VBO_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <iostream>
#include "../../ranger.h"

namespace Ranger {
    class VBO final {

    public:
        VBO() = default;

        virtual ~VBO() {
            if (_genBound)
                glDeleteBuffers(1, &_vboId);
            std::cout << "~VBO" << std::endl;
        }

        void construct();

        void gen();
        void bind(const MeshSPtr &mesh);

    private:
        // Indicate if an Id has been generated yet.
        bool _genBound = false;

        GLuint _vboId;
    };
}

#endif //RANGERBETA_VBO_H

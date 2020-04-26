//
// Created by William DeVore on 3/13/16.
//

#ifndef RANGERBETA_EBO_H
#define RANGERBETA_EBO_H


#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "../../ranger.h"

namespace Ranger {
    class Mesh;

    class EBO final {   // aka IBO

    public:
        EBO() = default;

        virtual ~EBO() {
            if (_genBound)
                glDeleteBuffers(1, &_eboId);
            std::cout << "~EBO" << std::endl;
        }

        void construct();

        void gen();
        void bind(const MeshSPtr &mesh);

    private:
        // Indicate if an Id has been generated yet.
        bool _genBound = false;
        GLuint _eboId;
    };
}


#endif //RANGERBETA_EBO_H

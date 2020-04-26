//
// Created by William DeVore on 3/13/16.
//

#ifndef RANGERBETA_VAO_H
#define RANGERBETA_VAO_H

// #define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
// #include <vector>
#include "../../ranger.h"

namespace Ranger {

class VAO final {
public:
    VAO();

    virtual ~VAO()
    {
        if (_genBound)
            glDeleteVertexArrays(1, &_vaoId);
        std::cout << "~VAO" << std::endl;
    }

    void construct(const MeshSPtr& mesh);

    void release();

    void bind();
    void use();
    void unUse();

    //! Use this more often than the draw methods.
    void render(const VectorShapeSPtr& shape);

    // Rarely used, but could be useful.
    void draw(const VectorShapeSPtr& shape);
    void draw(int primitiveType, int offset, int count);

private:
    static constexpr const int XYZ_Component_count = 3;

    // Indicate if an Id has been generated yet.
    bool _genBound = false;

    GLuint _vaoId;
    MeshSPtr _mesh;
};
}

#endif // RANGERBETA_VAO_H

//
// Created by William DeVore on 3/13/16.
//

#include "vao.h"
#include "../../Rendering/Vectors/vector_shape.h"
#include "mesh.h"

namespace Ranger {
    VAO::VAO() {
    }

    void VAO::construct(const MeshSPtr &mesh) {
        // Note: what ever object calls this method must also call release() too in order
        // to avoid leaks.
        _mesh = mesh;
    }

    void VAO::release() {
        _mesh = nullptr;
    }

    void VAO::bind() {
        if (!_genBound) {
            glGenVertexArrays(1, &_vaoId);
            _genBound = true;
        }

        _mesh->gen();

        // Bind the Vertex Array Object first, then bind and set vertex buffer(s)
        // and attribute pointer(s).
        glBindVertexArray(_vaoId);

        _mesh->bind();

        glVertexAttribPointer(0, XYZ_Component_count, GL_FLOAT, GL_FALSE, XYZ_Component_count * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(0);

        // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound
        // vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs),
        // remember: do NOT unbind the EBO, keep it bound to this VAO
        glBindVertexArray(0);
    }


    void VAO::draw(const VectorShapeSPtr &shape) {
        use();

        render(shape);

        unUse();
    }

    void VAO::draw(int primitiveType, int offset, int count) {
        glBindVertexArray(_vaoId);
        glDrawElements(primitiveType, count, GL_UNSIGNED_INT, (const GLvoid*)(offset));
        glBindVertexArray(0);
    }

    void VAO::use() {
        glBindVertexArray(_vaoId);
    }

    void VAO::unUse() {
        // See opengl wiki as to why "glBindVertexArray(0)" isn't really necessary here:
        // https://www.opengl.org/wiki/Vertex_Specification#Vertex_Buffer_Object
        // Note the line "Changing the GL_ARRAY_BUFFER binding changes nothing about vertex attribute 0..."
        glBindVertexArray(0);
    }

    void VAO::render(const VectorShapeSPtr &shape) {
        // The signature of glDrawElements was defined back before there were buffer objects;
        // originally you'd pass an actual pointer to data in a client-side vertex array.
        // When device-side buffers were introduced, this function was extended to support them
        // as well, by shoehorning a buffer offset into the address argument.
        // Because we are using VBOs we need to awkwardly cast the offset value into a
        // pointer to void.
        // If we weren't using VBOs then we would use client-side addresses: &_mesh->indices[offset]

        // Rather than multiply repeatedly
        //glDrawElements(_shape->primitiveType, _shape->count, GL_UNSIGNED_INT, (const GLvoid*)(_shape->offset * sizeof(unsigned int)));
        // we use a pre computed version.
        glDrawElements(shape->primitiveType, shape->count, GL_UNSIGNED_INT, (const GLvoid*)(shape->offset()));
    }


}

//
// Created by William DeVore on 3/9/16.
//

#ifndef RANGERBETA_VECTOR_ATLAS_H
#define RANGERBETA_VECTOR_ATLAS_H


#include <vector>
#include "../../Components/stage.h"
#include "../../ranger.h"

namespace Ranger {
    class VectorAtlas {

    public:
        VectorAtlas();

        virtual ~VectorAtlas();

        int addVertex(float x, float y, float z);

        void addIndex(int i);

        int begin();

        int end();

        void construct();

        const MeshSPtr &mesh() const {
            return _mesh;
        }

    protected:
        bool _hasNormals = false;
        bool _hasColors = true;
        bool _isStatic = true;

        int _vertexIdx = 0;
        int _vertexSize = 0;

        int _prevComponentCount = 0;
        int _componentCount = 0;

        int _Idx = 0;
        int _prevIndexCount = 0;

        // TODO: consider change to a unique_ptr and using option C as
        // described by this article:
        // http://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
        MeshSPtr _mesh;
    };
}

#endif //RANGERBETA_VECTOR_ATLAS_H

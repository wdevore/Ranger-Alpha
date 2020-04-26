//
// Created by William DeVore on 3/9/16.
//

#ifndef RANGERBETA_VECTOR_UNIFORM_ATLAS_H
#define RANGERBETA_VECTOR_UNIFORM_ATLAS_H


#include "vector_atlas.h"
#include "../../Components/stage.h"
#include "../../ranger.h"

namespace Ranger {
    class VectorUniformAtlas final : public VectorAtlas {
    public:
        VectorUniformAtlas() { }

        virtual ~VectorUniformAtlas() = default;

        VectorUniformAtlas(bool isStatic);

        void add(float x, float y);
        void add(float x, float y, float z);

        void addWithIndex(float x, float y, float z, int i);
    };
}

#endif //RANGERBETA_VECTOR_UNIFORM_ATLAS_H

//
// Created by William DeVore on 3/9/16.
//

#ifndef RANGERBETA_UNIFORM_ATLAS_H
#define RANGERBETA_UNIFORM_ATLAS_H


#include <unordered_map>
#include <iostream>
#include "atlas.h"
#include "../../ranger.h"

namespace Ranger {
    class UniformAtlas final : public Atlas {

    public:

        UniformAtlas();

        virtual ~UniformAtlas() { std::cout << "~UniformAtlas" << std::endl; };

        virtual void construct(const VectorObjectSPtr& vo) override;


    private:
        void _buildSquare();

        void _buildCenteredSquare();

        void _buildCenteredTriangle();

        void _buildSolidCircle(int segments);

        void _buildHollowCircle(int segments);

        void _buildPlus();

        void _buildCross();

        void _buildLine();

    };
}

#endif //RANGERBETA_UNIFORM_ATLAS_H

//
// Created by William DeVore on 3/13/16.
//

#ifndef RANGERBETA_BASIC_SHAPES_H
#define RANGERBETA_BASIC_SHAPES_H

#include "../atlas.h"
#include <iostream>

namespace Ranger {
class BasicShapes final : public Atlas {
public:
    BasicShapes();

    virtual ~BasicShapes();

    // ------------------------------------------------------------------
    // Atlas overrides
    // ------------------------------------------------------------------
    virtual void construct(const VectorObjectSPtr& vo) override;

    void release() override;

    //        void bind();

    //        void use();
    //
    //        void unUse();

    //! Simple draw
    //        void draw(const VectorShapeSPtr &shape);

    // ------------------------------------------------------------------
    // Complex Drawing
    // ------------------------------------------------------------------

private:
    void _build_Square();
    void _build_CenteredSquare();

    void _build_CenteredTriangle();
};
}

#endif //RANGERBETA_BASIC_SHAPES_H

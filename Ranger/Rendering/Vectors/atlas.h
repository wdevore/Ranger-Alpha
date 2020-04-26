//
// Created by William DeVore on 3/9/16.
//

#ifndef RANGERALPHA_ATLAS_H
#define RANGERALPHA_ATLAS_H

#include "../../ranger.h"
#include "../GLObjects/vao.h"
#include <string>
#include <unordered_map>

namespace Ranger {
class Atlas {
public:
    Atlas() = default;

    virtual ~Atlas();

    //        virtual VectorUniformAtlasSPtr atlas();

    virtual const VectorShapeSPtr& shape(std::string name);

    virtual void construct(const VectorObjectSPtr& vo);

    virtual void release();

    virtual void markDirty(){};

    virtual void addShape(const VectorShapeSPtr& shape);

protected:
    std::unordered_map<std::string, VectorShapeSPtr> _shapes;

    VectorObjectSPtr _vo;

    //        VectorUniformAtlasSPtr _uAtlas;
    //
    //        VAO _vao;
};
}

#endif //RANGERALPHA_ATLAS_H

//
// Created by William DeVore on 3/15/16.
//

#include "atlas.h"
#include "../../ranger.h"
#include "vector_shape.h"
//#include "vector_atlas.h"
//#include "vector_uniform_atlas.h"

namespace Ranger {
//    VectorUniformAtlasSPtr Atlas::atlas() {
//        return _uAtlas;
//    }

const VectorShapeSPtr& Atlas::shape(std::string name) { return _shapes[name]; }

void Atlas::addShape(const VectorShapeSPtr& shape)
{
    _shapes[shape->name] = shape;
}

void Atlas::release()
{
    // Release all shapes.
    std::cout << "Atlas::releasing" << std::endl;

    //        std::for_each(_shapes.begin(), _shapes.end(),
    //                      [](const std::unordered_map<std::string, VectorShapeSPtr>::value_type &p) {
    //                          std::cout << "Releasing shape: " << p.first << std::endl;
    //                          p.second->release();
    //                      });
}

Atlas::~Atlas()
{
    std::cout << "Atlas::~Atlas" << std::endl;
    release();
}

void Atlas::construct(const VectorObjectSPtr& vo)
{
    _vo = vo;
    //        _uAtlas = std::make_shared<VectorUniformAtlas>();
    //        _uAtlas->construct();
    //
    //        _vao.construct(_uAtlas->mesh());
}
}
//
// Created by William DeVore on 3/24/16.
//

#include "vector_object.h"
#include "vector_atlas.h"
#include "vector_shape.h"
#include "vector_uniform_atlas.h"

namespace Ranger {
VectorObject::VectorObject() {}
VectorObject::~VectorObject() { std::cout << "~VectorObject" << std::endl; }

void VectorObject::construct()
{
    uAtlas = std::make_unique<VectorUniformAtlas>();
    uAtlas->construct();

    vao.construct(uAtlas->mesh());
}

void VectorObject::use()
{
    vao.use();
}

void VectorObject::unUse()
{
    vao.unUse();
}

void VectorObject::release()
{
    vao.release();
}

void VectorObject::bind()
{
    vao.bind();
}

void VectorObject::draw(const VectorShapeSPtr& shape)
{
    vao.render(shape);
}
}
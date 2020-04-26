//
// Created by William DeVore on 3/13/16.
//

#define GLEW_STATIC
#include <GL/glew.h>

#include "../vector_object.h"
#include "../vector_shape.h"
#include "../vector_uniform_atlas.h"
#include "basic_shapes.h"

namespace Ranger {
BasicShapes::BasicShapes()
{
}

BasicShapes::~BasicShapes()
{
    release();
    std::cout << "~BasicShapes" << std::endl;
};

void BasicShapes::construct(const VectorObjectSPtr& vo)
{
    Atlas::construct(vo);

    _build_Square();
    _build_CenteredSquare();
    _build_CenteredTriangle();
}

//    void BasicShapes::bind() {
//        std::for_each(_shapes.begin(), _shapes.end(),
//                      [](const std::unordered_map<std::string, VectorShapeSPtr>::value_type &p) {
//                          //std::cout << "Binding shape: " << p.first << std::endl;
//                          p.second->bind();
//                      });
//    }

void BasicShapes::release()
{
    //        _vo->vao.release();
    //        _vao.release();
}
//
//    void BasicShapes::bind() {
//        _vao.bind();
//    }
//
//    void BasicShapes::draw(const VectorShapeSPtr &shape) {
//        _vao.render(shape);
//    }

// Origin is at the bottom left
void BasicShapes::_build_Square()
{
    VectorShapeSPtr s = std::make_shared<VectorShape>();
    s->name = "Square";
    s->primitiveType = GL_TRIANGLES;

    s->setOffset(_vo->uAtlas->begin());
    int v0 = _vo->uAtlas->addVertex(0.0f, 0.0f, 0.0f);
    int v1 = _vo->uAtlas->addVertex(0.0f, 1.0f, 0.0f);
    int v2 = _vo->uAtlas->addVertex(1.0f, 1.0f, 0.0f);
    int v3 = _vo->uAtlas->addVertex(1.0f, 0.0f, 0.0f);

    // These indices are specified locally to the shape
    _vo->uAtlas->addIndex(v0);
    _vo->uAtlas->addIndex(v1);
    _vo->uAtlas->addIndex(v3);
    _vo->uAtlas->addIndex(v1);
    _vo->uAtlas->addIndex(v2);
    _vo->uAtlas->addIndex(v3);

    s->count = _vo->uAtlas->end();

    addShape(s);
}

void BasicShapes::_build_CenteredSquare()
{
    VectorShapeSPtr s = std::make_shared<VectorShape>();
    s->name = "CenteredSquare";
    s->primitiveType = GL_TRIANGLES;

    s->setOffset(_vo->uAtlas->begin());
    float l = 0.5f;
    int v0 = _vo->uAtlas->addVertex(l, l, 0.0f); //3
    int v1 = _vo->uAtlas->addVertex(l, -l, 0.0f); //4
    int v2 = _vo->uAtlas->addVertex(-l, -l, 0.0f); //5
    int v3 = _vo->uAtlas->addVertex(-l, l, 0.0f); //6

    // These indices are specified locally to the shape
    _vo->uAtlas->addIndex(v0);
    _vo->uAtlas->addIndex(v3);
    _vo->uAtlas->addIndex(v1);
    _vo->uAtlas->addIndex(v1);
    _vo->uAtlas->addIndex(v3);
    _vo->uAtlas->addIndex(v2);

    s->count = _vo->uAtlas->end();

    addShape(s);
}

void BasicShapes::_build_CenteredTriangle()
{
    VectorShapeSPtr s = std::make_shared<VectorShape>();
    s->name = "CenteredTriangle";
    s->primitiveType = GL_TRIANGLES;

    // 30 degrees yields triangle sides of equal length but the bbox is
    // rectangular not square.
    // 0 degrees yields a square bbox with unequal triangle sides.
    float h = 0.5f * cos(Math::toRadians(30.0f));

    s->setOffset(_vo->uAtlas->begin());
    float l = 0.25f;
    int v0 = _vo->uAtlas->addVertex(-l, -h, 0.0f); //0
    int v1 = _vo->uAtlas->addVertex(l, -h, 0.0f); //1
    int v2 = _vo->uAtlas->addVertex(0.0f, h, 0.0f); //2

    _vo->uAtlas->addIndex(v0);
    _vo->uAtlas->addIndex(v1);
    _vo->uAtlas->addIndex(v2);
    s->count = _vo->uAtlas->end();

    s->minPoint.x = -l;
    s->minPoint.y = -h;
    s->maxPoint.x = l;
    s->maxPoint.y = h;

    addShape(s);
}

//    void BasicShapes::use() {
//        _vao.use();
//    }
//
//    void BasicShapes::unUse() {
//        _vao.unUse();
//    }
}

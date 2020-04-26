//
// Created by William DeVore on 3/9/16.
//
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "uniform_atlas.h"
#include "vector_atlas.h"
#include "vector_uniform_atlas.h"
#include "vector_shape.h"
#include "vector_object.h"


namespace Ranger {
    UniformAtlas::UniformAtlas() {
//        _uAtlas = std::make_shared<VectorUniformAtlas>(true);
    }

    void UniformAtlas::construct(const VectorObjectSPtr& vo) {
        Atlas::construct(vo);

        _buildSquare();
        _buildCenteredSquare();
        _buildCenteredTriangle();

        _buildSolidCircle(6);
        _buildHollowCircle(6);

        _buildSolidCircle(8);

        _buildSolidCircle(16);
        _buildHollowCircle(16);

        _buildSolidCircle(32);

        _buildSolidCircle(64);
        _buildHollowCircle(64);

        _buildPlus();
        _buildCross();
        _buildLine();
    }

    void UniformAtlas::_buildSquare() {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();
        shape->name = "Square";
        shape->primitiveType = GL_LINE_LOOP;

        shape->setOffset(_vo->uAtlas->begin());
        _vo->uAtlas->add(0.0f, 0.0f);
        _vo->uAtlas->add(1.0f, 0.0f);
        _vo->uAtlas->add(1.0f, 1.0f);
        _vo->uAtlas->add(0.0f, 1.0f);
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = 0.0f;
        shape->minPoint.y = 0.0f;

        shape->maxPoint.x = 1.0f;
        shape->maxPoint.y = 1.0f;

        addShape(shape);
    }

    void UniformAtlas::_buildCenteredSquare() {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();
        shape->name = "CenteredSquare";
        shape->primitiveType = GL_LINE_LOOP;

        shape->setOffset(_vo->uAtlas->begin());
        _vo->uAtlas->add(-0.5f, -0.5f);
        _vo->uAtlas->add(0.5f, -0.5f);
        _vo->uAtlas->add(0.5f, 0.5f);
        _vo->uAtlas->add(-0.5f, 0.5f);
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = -0.5f;
        shape->minPoint.y = -0.5f;
        shape->maxPoint.x = 0.5f;
        shape->maxPoint.y = 0.5f;

        addShape(shape);
    }

    void UniformAtlas::_buildCenteredTriangle() {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();
        shape->name = "CenteredTriangle";
        shape->primitiveType = GL_TRIANGLES;

        // 30 degrees yields triangle sides of equal length but the bbox is
        // rectangular not square.
        // 0 degrees yields a square bbox with unequal triangle sides.
        float h = 0.5f * cos(Math::toRadians(30.0f));

        shape->setOffset(_vo->uAtlas->begin());
        _vo->uAtlas->add(-0.5f, -h);
        _vo->uAtlas->add(0.5f, -h);
        _vo->uAtlas->add(0.0f, h);
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = -0.5f;
        shape->minPoint.y = -h;
        shape->maxPoint.x = 0.5f;
        shape->maxPoint.y = h;

        addShape(shape);
    }

    void UniformAtlas::_buildSolidCircle(int segments) {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();

        std::stringstream ss;
        ss << segments;
        shape->name = "Circle" + ss.str();

        shape->setOffset(_vo->uAtlas->begin());
        shape->primitiveType = GL_TRIANGLE_FAN;

        _vo->uAtlas->add(0.0f, 0.0f); // Center of fan-out

        float angleStep = 2 * Math::PI / segments;
        float angle = 0.0f;
        float radius = 0.5f;

        for (int i = 0; i < segments; i++) {
            _vo->uAtlas->add(radius * cos(angle), radius * sin(angle));
            angle += angleStep;
        }

        _vo->uAtlas->add(radius * cos(0.0f), radius * sin(0.0f));

        shape->minPoint.x = -0.5f;
        shape->minPoint.y = -0.5f;
        shape->maxPoint.x = 0.5f;
        shape->maxPoint.y = 0.5f;

        shape->count = _vo->uAtlas->end();
        addShape(shape);
    }

    void UniformAtlas::_buildHollowCircle(int segments) {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();

        std::stringstream ss;
        ss << segments;
        shape->name = "HollowCircle" + ss.str();
        shape->primitiveType = GL_LINE_LOOP;

        float angleStep = 2 * Math::PI / segments;
        float angle = 0.0f;
        float radius = 0.5f;

        shape->setOffset(_vo->uAtlas->begin());
        for (int i = 0; i < segments; i++) {
            _vo->uAtlas->add(radius * cos(angle), radius * sin(angle));
            angle += angleStep;
        }
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = -0.5f;
        shape->minPoint.y = -0.5f;
        shape->maxPoint.x = 0.5f;
        shape->maxPoint.y = 0.5f;

        addShape(shape);
    }

    void UniformAtlas::_buildPlus() {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();
        shape->name = "Plus";
        shape->primitiveType = GL_LINES;

        shape->setOffset(_vo->uAtlas->begin());
        _vo->uAtlas->add(-0.5f, 0.0f);
        _vo->uAtlas->add(0.5f, 0.0f);
        _vo->uAtlas->add(0.0f, 0.5f);
        _vo->uAtlas->add(0.0f, -0.5f);
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = -0.5f;
        shape->minPoint.y = -0.5f;
        shape->maxPoint.x = 0.5f;
        shape->maxPoint.y = 0.5f;

        addShape(shape);
    }

    void UniformAtlas::_buildCross() {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();
        shape->name = "Cross";
        shape->primitiveType = GL_LINES;

        shape->setOffset(_vo->uAtlas->begin());
        _vo->uAtlas->add(-0.5f, -0.5f);
        _vo->uAtlas->add(0.5f, 0.5f);
        _vo->uAtlas->add(-0.5f, 0.5f);
        _vo->uAtlas->add(0.5f, -0.5f);
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = -0.5f;
        shape->minPoint.y = -0.5f;
        shape->maxPoint.x = 0.5f;
        shape->maxPoint.y = 0.5f;

        addShape(shape);
    }

    // Unit X axis line
    void UniformAtlas::_buildLine() {
        VectorShapeSPtr shape = std::make_shared<VectorShape>();
        shape->name = "Line";
        shape->primitiveType = GL_LINES;

        shape->setOffset(_vo->uAtlas->begin());
        _vo->uAtlas->add(0.0f, 0.0f);
        _vo->uAtlas->add(1.0f, 0.0f);
        shape->count = _vo->uAtlas->end();

        shape->minPoint.x = 0.0f;
        shape->minPoint.y = 0.0f;
        shape->maxPoint.x = 1.0f;
        shape->maxPoint.y = 0.0f;

        addShape(shape);
    }

}
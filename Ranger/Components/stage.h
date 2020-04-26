//
// Created by William DeVore on 3/9/16.
//

#ifndef RANGERBETA_STAGE_H
#define RANGERBETA_STAGE_H

#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

#include "../ranger.h"
#include "scene_manager.h"

namespace Ranger {
class Stage final {
public:
    Stage();

    ~Stage() { std::cout << "Stage::~Stage" << std::endl; };

    void construct(float width, float height);

    float farRange{ 5000.0f };

    bool step();

    //   const DecimalNumbersSPtr &digitFont() const { return _digits; }

private:
    VectorShapeSPtr _shapeS;
    VectorShapeSPtr _shapeCS;
    VectorShapeSPtr _shapeT;

    //   DecimalNumbersSPtr _digits;
    BasicShapesSPtr _basicShapes;

    VectorObjectSPtr _vo;

    ShaderSPtr _basicShader;
    
    std::unique_ptr<SceneManager> _sceneManager;

    glm::mat4 _vp;

    // Hacking for fun
    float _angle{ 0.0f };
    glm::vec3 _pos{};
    float _incX{ 1.0f };

    GLuint _mvpLoc;
    GLuint _colorLoc;
    void _animateSquare();
    void _drawVirtualBg();
    void _drawFPS();
    void _drawLowerLeftSquare();
    void _drawUpperRightSquare();
    void _drawSquareAt(float x, float y);

    // Debugging stuff
    std::ostringstream _osFPS;
    std::ostringstream _osUpdate;
    std::ostringstream _osRender;
};
}

#endif // RANGERBETA_STAGE_H

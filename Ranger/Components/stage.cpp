//
// Created by William DeVore on 3/9/16.
//
#include <iomanip>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stage.h"

#include "../Extensions/Graphics/view.h"
#include "../GLFW/window.h"
#include "../IO/configuration.h"
#include "../Rendering/Shaders/basic_shader.h"
#include "../Rendering/Vectors/Shapes/basic_shapes.h"
#include "../Rendering/Vectors/vector_object.h"
#include "../Rendering/freetypefont.h"
#include "../Rendering/rendercontext.h"
#include "../engine.h"

namespace Ranger {
Stage::Stage()
{
    _osUpdate << std::fixed << std::setw(8) << std::setfill('0') << std::right << std::setprecision(4);
    _osRender << std::fixed << std::setw(8) << std::setfill('0') << std::setprecision(4);
}

void Stage::construct(float width, float height)
{
    _sceneManager = std::make_unique<SceneManager>();

    _vo = std::make_shared<VectorObject>();
    _vo->construct();

    _basicShapes = std::make_shared<BasicShapes>();
    _basicShapes->construct(_vo);

    //        _digits = std::make_shared<DecimalNumbers>();
    //        _digits->construct(_vo);

    _vo->bind();

    _shapeS = _basicShapes->shape("Square");
    _shapeCS = _basicShapes->shape("CenteredSquare");
    _shapeT = _basicShapes->shape("CenteredTriangle");

    _basicShader = std::make_shared<BasicShader>();
    _basicShader->load();

    const EnginePtr& engine = App::engine();

    _vp = engine->camera().matrix() * engine->view().matrix();

    // just playing around
    _pos.x = -200.0f;

    _mvpLoc = glGetUniformLocation(_basicShader->program(), "mvp");
    _colorLoc = glGetUniformLocation(_basicShader->program(), "fragColor");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Stage::step()
{
    _basicShader->use();
    _vo->use();

    _drawVirtualBg();

    _animateSquare();
    _drawLowerLeftSquare();
    _drawUpperRightSquare();
    _drawSquareAt(450.0f, 100.0f);

    // _sceneManager->step();

    _vo->unUse();

    //  Temporary fps display. This will move to the overlay layer when ready.
    _drawFPS();

    return true;
}

void Stage::_drawFPS()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    const RenderContextPtr& renderer = App::renderContext();
    const ConfigurationPtr& config = App::config();
    const EnginePtr& engine = App::engine();
    glm::vec3 white{ 1.0f, 1.0f, 1.0f };

    _osFPS.str("");
    _osFPS << "fps: " << std::to_string(engine->fps());

    float svx = static_cast<float>(config->virtualWidth());
    float svy = static_cast<float>(config->virtualHeight());
    float fontScale = config->fontScale();

    float lowerLeftAnchorX = -svx / 2.0f + 5.0f;
    float lowerLeftAnchorY = -svy / 2.0f;

    _osUpdate.str("");
    _osUpdate << "u: " << std::fixed << std::setw(7) << std::setfill('0') << std::right << std::setprecision(4) << (1000.0f * engine->updateDelta());

    _osRender.str("");
    _osRender << "r: " << std::fixed << std::setw(7) << std::setfill('0') << std::right << std::setprecision(4) << (1000.0f * engine->renderDelta());

    renderer->freeTypeFont()->renderText(_vp, _osUpdate.str(), lowerLeftAnchorX, lowerLeftAnchorY + 40.0f, fontScale, white);
    renderer->freeTypeFont()->renderText(_vp, _osRender.str(), lowerLeftAnchorX, lowerLeftAnchorY + 25.0f, fontScale, white);
    renderer->freeTypeFont()->renderText(_vp, _osFPS.str(), lowerLeftAnchorX, lowerLeftAnchorY + 10.0f, fontScale, white);
}

void Stage::_drawSquareAt(float x, float y)
{
    glm::mat4 mvp;

    glm::mat4 model;
    const ConfigurationPtr& config = App::config();

    float svx = static_cast<float>(config->virtualWidth());
    float svy = static_cast<float>(config->virtualHeight());

    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(25.0f, 25.0f, 1.0f));

    mvp = _vp * model;
    glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glm::vec3 color = glm::vec3(0.0f, 1.0f, 1.0f);
    glUniform3fv(_colorLoc, 1, glm::value_ptr(color));

    _vo->draw(_shapeCS);
}

void Stage::_drawVirtualBg()
{
    glm::mat4 mvp;

    glm::mat4 model;
    const ConfigurationPtr& config = App::config();

    float svx = static_cast<float>(config->virtualWidth());
    float svy = static_cast<float>(config->virtualHeight());

    model = glm::translate(model, glm::vec3(-svx / 2.0f, -svy / 2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(svx, svy, 1.0f));

    mvp = _vp * model;
    glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
    glUniform3fv(_colorLoc, 1, glm::value_ptr(color));

    _vo->draw(_shapeS);
}

void Stage::_drawLowerLeftSquare()
{
    glm::mat4 mvp;

    glm::mat4 model;
    const ConfigurationPtr& config = App::config();

    float s = 50.0f;
    float svx = static_cast<float>(config->virtualWidth());
    float svy = static_cast<float>(config->virtualHeight());

    model = glm::translate(model, glm::vec3(-svx / 2.0f, -svy / 2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(s, s, 1.0f));

    mvp = _vp * model;
    glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
    glUniform3fv(_colorLoc, 1, glm::value_ptr(color));

    _vo->draw(_shapeS);
}

void Stage::_drawUpperRightSquare()
{
    glm::mat4 mvp;

    glm::mat4 model;
    const ConfigurationPtr& config = App::config();

    float s = 50.0f;
    float svx = static_cast<float>(config->virtualWidth());
    float svy = static_cast<float>(config->virtualHeight());

    model = glm::translate(model, glm::vec3(svx / 2.0f - (s), svy / 2.0f - (s), 0.0f));
    model = glm::scale(model, glm::vec3(s, s, 1.0f));

    mvp = _vp * model;
    glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
    glUniform3fv(_colorLoc, 1, glm::value_ptr(color));

    _vo->draw(_shapeS);
}
void Stage::_animateSquare()
{
    glm::mat4 mvp;

    glm::mat4 model;
    // transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    // model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
    // model = glm::translate(model, glm::vec3(250.0f, 50.0f, 0.0f));
    _pos.x += _incX;
    if (_pos.x > 199.0f) {
        _pos.x = 200.0f;
        _incX = -1.0f;
    } else if (_pos.x < -199.0f) {
        _pos.x = -200.0f;
        _incX = 1.0f;
    }
    model = glm::translate(model, _pos);

    _angle += 0.5f;
    if (_angle == 360.0f)
        _angle = 0.0f;
    model = glm::rotate(model, glm::radians(_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(200.0f, 200.0f, 1.0f));
    // float sx = 1500.0f / 1000.0f;
    // float sy = 900.0f / 600.0f;
    // model = glm::scale(model, glm::vec3(sx, sy, 1.0f));

    mvp = _vp * model;
    glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glm::vec3 color = glm::vec3(0.9f, 0.0f, 0.9);
    glUniform3fv(_colorLoc, 1, glm::value_ptr(color));

    _vo->draw(_shapeCS);
}
}

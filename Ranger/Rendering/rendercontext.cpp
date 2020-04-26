//
// Created by William DeVore on 11/14/15.
//
#define GLEW_STATIC

#include <GL/glew.h>

#include <iostream>

#include "rendercontext.h"

namespace Ranger {
    RenderContext::~RenderContext() {
        std::cout << "RenderContext::~RenderContext" << std::endl;
    }

    bool RenderContext::initialize() {
        _ftFont = std::make_unique<FreeTypeFont>();

        if (_ftFont == nullptr) {
            std::cout << "Failed to construct FreeTypeFont class" << std::endl;
            return false;
        }

        return _ftFont->initialize();
    }

    void RenderContext::clearColor(float r, float g, float b, float a) {
        _clearColor.set(r, g, b, a);
        glClearColor(_clearColor.r(), _clearColor.g(), _clearColor.b(), _clearColor.a());
    }

    void RenderContext::clearColor(const Color& clearColor) {
        _clearColor.set(clearColor);
        glClearColor(_clearColor.r(), _clearColor.g(), _clearColor.b(), _clearColor.a());
    }

    void RenderContext::clear() {
        //int r = rand();
        //glClearColor(r % 255 / 255.0f,r % 128 / 255.0f,0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void RenderContext::pre() {
    }

    void RenderContext::post() {

    }

}
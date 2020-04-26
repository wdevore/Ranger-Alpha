//
// Created by William DeVore on 11/14/15.
//

#ifndef RANGERALPHA_RENDERCONTEXT_H
#define RANGERALPHA_RENDERCONTEXT_H

#include "color.h"
#include "freetypefont.h"
#include <memory>

namespace Ranger {
class RenderContext final {

public:
    ~RenderContext();

    bool initialize();

    void clear();

    void pre();

    void post();

    void clearColor(float r, float g, float b, float a);

    void clearColor(const Color& clearColor);

    const std::unique_ptr<FreeTypeFont>& freeTypeFont()
    {
        return _ftFont;
    }

private:
    Color _clearColor{ Color::Orange() };

    std::unique_ptr<FreeTypeFont> _ftFont;
};
}

#endif //RANGERALPHA_RENDERCONTEXT_H

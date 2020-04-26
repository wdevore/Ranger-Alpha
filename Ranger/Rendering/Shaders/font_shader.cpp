//
// Created by William DeVore on 3/11/16.
//

#include "font_shader.h"

namespace Ranger {
void FontShader::load()
{
    _load("Ranger/Rendering/Shaders/font.vs", "Ranger/Rendering/Shaders/font.frag");
}

void FontShader::postUse()
{
}
}

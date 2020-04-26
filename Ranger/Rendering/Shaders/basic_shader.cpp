//
// Created by William DeVore on 3/11/16.
//

#include "basic_shader.h"

namespace Ranger {
void BasicShader::load()
{
    // _load("Ranger/Rendering/Shaders/basic.vs", "Ranger/Rendering/Shaders/basic.frag");
    _load("Ranger/Rendering/Shaders/basic_mvp.vs", "Ranger/Rendering/Shaders/basic.frag");
}

void BasicShader::postUse()
{
}
}

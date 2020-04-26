//
// Created by William DeVore on 3/11/16.
//

#ifndef RANGERALPHA_FONT_SHADER_H
#define RANGERALPHA_FONT_SHADER_H

#include "../shader.h"

namespace Ranger {
class FontShader final : public Shader {

public:
    virtual void postUse() override;

    FontShader() = default;

    virtual ~FontShader() = default;

    virtual void load() override;
};
}

#endif //RANGERALPHA_FONT_SHADER_H

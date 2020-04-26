//
// Created by William DeVore on 3/11/16.
//

#ifndef RANGERALPHA_BASIC_SHADER_H
#define RANGERALPHA_BASIC_SHADER_H

#include "../shader.h"

namespace Ranger {
class BasicShader final : public Shader {

public:
    virtual void postUse() override;

    BasicShader() = default;

    virtual ~BasicShader() = default;

    virtual void load() override;
};
}

#endif //RANGERALPHA_BASIC_SHADER_H

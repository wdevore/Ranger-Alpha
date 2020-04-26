//
// Created by William DeVore on 3/6/16.
//

#include "engine.h"
#include "IO/configuration.h"
#include "Rendering/rendercontext.h"

namespace Ranger {
    const EnginePtr App::_engine = std::make_unique<Engine>();
    const ConfigurationPtr App::_config = std::make_unique<Configuration>();
    const RenderContextPtr App::_renderContext = std::make_unique<RenderContext>();
}
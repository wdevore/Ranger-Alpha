//
// Created by William DeVore on 3/6/16.
//

#ifndef RANGERALPHA_RANGER_H
#define RANGERALPHA_RANGER_H

#include <functional> // For: function<>
#include <memory> // For: unique_ptr

namespace Ranger {
//---------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------
class Engine;
class Configuration;
class RenderContext;
class Stage;
class Mesh;
class VectorShape;
class VectorObject;
class SceneNode;
class BaseNode;
class BasicShapes;
class UpdateTarget;
class Shader;
class TimingTarget;
class UniformAtlas;
class VectorUniformAtlas;
class VectorAtlas;
class Scheduler;
class Window;

//---------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------
static constexpr double FPS = 60.0;

// 1 frame period is equal to a fraction. For example, if
// FRAMES_PER_SECOND = 60.0 then frame period is ~0.01666666667s of a second
// or in milliseconds it is 1000.0/60.0 = ~16.66666667ms per frame.
static constexpr double FRAME_PERIOD = (1000.0 / FPS);

static constexpr int INITIAL_START_TAG = 1000000;
static constexpr int AUTO_GEN_TAG = -1;

//! Typically the Animation systems are scheduled with high priority.
struct SchedulePriority {
    static constexpr int SYSTEM_HIGH_PRIORITY = -100000000;
    static constexpr int NORMAL_PRIORITY = 0;
    static constexpr int SYSTEM_LOW_PRIORITY = 100000000;
};

enum class Orientation : int { PORTRAIT,
    LANDSCAPE };

//! A function called on every update.
/*!
     * This is the second kind of "target" the @see Scheduler can work with
     * as opposed to a @see TimingTarget.
     */
using UpdateTargetSPtr = std::shared_ptr<UpdateTarget>;
using UpdateTargetWPtr = std::weak_ptr<UpdateTarget>;

using StageSPtr = std::shared_ptr<Stage>;
using SchedulerSPtr = std::shared_ptr<Scheduler>;

using EnginePtr = std::unique_ptr<Engine>;
using ConfigurationPtr = std::unique_ptr<Configuration>;
using RenderContextPtr = std::unique_ptr<RenderContext>;
using VectorUniformAtlasPtr = std::unique_ptr<VectorUniformAtlas>;
using WindowPtr = std::unique_ptr<Window>;

using ShaderSPtr = std::shared_ptr<Shader>;
using SceneNodeSPtr = std::shared_ptr<SceneNode>;
using BaseNodeSPtr = std::shared_ptr<BaseNode>;
using BasicShapesSPtr = std::shared_ptr<BasicShapes>;
using SharedTimingTarget = std::shared_ptr<TimingTarget>;

using VectorAtlasSPtr = std::shared_ptr<VectorAtlas>;
using VectorObjectSPtr = std::shared_ptr<VectorObject>;
using VectorShapeSPtr = std::shared_ptr<VectorShape>;
using UniformAtlasSPtr = std::shared_ptr<UniformAtlas>;

using MeshSPtr = std::shared_ptr<Mesh>;

using ConfigureCallback = std::function<void(Engine&)>;

class App {
private:
    static const StageSPtr _stage;
    static const EnginePtr _engine;
    static const ConfigurationPtr _config;
    static const RenderContextPtr _renderContext;

public:
    static const EnginePtr& engine() { return _engine; }

    static const ConfigurationPtr& config() { return _config; }

    static const RenderContextPtr& renderContext() { return _renderContext; }
};
}

#endif // RANGERALPHA_RANGER_H

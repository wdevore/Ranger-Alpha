//
// Created by William DeVore on 3/6/16.
//

#ifndef RANGERALPHA_ENGINE_H
#define RANGERALPHA_ENGINE_H

#include "Extensions/Graphics/camera.h"
#include "Extensions/Graphics/view.h"
#include "Extensions/Graphics/viewport.h"
#include "GLFW/window.h"
#include "ranger.h"

namespace Ranger {
class Engine final {
public:
    Engine();
    ~Engine();

    //---------------------------------------------------------------------
    // Methods
    //---------------------------------------------------------------------
    void configure(ConfigureCallback preConfCallback);

    void configureComplete();

    void start();

    //---------------------------------------------------------------------
    // Properties
    //---------------------------------------------------------------------
    const Viewport& viewport() const
    {
        return _viewport;
    }

    const Camera& camera() const
    {
        return _camera;
    }

    const View& view() const
    {
        return _view;
    }

    const WindowPtr& window() const
    {
        return _window;
    }

    int fps() const
    {
        return _fps;
    }

    float updateDelta() const
    {
        return _deltaUpdateTime;
    }

    float renderDelta() const
    {
        return _deltaRenderTime;
    }

    //---------------------------------------------------------------------
    // Events
    //---------------------------------------------------------------------
    //        void registerKeyboardListener(const KeyboardInputSPtr& subscriber);
    //        void unregisterKeyboardListener(const KeyboardInputSPtr& subscriber);

private:
    void loop();

private:
    StageSPtr _stage;

    WindowPtr _window;

    //---------------------------------------------------------------------
    // Timing
    //---------------------------------------------------------------------
    bool _pauseEnabled{ false };

    double _currentUpdateTime;
    double _deltaUpdateTime;

    double _deltaRenderTime;
    double _currentRenderTime;

    double _currentSwapTime;
    double _deltaSwapTime;

    //! For debugging only. Set to -1 when not debugging.
    int _loopFor = -1; // -1 = normal non-debug mode.

    const bool _fullScreen{ false };
    double _fpsUpdateRate = 1.0; // In seconds.
    int _fps{};

    Viewport _viewport;
    Camera _camera;
    View _view;

    int _joyAxisCount;
};
}

#endif //RANGERALPHA_ENGINE_H

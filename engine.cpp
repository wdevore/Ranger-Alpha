//
// Created by William DeVore on 3/6/16.
//
//#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iomanip>
#include <iostream>
#include <thread>

#include "Components/stage.h"
#include "IO/configuration.h"
#include "Rendering/rendercontext.h"
#include "engine.h"

namespace Ranger {
Engine::Engine()
    : _fullScreen{ false }
{
}

Engine::~Engine() { std::cout << "Engine::~Engine" << std::endl; }

void Engine::configure(ConfigureCallback preConfCallback)
{
    std::cout << "Engine::configure" << std::endl;

    using namespace Ranger;

    if (!_fullScreen) {
        // Read JSON config for position
        App::config()->configure("config.json");
        if (App::config()->isShowConfig())
            std::cout << "Engine: " << *(App::config().get()) << std::endl;
    }

    if (App::config()->isEngineEnabled())
        std::cout << "Engine: "
                  << "Starting..." << std::endl;
    else {
        std::cerr << "Engine: "
                  << " is disabled in the configuration file." << std::endl;
        return;
    }

    _fpsUpdateRate = App::config()->FPSRefreshRate();
    std::cout << "refresh rate every (" << _fpsUpdateRate << ") seconds"
              << std::endl;

    // Construct GLFW window
    _window = std::make_unique<Window>();

    bool constructed = _window->construct(App::config());

    if (constructed) {
        glfwSetWindowUserPointer(_window->glfwWindow(), _window.get());

        auto func = [](GLFWwindow* w, int key, int scancode, int action, int mode) {
            static_cast<Window*>(glfwGetWindowUserPointer(w))
                ->keyPressed(key, scancode, action, mode);
        };

        glfwSetKeyCallback(_window->glfwWindow(), func);

        std::cout << "Engine: "
                  << "Window constructed: " << std::endl;

        // Bind RenderContext to SceneManager
        //            App::sceneManager->setRenderContext(App::renderContext);
    } else {
        std::cerr << "Engine: "
                  << "Failed to construct Window." << std::endl;
        return;
    }

    _loopFor = App::config()->loopFor();
    if (_loopFor < 0)
        std::cout << "Engine: "
                  << "Looping forever" << std::endl;
    else
        std::cout << "Engine: "
                  << "Looping for: " << _loopFor << std::endl;

    //        App::scheduler->initialize();

    // The engine has completed the pre phase. Now it is the dev's turn.
    preConfCallback(*this);
}

void Engine::start()
{
    // Define the viewport dimensions
    _viewport.setDimensions(App::config());
    _viewport.apply();

    // Calc the aspect ratio between the physical (aka device) dimensions and the
    // the virtual (aka user's design choice) dimensions.
    const ConfigurationPtr& config = App::config();

    float ratioCorrection{};
    float deviceRatio = (float)config->deviceResolutionWidth() / (float)config->deviceResolutionHeight();
    float virtualRatio = (float)config->virtualWidth() / (float)config->virtualHeight();

    float xRatioCorrection = (float)config->deviceResolutionWidth() / (float)config->virtualWidth();
    float yRatioCorrection = (float)config->deviceResolutionHeight() / (float)config->virtualHeight();

    if (virtualRatio < deviceRatio) {
        ratioCorrection = yRatioCorrection;
    } else {
        ratioCorrection = xRatioCorrection;
    }

    // Define the projection (ortho for this engine)
    _camera.initialize(ratioCorrection,
        0.0f, 0.0f,
        App::config()->deviceResolutionHeight(),
        App::config()->deviceResolutionWidth());

    if (App::config()->is_ViewCentered())
        _camera.setCentered();

    _view.initialize(App::config()->view());

    _stage = std::make_shared<Stage>();
    _stage->construct((float)_viewport.screenWidth, (float)_viewport.screenHeight);

    std::cout << "###########################################" << std::endl;
    std::cout << "Engine: "
              << "Ranger is starting!" << std::endl;
    std::cout << "###########################################" << std::endl;
    if (_loopFor < 0)
        loop();

    std::cout << "Engine: "
              << "Ranger is exiting..." << std::endl;
}

void Engine::configureComplete()
{
}

void Engine::loop()
{
    //        int loopCount = 0;
    // std::cout << "Engine: " << "FRAME_PERIOD: " << FRAME_PERIOD << std::endl;

    // glfwGetTime returns the number of seconds since the app started running.
    // "seconds" is typically measured in micro or nano time units.
    double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double deltaTime{ FRAME_PERIOD };

    int nbFrames = 0;

    std::cout << std::fixed << std::setw(11) << std::setprecision(4) << std::endl;
    const ConfigurationPtr& config = App::config();
    bool stickActive = false;

    while (_window->running()) {
        _window->poll();

        // ####################################################################
        // BEGIN Update and Render
        // ####################################################################

        if (!_pauseEnabled) {
        // BEGIN ------------- UPDATE ----------------------------------------
#pragma region Show joystick info
            if (config->isShowJoystickInfo()) {
                const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &_joyAxisCount);
                stickActive = false;
                for (int i = 0; i < _joyAxisCount; i++) {
                    if (axes[i] != 0.0) {
                        std::cout << "(" << i << ")" << axes[i] << " # ";
                        stickActive = true;
                    }
                }
                if (stickActive)
                    std::cout << std::endl;
            }
#pragma endregion

            _currentUpdateTime = glfwGetTime();

            // Refresh scheduler
            //                App::scheduler->update(deltaTime);

            _deltaUpdateTime = glfwGetTime() - _currentUpdateTime;
            // END ------------- UPDATE ----------------------------------------

            // This clear sync locked with the vertical refresh. The clear itself
            // takes ~30 microseconds on a mid-range mobile nvidia GPU.
            _window->clear();

            // BEGIN ------------- RENDER ----------------------------------------
            _currentRenderTime = glfwGetTime();

            if (_window->fillPolyMode)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            bool continueStepping = _stage->step();
            if (!continueStepping) {
                std::cout << "Engine::loop stage stopped stepping, most likely from a lack of Scenes." << std::endl;
                break;
            }

#pragma region Work simulation
            // std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate
            // Render scene(s).
            //                bool continueDraws = App::sceneManager->step(deltaTime);
            //                if (!continueDraws) {
            //                    // There are no more scenes to render.
            //                    std::cout << "Engine::loop: " << "There are no more
            //                    Scenes to render." << std::endl;
            //                    _window->destroy();
            //                    break;
            //                }
#pragma endregion

            _deltaRenderTime = glfwGetTime() - _currentRenderTime;
            // END ------------- RENDER ----------------------------------------

            // Swap is synced to the vertical which means it is waits based on the monitor refresh rate.
            // The window->clear is also locked to the sync.
            _currentSwapTime = glfwGetTime();
            _window->swap();
            _deltaSwapTime = glfwGetTime() - _currentSwapTime;
        }

        // ####################################################################
        // END Update and Render
        // ####################################################################

        currentTime = glfwGetTime();
        nbFrames++;

#pragma region Show timing
        // if (config->isShowTimingInfo() && (currentTime - lastTime >= 1.0)) {
        //     std::cout << nbFrames << std::endl;
        //     _fps = nbFrames;
        //     nbFrames = 0; // Frames that occurred during the time second interval.
        //     lastTime += 1.0; // Move forward to the next Rate.
        // }

        if (currentTime - lastTime >= _fpsUpdateRate) { // N Seconds passed?
            _fps = int(nbFrames / _fpsUpdateRate);

            if (config->isShowTimingInfo()) {
                std::cout
                    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                    << std::endl;
                std::cout << _fps << " FPS" << std::endl;
                std::cout << _deltaSwapTime << " Swap ms/loop" << std::endl;
                std::cout << _deltaUpdateTime << " Update ms/loop" << std::endl;
                std::cout << _deltaRenderTime << " Render ms/loop" << std::endl;
                std::cout << (1000.0 * _fpsUpdateRate) / double(nbFrames)
                          << " ms/frame, Frames: " << nbFrames << std::endl;
            }
            nbFrames = 0; // Frames that occurred during the time second interval.
            lastTime += _fpsUpdateRate; // Move forward to the next Rate.
        }
#pragma endregion
    }

    std::cout << "Engine::loop: loop exited, beginning release cycle..."
              << std::endl;
}
}
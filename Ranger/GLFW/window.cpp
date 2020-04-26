//
// Created by William DeVore on 3/6/16.
//

#include <iostream>

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../IO/configuration.h"
#include "../Rendering/rendercontext.h"
#include "window.h"

namespace Ranger {
//    bool Window::_quitTriggered = false;

Window::Window() {}

Window::~Window()
{
    std::cout << "Window::~Window" << std::endl;

    // Terminate GLFW, clearing any resources allocated by GLFW.
    if (!_destroyed) {
        std::cout << "Window::~Window terminating GLFW" << std::endl;
        glfwTerminate();
    }

    _window = nullptr;
}

bool Window::construct(const ConfigurationPtr& config)
{
    bool glfwInitialized = initGLFW(config);

    initGL(config);

    return glfwInitialized;
}

bool Window::initGLFW(const ConfigurationPtr& config)
{
    // GLFW ---------------------------------------------------------------------------
    // Init GLFW
    // --------------------------------------------------------------------------------
    glfwInit();

    // Set all the required options for GLFW.
    if (config->isShowGLInfo())
        std::cout << "Window::construct "
                  << "Requesting OpenGL minimum of: " << config->GLMajorVersion()
                  << "." << config->GLMinorVersion() << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // NOTE: Required by OSX! Otherwise the app crashes.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    _window = glfwCreateWindow(
        config->deviceResolutionWidth(),
        config->deviceResolutionHeight(),
        config->title().c_str(), nullptr, nullptr);

    if (_window == nullptr) {
        std::cerr << "Window: "
                  << "Failed to create GLFW window." << std::endl;
        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate();
        return false;
    }

    glfwSetFramebufferSizeCallback(_window, &Window::FrameBufferSizeCallback);

    // Needed for glfwGetWindowUserPointer to work
    glfwSetWindowUserPointer(_window, this);

    // glfwSetWindowSize(_window,
    //     config->deviceResolutionWidth(), config->deviceResolutionHeight());

    // Sets the upper left position of Window frame.
    glfwSetWindowPos(_window,
        config->windowPositionX(),
        config->windowPositionY());

    glfwMakeContextCurrent(_window);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();

    glfwGetWindowFrameSize(_window, &frameLeft, &frameTop, &frameRight, &frameBottom);
    // Deprecated (The camera compensates for it): Adjust device resolution to compensate for frame offsets.
    // config->deviceResolutionWidth(config->deviceResolutionWidth() - (frameLeft + frameRight));
    // config->deviceResolutionHeight(config->deviceResolutionHeight() - (frameTop + frameBottom));

    if (config->isShowMonitorInfo()) {
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        std::cout << "Monitor refresh rate: " << mode->refreshRate << " Hz"
                  << std::endl;
        std::cout << "Monitor colors: "
                  << "RGB(" << mode->redBits << "," << mode->greenBits << ","
                  << mode->blueBits << ")" << std::endl;
        std::cout << "Monitor dimensions: " << mode->width << " x " << mode->height
                  << std::endl;

        int windowWidth;
        int windowHeight;
        glfwGetWindowSize(_window, &windowWidth, &windowHeight);
        std::cout << "Windowsize: " << windowWidth << " x " << windowHeight << std::endl;

        std::cout << "Framesize: "
                  << "left-top : " << frameLeft << " x " << frameTop
                  << ", right-bottom : " << frameRight << " x " << frameBottom << std::endl;
    }

    // Set keyboard callback function
    glfwSetKeyCallback(_window, &Window::KeyPressCallback);

    int joy1Present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    if (joy1Present == GLFW_TRUE) {
        std::cout << "Window: "
                  << "Joystick 1 is present " << std::endl;
        const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
        std::cout << "and its name is: '"
                  << name << "'" << std::endl;
    }

    int joy2Present = glfwJoystickPresent(GLFW_JOYSTICK_2);
    if (joy2Present == GLFW_TRUE) {
        std::cout << "Window: "
                  << "Joystick 2 is present" << std::endl;
    }

    int joy3Present = glfwJoystickPresent(GLFW_JOYSTICK_3);
    if (joy3Present == GLFW_TRUE) {
        std::cout << "Window: "
                  << "Joystick 3 is present" << std::endl;
    }

    return true;
}

void Window::initGL(const ConfigurationPtr& config)
{
    // Set this to true so GLEW knows to use a modern approach to retrieving
    // function pointers and extensions
    glewExperimental = GL_TRUE;

    // GLEW ---------------------------------------------------------------------------
    // Initialize GLEW to setup the OpenGL Function pointers
    // --------------------------------------------------------------------------------
    glewInit();

    if (config->isShowGLInfo()) {
        std::cout << "GL Version obtained: " << glGetString(GL_VERSION)
                  << std::endl;
        std::cout << "GL vender: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "GL renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        GLint nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Max # of vertex attributes supported: " << nrAttributes
                  << std::endl;
    }

    if (config->is_lockToVSync()) {
        std::cout << "Window: "
                  << "Locking to VSync." << std::endl;
        glfwSwapInterval(1); // lock to vsync
    }

    const Color& color = config->clearColor();
    App::renderContext()->clearColor(color);
    bool initialized = App::renderContext()->initialize();

    if (!initialized) {
        std::cerr << "Window::construct: Failed to initialize render context"
                  << std::endl;
    }

    int frameBufWidth;
    int frameBufHeight;
    glfwGetFramebufferSize(_window, &frameBufWidth, &frameBufHeight);
    std::cout << "FrameBuffer size: " << frameBufWidth << " x " << frameBufHeight << std::endl;
}

bool Window::running() const { return !glfwWindowShouldClose(_window); }

void Window::swap()
{
    // Swap the screen buffers
    glfwSwapBuffers(_window);
}

void Window::clear()
{
    // Clear the buffers
    App::renderContext()->clear();
}

void Window::destroy()
{
    _destroyed = true;
    glfwSetWindowShouldClose(_window, GL_TRUE);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
}

void Window::poll()
{
    // Check if any events have been activated (key pressed, mouse moved etc.) and
    // call corresponding response functions
    // Will cause any callbacks to be triggered.
    if (Window::_quitTriggered) {
        glfwSetWindowShouldClose(_window, GL_TRUE);
    } else
        glfwPollEvents();
}

void Window::keyPressed(int key, int scancode, int action, int mode)
{
    std::cout << "keypressed" << std::endl;
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        _quitTriggered = true;
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        toggle = !toggle;
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        drawAllShapes = !drawAllShapes;

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        fillPolyMode = !fillPolyMode;
}

void Window::KeyPressCallback(GLFWwindow* win, int key, int scancode,
    int action, int mode)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->keyPressed(key, scancode, action, mode);
}

void Window::FrameBufferSizeCallback(GLFWwindow* win, int width, int height)
{
    std::cout << "FrameBuffer re-size: " << width << " x " << height << std::endl;
}
}
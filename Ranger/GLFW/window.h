//
// Created by William DeVore on 3/6/16.
//

#ifndef RANGERALPHA_WINDOW_H
#define RANGERALPHA_WINDOW_H

#include "../ranger.h"

class GLFWwindow;

namespace Ranger {
    class Window final {
    public:
        Window();

        ~Window();

        bool construct(const ConfigurationPtr& config);

        bool running() const;

        void setQuitTriggered(bool quitTriggered) {
            _quitTriggered = quitTriggered;
        }


        GLFWwindow* glfwWindow() const {
            return _window;
        }

        void destroy();

        void poll();

        void keyPressed(int key, int scancode, int action, int mode);

        //---------------------------------------------------------------------
        // OpenGL related
        //---------------------------------------------------------------------
        void clear();

        void swap();

        bool toggle{false};
        bool fillPolyMode{true};
        bool drawAllShapes{false};

        int frameLeft{};
        int frameTop{};
        int frameRight{};
        int frameBottom{};

    private:
        bool initGLFW(const ConfigurationPtr& config);
        void initGL(const ConfigurationPtr& config);

        // Framebuffer size event
        static void FrameBufferSizeCallback(GLFWwindow* win, int width, int height);

        // Here are our callbacks.
        static void KeyPressCallback(GLFWwindow* win, int key, int scancode, int action, int mode);

        GLFWwindow* _window;

        bool _destroyed{false};

        // Window related events
        bool _quitTriggered{false};

    };
}

#endif //RANGERALPHA_WINDOW_H

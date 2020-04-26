//
// Created by William DeVore on 3/8/16.
//

#include <GLFW/glfw3.h>
#include "time.h"

namespace Ranger {
    double Time::getTime() {
        return glfwGetTime();
    }
}
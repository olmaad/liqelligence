#include "context.hpp"

#include <GLFW/glfw3.h>

namespace liqelligence::core::gl
{
    context::context()
    {
        _init_result = glfwInit();
    }

    context::~context()
    {
        if (_init_result) {
            glfwTerminate();
        }
    }

    context::operator bool() const
    {
        return valid();
    }

    bool context::valid() const
    {
        return !!_init_result;
    }
}

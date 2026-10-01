#include "window.hpp"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace liqelligence::core::gl
{
    window::window()
    {
        _handle = glfwCreateWindow(1280, 720, "liqelligence", NULL, NULL);

        if (_handle) {
            glfwMakeContextCurrent(_handle);
            glewInit();

            glEnable(GL_DEPTH_TEST);
            glClearColor(0.078f, 0.090f, 0.095f, 0.f);
        }
    }

    window::operator bool() const
    {
        return valid();
    }

    bool window::valid() const
    {
        return !!_handle;
    }

    bool window::need_close() const
    {
        return !valid() || glfwWindowShouldClose(_handle);
    }

    void window::draw()
    {
        if (!valid()) {
            return;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(_handle);
    }

    void window::process()
    {
        if (!valid()) {
            return;
        }

        glfwPollEvents();
    }
}

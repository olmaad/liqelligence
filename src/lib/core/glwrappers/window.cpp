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
            //glfwSwapInterval(0);
            glewInit();

            glClearColor(1.f, 0.f, 0.f, 1.f);

            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //glEnable(GL_STENCIL_TEST);
            //glStencilMask(0xFF);
            //glStencilFunc(GL_EQUAL, 0, 0xFF);
            //glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
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

    void window::draw(std::function<void()> delegate)
    {
        if (!valid()) {
            return;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (delegate) {
            delegate();
        }

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

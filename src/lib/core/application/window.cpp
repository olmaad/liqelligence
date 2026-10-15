#include "window.hpp"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace liqelligence::core::application
{
    window* window::_instance = nullptr;

    window::window(window_delegate delegate, window_settings settings)
        : _delegate(std::move(delegate))
    {
        if (_instance) {
            return;
        }

        _instance = this;

        if (!glfwInit()) {
            return;
        }

        _handle = glfwCreateWindow(settings.size.x, settings.size.y, "Liqelligence", NULL, NULL);
        if (!_handle) {
            return;
        }

        glfwMakeContextCurrent(_handle);
        glfwSwapInterval(settings.sync ? 1 : 0);

        glfwSetWindowSizeCallback(_handle, &size_changed_callback);

        glewInit();

        const auto& fill = settings.fill_color;
        glClearColor(fill.r, fill.g, fill.b, fill.a);

        if (_delegate.onCreate) {
            _delegate.onCreate(*this);
        }

        if (_delegate.onScreenSizeChanged) {
            _delegate.onScreenSizeChanged(settings.size);
        }
    }

    window::~window() noexcept
    {
        glfwTerminate();

        _instance = nullptr;
    }

    bool window::valid() const
    {
        return !!_handle;
    }

    void window::set_icon(vector2d size, const std::vector<uint8_t>& data)
    {
        if (!valid()) {
            return;
        }

        const GLFWimage icon{
            .width = size.x,
            .height = size.y,
            .pixels = const_cast<uint8_t*>(data.data())
        };

        glfwSetWindowIcon(_handle, 1, &icon);
    }

    void window::show()
    {
        _last_update = std::chrono::system_clock::now();

        do
        {
            update();
            draw();

        } while (!need_close());

        close();
    }

    void window::close()
    {
        if (_delegate.onClose) {
            _delegate.onClose(*this);
        }

        _handle = nullptr;
    }

    bool window::need_close() const
    {
        return !valid() || glfwWindowShouldClose(_handle);
    }

    void window::update()
    {
        glfwPollEvents();

        const auto dt = (std::exchange(_last_update, std::chrono::system_clock::now()) - _last_update) * -1;
        if (_delegate.onUpdate) {
            _delegate.onUpdate(std::chrono::duration<float>(dt).count());
        }
    }

    void window::draw() const
    {
        if (!valid()) {
            return;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (_delegate.onDraw) {
            _delegate.onDraw();
        }

        glfwSwapBuffers(_handle);
    }

    void window::size_changed_callback(GLFWwindow* window, int width, int height)
    {
        if (_instance && _instance->_handle == window) {
            if (const auto& callback = _instance->_delegate.onScreenSizeChanged) {
                callback({ width, height });
            }
        }
    }
}

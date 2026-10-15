#pragma once

#include <core/application/window_delegate.hpp>
#include <core/application/window_setting.hpp>
#include <core/math/types.hpp>

class GLFWwindow;

namespace liqelligence::core::application
{
    class window
    {
    public:
        window(window_delegate delegate, window_settings settings);
        ~window() noexcept;

        window(const window&) = delete;
        window(window&&) = delete;
        window& operator=(const window&) = delete;
        window& operator=(window&&) = delete;

        bool valid() const;

        void set_icon(vector2d size, const std::vector<uint8_t>& data);

        void show();
        void close();

    private:
        bool need_close() const;

        void update();
        void draw() const;

        static void size_changed_callback(GLFWwindow* window, int width, int height);

    private:
        static window* _instance;

        window_delegate _delegate;
        GLFWwindow* _handle = nullptr;
        std::chrono::system_clock::time_point _last_update;
    };
}

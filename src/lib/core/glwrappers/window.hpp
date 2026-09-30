#pragma once

class GLFWwindow;

namespace liqelligence::core::gl
{
    class window
    {
    public:
        window();

        operator bool() const;

        bool valid() const;
        bool need_close() const;

        void draw();
        void process();

    private:
        GLFWwindow* _handle = nullptr;
    };
}

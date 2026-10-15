#pragma once

#include <core/math/types.hpp>

namespace liqelligence::core::application
{
    class window;

    struct window_delegate
    {
        std::function<void(window&)> onCreate;
        std::function<void(window&)> onClose;

        std::function<void(float)> onUpdate;
        std::function<void()> onDraw;

        std::function<void(vector2d)> onScreenSizeChanged;
    };
}

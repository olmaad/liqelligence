#pragma once

#include <core/math/types.hpp>

namespace liqelligence::core::application
{
    struct window_settings
    {
        vector2d size;
        color fill_color;
        bool sync = true;
    };
}

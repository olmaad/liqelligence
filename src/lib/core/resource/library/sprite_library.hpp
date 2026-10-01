#pragma once

#include <core/resource/library/library.hpp>

namespace liqelligence::core::resource
{
    class sprite;

    class sprite_library : public resource_library<sprite>
    {
    public:
        ~sprite_library() noexcept override = default;
    };
}
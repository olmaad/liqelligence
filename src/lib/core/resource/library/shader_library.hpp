#pragma once

#include <core/resource/library/library.hpp>

namespace liqelligence::core::resource
{
    class shader;

    class shader_library : public resource_library<shader>
    {
    public:
        ~shader_library() noexcept override = default;

    };
}

#pragma once

#include <core/resource/library/library.hpp>

namespace liqelligence::core::gl
{
    class shader;
}

namespace liqelligence::core::resource
{
    class shader_library : public resource_library<gl::shader>
    {
    public:
        ~shader_library() noexcept override = default;

    };
}

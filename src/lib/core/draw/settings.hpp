#pragma once

namespace liqelligence::core::draw
{
    enum class pass : uint8_t {
        stencil = 0,
        blend
    };

    struct settings {
        pass pass_type = pass::blend;
    };
}

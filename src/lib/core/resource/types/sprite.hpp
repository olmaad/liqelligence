#pragma once

#include <core/math/types.hpp>
#include <vector>

namespace liqelligence::core::resource
{
    class sprite
    {
    public:
        sprite(uvector2d size, std::vector<uint8_t> data);

        bool valid() const;

    private:
        uvector2d _size;
        std::vector<uint8_t> _data;

    };
}

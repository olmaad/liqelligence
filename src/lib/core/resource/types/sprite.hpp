#pragma once

#include <vector>

namespace liqelligence::core::resource
{
    class sprite
    {
    public:
        sprite(std::vector<uint8_t> data);

        bool valid() const;

    private:
        std::vector<uint8_t> _data;

    };
}

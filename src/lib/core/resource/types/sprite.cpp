#include "sprite.hpp"

namespace liqelligence::core::resource
{
    sprite::sprite(std::vector<uint8_t> data)
        : _data(std::move(data))
    {
    }

    bool sprite::valid() const
    {
        return true;
    }
}

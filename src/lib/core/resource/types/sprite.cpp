#include "sprite.hpp"

namespace liqelligence::core::resource
{
    sprite::sprite(uvector2d size, std::vector<uint8_t> data)
        : _size(size)
        , _data(std::move(data))
    {
    }

    bool sprite::valid() const
    {
        return _size.x && _size.y && !_data.empty();
    }
}

#include "sprite.hpp"

namespace liqelligence::core::resource
{
    sprite::sprite(uvector2d size, std::vector<uint8_t>&& data)
        : _size(size)
        , _texture(size, std::forward<std::vector<uint8_t>&&>(data))
    {
    }

    bool sprite::valid() const
    {
        return _texture;
    }

    uvector2d sprite::get_original_size() const
    {
        return _size;
    }

    const gl::texture& sprite::get_texture() const
    {
        return _texture;
    }

    void sprite::bind() const
    {
        _texture.bind();
    }

    void sprite::unbind() const
    {
        _texture.unbind();
    }
}

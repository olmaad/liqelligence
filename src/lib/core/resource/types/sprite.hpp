#pragma once

#include <core/glwrappers/texture.hpp>
#include <core/glwrappers/surface.hpp>
#include <core/math/types.hpp>
#include <gl/glew.h>
#include <vector>

namespace liqelligence::core::resource
{
    class sprite
    {
    public:
        sprite(uvector2d size, std::vector<uint8_t>&& data);

        bool valid() const;
        uvector2d get_original_size() const;
        const gl::texture& get_texture() const;

        void bind() const;
        void unbind() const;

    private:
        uvector2d _size;
        gl::texture _texture;

    };
}

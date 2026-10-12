#pragma once

#include <core/math/types.hpp>
#include <gl/glew.h>

namespace liqelligence::core::gl
{
    class texture
    {
    public:
        texture(uvector2d size, std::vector<uint8_t>&& data);
        ~texture();

        GLuint get_handle() const;

        void bind() const;
        void unbind() const;

        operator bool() const;

    private:
        GLuint _handle = 0u;

    };
}
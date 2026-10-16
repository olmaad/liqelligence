#pragma once

#include <gl/glew.h>
#include <core/glwrappers/vertex_array.hpp>

namespace liqelligence::core::gl
{
    class surface2d
    {
    public:
        surface2d();

        size_t get_vertex_count() const;

        void bind() const;
        void unbind() const;

    private:
        vertex_array<fvector4d, GL_ARRAY_BUFFER> _array;

    };
}

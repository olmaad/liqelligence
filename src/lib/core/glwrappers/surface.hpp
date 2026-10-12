#pragma once

#include <gl/glew.h>

namespace liqelligence::core::gl
{
    class surface2d
    {
    public:
        surface2d();
        ~surface2d();

        size_t get_vertex_count() const;
        GLuint get_vertex_array_handle() const;
        GLuint get_vertex_buffer_handle() const;

        void bind() const;
        void unbind() const;

        operator bool() const;

    private:
        GLuint _vertex_array_handle = 0u;
        GLuint _vertex_buffer_handle = 0u;

    };
}

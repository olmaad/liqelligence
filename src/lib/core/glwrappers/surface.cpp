#include "surface.hpp"

#include <array>

namespace
{
    constexpr std::array<float, 24u> vertices{
            0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f,
            0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 1.f
    };
}

namespace liqelligence::core::gl
{
    surface2d::surface2d()
    {
        glGenVertexArrays(1, &_vertex_array_handle);
        if (!_vertex_array_handle) {
            return;
        }

        glGenBuffers(1, &_vertex_buffer_handle);
        if (!_vertex_buffer_handle) {
            return;
        }

        glBindVertexArray(_vertex_array_handle);
        glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_handle);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0u, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<const void*>(0u));
        glEnableVertexAttribArray(0u);

        glVertexAttribPointer(1u, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<const void*>(2u * sizeof(float)));
        glEnableVertexAttribArray(1u);

        glBindVertexArray(NULL);
    }

    surface2d::~surface2d()
    {
        if (_vertex_array_handle) {
            glDeleteVertexArrays(1u, &_vertex_array_handle);
        }

        if (_vertex_buffer_handle) {
            glDeleteBuffers(1u, &_vertex_buffer_handle);
        }
    }

    size_t surface2d::get_vertex_count() const
    {
        constexpr auto count = vertices.size() / 4u;
        return count;
    }

    GLuint surface2d::get_vertex_array_handle() const
    {
        return _vertex_array_handle;
    }

    GLuint surface2d::get_vertex_buffer_handle() const
    {
        return _vertex_buffer_handle;
    }

    void surface2d::bind() const
    {
        glBindVertexArray(_vertex_array_handle);
    }

    void surface2d::unbind() const
    {
    }

    surface2d::operator bool() const
    {
        return !!_vertex_array_handle && !!_vertex_buffer_handle;
    }
}

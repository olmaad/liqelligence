#pragma once

#include <gl/glew.h>
#include <core/glwrappers/vertex_buffer.hpp>

namespace liqelligence::core::gl
{
    template<typename t_value, GLenum gl_type>
    class vertex_array
    {
        using buffer_t = vertex_buffer<t_value, gl_type>;

    public:
        vertex_array(std::initializer_list<typename buffer_t::attribute>&& attributes)
            : _buffer(std::forward<std::initializer_list<typename buffer_t::attribute>>(attributes))
        {
            glGenVertexArrays(1, &_handle);
        }

        ~vertex_array()
        {
            if (_handle) {
                glDeleteVertexArrays(1u, &_handle);
            }
        }

        void bind() const
        {
            if (!_handle) {
                return;
            }

            glBindVertexArray(_handle);
            _buffer.bind();
        }

        void unbind() const
        {
            if (!_handle) {
                return;
            }

            _buffer.unbind();
            glBindVertexArray(0u);
        }

        const buffer_t& get_buffer() const
        {
            return _buffer;
        }

    private:
        GLuint _handle = 0u;
        buffer_t _buffer;

    };
}

#pragma once

#include <gl/glew.h>
#include <core/math/types.hpp>

namespace liqelligence::core::gl
{
    template<typename t_value>
    struct vertex_buffer_types {
        static_assert(false, "Please implement vertex_buffer_gl_type");
        using underlying_type = char;
        static constexpr GLenum gl_value_type = GL_BYTE;
    };

    template<> struct vertex_buffer_types<float> {
        using underlying_type = float;
        static constexpr GLenum gl_value_type = GL_FLOAT;
    };
    template<> struct vertex_buffer_types<frect2d> {
        using underlying_type = float;
        static constexpr GLenum gl_value_type = GL_FLOAT;
    };

    template<typename t_value, GLenum gl_type>
    class vertex_buffer
    {
    public:
        vertex_buffer(GLuint index = 0u, GLuint divisor = 0u)
            : _index(index)
            , _divisor(divisor)
        {
            glGenBuffers(1u, &_handle);
        }

        ~vertex_buffer()
        {
            if (_handle) {
                glDeleteBuffers(1u, &_handle);
            }
        }

        void set_index(GLuint value)
        {
            _index = value;
            update_attributes();
        }

        void set_divisor(GLuint value)
        {
            _divisor = value;
            update_attributes();
        }

        void bind() const
        {
            if (!_handle) {
                return;
            }

            glBindBuffer(gl_type, _handle);
            glEnableVertexAttribArray(_index);

            update_attributes();
        }

        void unbind() const
        {
            if (!_handle) {
                return;
            }

            glDisableVertexAttribArray(_index);
            glBindBuffer(gl_type, 0u);
        }

        void write_data(const std::vector<t_value>& data, GLenum usage) const
        {
            glBufferData(gl_type, data.size() * sizeof(t_value), data.data(), usage);
        }

    private:
        void update_attributes() const
        {
            constexpr auto vertex_dimension = sizeof(t_value) / sizeof(vertex_buffer_types<t_value>::underlying_type);
            glVertexAttribPointer(_index, vertex_dimension, vertex_buffer_types<t_value>::gl_value_type, GL_FALSE, sizeof(t_value), reinterpret_cast<const void*>(0u));
            glVertexAttribDivisor(_index, _divisor);
        }

    private:
        GLuint _handle = 0u;
        GLuint _index = 0u;
        GLuint _divisor = 0u;

    };
}

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
    template<> struct vertex_buffer_types<fvector2d> {
        using underlying_type = float;
        static constexpr GLenum gl_value_type = GL_FLOAT;
    };
    template<> struct vertex_buffer_types<fvector3d> {
        using underlying_type = float;
        static constexpr GLenum gl_value_type = GL_FLOAT;
    };
    template<> struct vertex_buffer_types<fvector4d> {
        using underlying_type = float;
        static constexpr GLenum gl_value_type = GL_FLOAT;
    };

    template<typename t_value, GLenum gl_type>
    class vertex_buffer
    {
    public:
        struct attribute {
            GLuint index = 0u;
            GLuint divisor = 0u;
            size_t dimension = sizeof(t_value) / sizeof(vertex_buffer_types<t_value>::underlying_type);
            size_t offset = 0u;
        };

    public:
        vertex_buffer(std::initializer_list<attribute> attributes)
            : _attributes(attributes)
        {
            glGenBuffers(1u, &_handle);
        }

        ~vertex_buffer()
        {
            if (_handle) {
                glDeleteBuffers(1u, &_handle);
            }
        }

        void add_attribute(attribute attribute)
        {
            _attributes.emplace_back(attribute);
        }

        void clear_attributes()
        {
            _attributes.clear();
        }

        void bind() const
        {
            if (!_handle) {
                return;
            }

            glBindBuffer(gl_type, _handle);

            for (const auto& it : _attributes) {
                enable_attribute(it);
            }
        }

        void unbind() const
        {
            if (!_handle) {
                return;
            }

            for (const auto& it : _attributes) {
                disable_attribute(it);
            }

            glBindBuffer(gl_type, 0u);
        }

        void write_data(const std::vector<t_value>& data, GLenum usage) const
        {
            if (!_handle) {
                return;
            }

            glBufferData(gl_type, data.size() * sizeof(t_value), data.data(), usage);
        }

    private:
        void enable_attribute(const attribute& attribute) const
        {
            glEnableVertexAttribArray(attribute.index);
            glVertexAttribPointer(attribute.index, attribute.dimension, vertex_buffer_types<t_value>::gl_value_type, GL_FALSE, sizeof(t_value), reinterpret_cast<const void*>(attribute.offset * sizeof(vertex_buffer_types<t_value>::underlying_type)));
            glVertexAttribDivisor(attribute.index, attribute.divisor);
        }

        void disable_attribute(const attribute& attribute) const
        {
            glDisableVertexAttribArray(attribute.index);
        }

    private:
        GLuint _handle = 0u;
        std::vector<attribute> _attributes;

    };
}

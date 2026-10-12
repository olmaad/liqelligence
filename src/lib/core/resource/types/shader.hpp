#pragma once

#include <gl/glew.h>
#include <core/math/types.hpp>
#include <vector>
#include <string>

namespace liqelligence::core::resource
{
    class shader
    {
    public:
        enum class type
        {
            fragment = GL_FRAGMENT_SHADER,
            vertex = GL_VERTEX_SHADER
        };

    public:
        shader(std::vector<uint8_t>&& fragment_code, std::vector<uint8_t>&& vertex_code);
        ~shader();

        bool valid() const;
        GLuint get_handle() const;

        void bind() const;
        void unbind() const;

        void set_uniform(std::string_view name, vector2d value) const;

    private:
        GLuint create_program(const std::vector<uint8_t>& fragment_code, const std::vector<uint8_t>& vertex_code);
        GLuint compile(type type, const std::vector<uint8_t>& code) const;

    private:
        GLuint _handle = 0u;

    };
}

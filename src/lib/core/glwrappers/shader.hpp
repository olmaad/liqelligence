#pragma once

#include <gl/glew.h>
#include <vector>

namespace liqelligence::core::gl
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

    private:
        GLuint create_program(const std::vector<uint8_t>& fragment_code, const std::vector<uint8_t>& vertex_code);
        GLuint compile(type type, const std::vector<uint8_t>& code) const;

    private:
        GLuint _handle = 0u;

    };
}

#include "shader.hpp"

#include <array>

namespace liqelligence::core::gl
{
    shader::shader(std::vector<uint8_t>&& fragment_code, std::vector<uint8_t>&& vertex_code)
    {
        _handle = create_program(fragment_code, vertex_code);
    }

    shader::~shader()
    {
        if (_handle) {
            glDeleteProgram(_handle);
        }
    }

    bool shader::valid() const
    {
        if (_handle) {
            glValidateProgram(_handle);

            GLint result = GL_FALSE;
            glGetProgramiv(_handle, GL_VALIDATE_STATUS, &result);

            return !!result;
        }

        return false;
    }

    GLuint shader::create_program(const std::vector<uint8_t>& fragment_code, const std::vector<uint8_t>& vertex_code)
    {
        GLuint handle{};

        auto fragment_handle = compile(type::fragment, fragment_code);
        auto vertex_handle = compile(type::vertex, vertex_code);

        if (fragment_handle && vertex_handle) {
            handle = glCreateProgram();

            glAttachShader(handle, fragment_handle);
            glAttachShader(handle, vertex_handle);
            glLinkProgram(handle);

            GLint result = GL_FALSE;
            glGetProgramiv(handle, GL_LINK_STATUS, &result);

            if (!result) {
                glDeleteProgram(handle);
                handle = {};
            }
        }

        glDeleteShader(fragment_handle);
        glDeleteShader(vertex_handle);

        return handle;
    }

    GLuint shader::compile(type type, const std::vector<uint8_t>& code) const
    {
        GLuint handle = glCreateShader(static_cast<GLenum>(type));
        if (!handle) {
            return {};
        }

        std::array<const GLchar*, 1> source_code{ reinterpret_cast<const GLchar*>(code.data()) };
        std::array<const GLint, 1> source_size{ static_cast<GLint>(code.size()) };

        glShaderSource(handle, 1, source_code.data(), source_size.data());
        glCompileShader(handle);

        GLint compile_result = GL_FALSE;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_result);

        if (!compile_result) {
            return {};
        }

        return handle;
    }
}

#include "texture.hpp"

namespace liqelligence::core::gl
{
    texture::texture(uvector2d size, std::vector<uint8_t>&& data)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &_handle);
        if (_handle) {
            glTextureStorage2D(_handle, 1, GL_RGBA8, size.x, size.y);
            glTextureSubImage2D(_handle, 0, 0, 0, size.x, size.y, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

            glTextureParameteri(_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
    }

    texture::~texture()
    {
        if (_handle) {
            glDeleteTextures(1u, &_handle);
        }
    }

    GLuint texture::get_handle() const
    {
        return _handle;
    }

    void texture::bind() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _handle);
    }

    void texture::unbind() const
    {
    }

    texture::operator bool() const
    {
        return !!_handle;
    }
}

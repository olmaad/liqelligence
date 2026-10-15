#include "screen.hpp"

#include <gl/glew.h>
#include <core/resource/types/shader.hpp>

namespace liqelligence::core::draw
{
    vector2d screen::get_size() const
    {
        return _size;
    }

    void screen::set_size(vector2d value)
    {
        _size = value;

        glViewport(0, 0, _size.x, _size.y);
    }

    void screen::fill_uniforms(const resource::shader& shader) const
    {
        shader.set_uniform("u_screen_size", fvector2d(_size));
    }
}

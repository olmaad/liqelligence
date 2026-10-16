#include "surface.hpp"

#include <core/draw/bindable.hpp>
#include <core/math/types.hpp>

namespace
{
    using namespace liqelligence;

    const std::vector<fvector4d> vertices
    {
        {0.f, 0.f, 0.f, 0.f},
        {1.f, 0.f, 1.f, 0.f},
        {1.f, 1.f, 1.f, 1.f},
        {0.f, 0.f, 0.f, 0.f},
        {1.f, 1.f, 1.f, 1.f},
        {0.f, 1.f, 0.f, 1.f}
    };
}

namespace liqelligence::core::gl
{
    surface2d::surface2d()
        : _array(
            {
                {.index = 0u, .dimension = 2u, .offset = 0u},
                {.index = 1u, .dimension = 2u, .offset = 2u}
            })
    {
        draw::scoped_bind binded_array(_array);

        binded_array->get_buffer().write_data(vertices, GL_STATIC_DRAW);
    }

    size_t surface2d::get_vertex_count() const
    {
        return vertices.size();
    }

    void surface2d::bind() const
    {
        _array.bind();
    }

    void surface2d::unbind() const
    {
        _array.unbind();
    }
}

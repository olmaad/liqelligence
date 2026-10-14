#include "sprite_unit.hpp"

#include <core/resource/types/sprite.hpp>
#include <core/resource/types/shader.hpp>
#include <core/glwrappers/vertex_buffer.hpp>
#include <core/glwrappers/surface.hpp>
#include <core/draw/bindable.hpp>

namespace liqelligence::core::draw
{
    sprite_unit::sprite_unit(frect2d rect, const resource::sprite& sprite, const resource::shader& shader)
        : _rect(rect)
        , _sprite(sprite)
        , _shader(shader)
    {
    }

    frect2d sprite_unit::get_rect() const
    {
        return _rect;
    }

    const resource::sprite& sprite_unit::get_sprite() const
    {
        return _sprite;
    }

    const resource::shader& sprite_unit::get_shader() const
    {
        return _shader;
    }

    sprite_unit::hash_t sprite_unit::get_hash() const
    {
        auto result = (static_cast<hash_t>(_sprite.get_texture().get_handle()) << sizeof(hash_t) * 4u) | _shader.get_handle();
        return result;
    }

    std::generator<const action&> flush(const std::vector<sprite_unit>& units)
    {
        if (units.empty()) {
            co_return;
        }

        co_yield lambda_action([&units]()
            {
                auto& unit = units.front();

                scoped_bind binded_shader(unit.get_shader());
                binded_shader->set_uniform("u_screen_size", vector2d(1280.f, 720.f));

                scoped_bind binded_sprite(unit.get_sprite());

                gl::surface2d surface;
                scoped_bind binded_surface(surface);

                gl::vertex_buffer<frect2d, GL_ARRAY_BUFFER> rects_buffer(2u, 1u);
                scoped_bind binded_rects_buffer(rects_buffer);

                const auto rects = units
                    | std::views::transform([](const auto& it)
                        {
                            return it.get_rect();
                        })
                    | std::ranges::to<std::vector>();

                binded_rects_buffer->write_data(rects, GL_STREAM_DRAW);

                glDrawArraysInstanced(GL_TRIANGLES, 0, binded_surface->get_vertex_count(), units.size());
            });
    }
}

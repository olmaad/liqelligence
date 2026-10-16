#include "sprite_unit.hpp"

#include <core/resource/types/sprite.hpp>
#include <core/resource/types/shader.hpp>
#include <core/glwrappers/vertex_buffer.hpp>
#include <core/glwrappers/surface.hpp>
#include <core/context/context.hpp>
#include <core/draw/bindable.hpp>
#include <core/draw/screen.hpp>

namespace liqelligence::core::draw
{
    sprite_unit::sprite_unit(fvector2d pos, vector2d size, const resource::sprite& sprite, const resource::shader& shader)
        : _pos(pos)
        , _size(size)
        , _sprite(sprite)
        , _shader(shader)
    {
    }

    fvector2d sprite_unit::get_pos() const
    {
        return _pos;
    }

    vector2d sprite_unit::get_size() const
    {
        return _size;
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

        co_yield lambda_action([&units](settings settings)
            {
                auto& unit = units.front();

                scoped_bind binded_shader(unit.get_shader());
                binded_shader->set_uniform("u_discard", settings.pass_type == pass::stencil);
                context::get<screen>().fill_uniforms(*binded_shader);

                scoped_bind binded_sprite(unit.get_sprite());

                gl::surface2d surface;
                scoped_bind binded_surface(surface);

                gl::vertex_buffer<fvector4d, GL_ARRAY_BUFFER> rects_buffer({ {.index = 2u, .divisor = 1u } });
                scoped_bind binded_rects_buffer(rects_buffer);

                const auto rects = units
                    | std::views::transform([](const auto& it)
                        {
                            return fvector4d{ it.get_pos(), it.get_size() };
                        })
                    | std::ranges::to<std::vector>();

                binded_rects_buffer->write_data(rects, GL_STREAM_DRAW);

                glDrawArraysInstanced(GL_TRIANGLES, 0, binded_surface->get_vertex_count(), units.size());
            });
    }
}

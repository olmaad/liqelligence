#include "sprite_component.hpp"

#include <core/resource/library/sprite_library.hpp>
#include <core/resource/library/shader_library.hpp>
#include <core/resource/types/sprite.hpp>
#include <core/draw/units/sprite_unit.hpp>
#include <core/draw/drawer.hpp>
#include <core/context/context.hpp>

namespace liqelligence::game
{
    sprite_component::sprite_component(const std::string& sprite, const std::string& shader)
    {
        auto& sprites = core::context::get<core::resource::library>().get<core::resource::sprite_library>();
        _sprite = sprites.find(sprite);

        if (_sprite) {
            const auto size = _sprite->get_original_size();
            set_size(size);
        }

        auto& shaders = core::context::get<core::resource::library>().get<core::resource::shader_library>();
        _shader = shaders.find(shader);
    }

    void sprite_component::draw() const
    {
        if (!_sprite || !_shader) {
            return;
        }

        core::context::get<core::draw::drawer>().draw(_priority, core::draw::sprite_unit({ get_transform().get_pos(), _size }, *_sprite, *_shader));
    }

    core::draw::priority_t sprite_component::get_priority() const
    {
        return _priority;
    }

    void sprite_component::set_priority(core::draw::priority_t value)
    {
        _priority = value;
    }

    vector2d sprite_component::get_size() const
    {
        return _size;
    }

    void sprite_component::set_size(vector2d value)
    {
        _size = value;
    }
}

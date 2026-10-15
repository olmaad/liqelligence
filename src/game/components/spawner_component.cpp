#include "spawner_component.hpp"

#include <components/lifetime_component.hpp>
#include <components/sprite_component.hpp>
#include <components/move_component.hpp>
#include <core/component/storage.hpp>
#include <core/component/entity.hpp>
#include <core/math/math.hpp>

namespace liqelligence::game
{
    void spawner_component::update(float dt)
    {
        constexpr std::array<float, 5u> offsets{ -30.f, -15.f, 0.f, 15.f, 30.f };

        _timer += dt;

        while (_timer > 0.05f) {
            _timer -= 0.05f;

            auto& storage = core::context::get<core::component::storage>();
            auto& entity = storage.add<core::component::entity>();
            entity.get_transform().set_pos(get_transform().get_pos());

            auto& sprite = entity.get_or_add<game::sprite_component>("particle", "sprite_basic");
            sprite.set_priority(100u);
            sprite.set_size(sprite.get_size() * vector2d { 8, 8 });

            auto& move = entity.get_or_add<game::move_component>();
            move.set_speed({ offsets.at(_offset % offsets.size()) * 5.f, 300.f });
            move.set_acceleration({ -offsets.at(_offset % offsets.size()) / 3.f, -50.f });

            auto& timer = entity.get_or_add<game::lifetime_component>(12.f);

            _offset += 1u;
            if (_offset >= 1000u) {
                _offset = 0u;
            }
        }
    }
}

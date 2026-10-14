#include "prototype.hpp"

#include <components/sprite_component.hpp>
#include <components/move_component.hpp>
#include <components/sets.hpp>
#include <core/component/storage.hpp>
#include <core/component/entity.hpp>
#include <core/draw/drawer.hpp>
#include <core/math/math.hpp>
#include <core/context/context.hpp>

namespace liqelligence::prototype
{
    void setup_scene()
    {
        constexpr vector2d screen_size{ 1280, 720 };

        auto& storage = core::context::get<core::component::storage>();

        for (size_t it = 0u; it < 1u; ++it) {
            auto& sprite = storage.add<game::sprite_component>("test_sprite_1", "sprite_basic");
            sprite.set_priority(0u);
            sprite.set_size(screen_size);
        }

        for (size_t it = 0u; it < 8u; ++it) {
            constexpr auto size = vector2d{ 100, 100 };

            auto& entity = storage.add<core::component::entity>();

            auto& sprite = entity.get_or_add<game::sprite_component>("test_sprite_2", "sprite_basic");
            sprite.set_priority(100u);
            sprite.set_size(size);

            auto& move = entity.get_or_add<game::move_component>(static_cast<float>(it) / 8.f * static_cast<float>(std::numbers::pi) * 2.f);
        }
    }

    void update_scene(float dt)
    {
        const auto& storage = core::context::get<core::component::storage>();
        for (auto& it : storage.get_all<game::update_components>()) {
            it.update(dt);
        }
    }

    void draw_scene()
    {
        const auto& storage = core::context::get<core::component::storage>();
        for (const auto& it : storage.get_all<game::drawable_components>()) {
            it.draw();
        }

        core::context::get<core::draw::drawer>().flush();
    }
}

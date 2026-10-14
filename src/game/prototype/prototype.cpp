#include "prototype.hpp"

#include <components/sets.hpp>
#include <core/component/storage.hpp>
#include <core/component/entity.hpp>
#include <core/draw/drawer.hpp>
#include <core/context/context.hpp>

namespace liqelligence::prototype
{
    void setup_scene()
    {
        constexpr vector2d screen_size{ 1280, 720 };

        auto& storage = core::context::get<core::component::storage>();

        auto& entity = storage.add<core::component::entity>();

        auto& spawner = entity.get_or_add<game::spawner_component>();
        spawner.get_transform().set_pos({ 50.f, 360.f });
    }

    void update_scene(float dt)
    {
        const auto& storage = core::context::get<core::component::storage>();
        for (auto& it : storage.get_all<game::update_components>()) {
            it.update(dt);
        }

        core::context::update();
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

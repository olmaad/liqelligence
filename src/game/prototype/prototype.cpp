#include "prototype.hpp"

#include <gl/glew.h>
#include <components/sets.hpp>
#include <core/component/storage.hpp>
#include <core/component/entity.hpp>
#include <core/resource/manager.hpp>
#include <core/draw/screen.hpp>
#include <core/draw/drawer.hpp>
#include <core/context/context.hpp>

namespace
{
    using namespace liqelligence;

    void setup(core::application::window&)
    {
        auto& resources = core::context::get<core::resource::manager>();
        resources.load(core::resource::manager::load_mode::all);

        auto& storage = core::context::get<core::component::storage>();

        auto& entity = storage.add<core::component::entity>();

        auto& spawner = entity.get_or_add<game::spawner_component>();
        spawner.get_transform().set_pos({ 50.f, 200.f });
    }

    void update(float dt)
    {
        const auto& storage = core::context::get<core::component::storage>();
        for (auto& it : storage.get_all<game::update_components>()) {
            it.update(dt);
        }

        core::context::update();
    }

    void draw()
    {
        const auto& storage = core::context::get<core::component::storage>();
        for (const auto& it : storage.get_all<game::drawable_components>()) {
            it.draw();
        }

        core::context::get<core::draw::drawer>().flush();
    }

    void on_size_changed(vector2d size)
    {
        auto& screen = core::context::get<core::draw::screen>();
        screen.set_size(size);
    }
}

namespace liqelligence::prototype
{
    core::application::window_delegate create_delegate()
    {
        core::application::window_delegate delegate{
            .onCreate = setup,

            .onUpdate = update,
            .onDraw = draw,

            .onScreenSizeChanged = on_size_changed
        };

        return delegate;
    }
}

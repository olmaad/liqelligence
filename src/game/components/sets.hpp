#pragma once

#include <core/component/interface_adapter.hpp>
#include <core/component/interface/draw_component.hpp>
#include <core/component/interface/update_component.hpp>

#include <components/move_component.hpp>
#include <components/sprite_component.hpp>
#include <components/spawner_component.hpp>
#include <components/lifetime_component.hpp>

namespace liqelligence::game
{
    using drawable_components = core::component::interface_adapter<core::component::i_draw_component, sprite_component>;
    using update_components = core::component::interface_adapter<core::component::i_update_component, spawner_component, move_component, lifetime_component>;
}

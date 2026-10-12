#pragma once

#include <core/component/interface_adapter.hpp>
#include <core/component/interface/draw_component.hpp>
#include <core/component/interface/update_component.hpp>

namespace liqelligence::game
{
    class sprite_component;
    class move_component;

    using drawable_components = core::component::interface_adapter<core::component::i_draw_component, sprite_component>;
    using update_components = core::component::interface_adapter<core::component::i_update_component, move_component>;
}

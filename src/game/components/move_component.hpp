#pragma once

#include <core/component/interface/update_component.hpp>
#include <core/component/component.hpp>

namespace liqelligence::game
{
    class move_component : public core::component::component, public core::component::i_update_component
    {
    public:
        move_component(core::component::component_ref sprite_ref, float offset);

        void update(float dt) override;

    private:
        core::component::component_ref _sprite_ref;
        float _degree = 0.f;

    };
}

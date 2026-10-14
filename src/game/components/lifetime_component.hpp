#pragma once

#include <core/component/interface/update_component.hpp>
#include <core/component/component.hpp>

namespace liqelligence::game
{
    class lifetime_component : public core::component::component, public core::component::i_update_component
    {
    public:
        lifetime_component(float time);

        void update(float dt) override;

    private:
        float _timer = 0.f;

    };
}

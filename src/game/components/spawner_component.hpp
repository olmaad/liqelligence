#pragma once

#include <core/component/interface/update_component.hpp>
#include <core/component/component.hpp>

namespace liqelligence::game
{
    class spawner_component : public core::component::component, public core::component::i_update_component
    {
    public:
        void update(float dt) override;

    private:
        float _timer = 0.f;
        size_t _offset = 0u;

    };
}

#pragma once

#include <core/component/interface/update_component.hpp>
#include <core/component/component.hpp>
#include <core/math/types.hpp>

namespace liqelligence::game
{
    class move_component : public core::component::component, public core::component::i_update_component
    {
    public:
        move_component();

        void update(float dt) override;

        fvector2d get_speed() const;
        void set_speed(fvector2d value);

        fvector2d get_acceleration() const;
        void set_acceleration(fvector2d value);

    private:
        fvector2d _speed;
        fvector2d _acceleration;

    };
}

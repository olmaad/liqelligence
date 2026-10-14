#include "move_component.hpp"

#include <core/component/storage.hpp>
#include <core/context/context.hpp>
#include <core/math/math.hpp>

namespace liqelligence::game
{
    move_component::move_component()
    {
    }

    void move_component::update(float dt)
    {
        _speed = _speed + _acceleration * dt;

        auto transform = get_transform();
        transform.set_pos(transform.get_pos() + _speed * dt);
    }

    fvector2d move_component::get_speed() const
    {
        return _speed;
    }

    void move_component::set_speed(fvector2d value)
    {
        _speed = value;
    }

    fvector2d move_component::get_acceleration() const
    {
        return _acceleration;
    }

    void move_component::set_acceleration(fvector2d value)
    {
        _acceleration = value;
    }
}

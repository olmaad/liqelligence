#include "lifetime_component.hpp"

#include <core/component/entity.hpp>

namespace liqelligence::game
{
    lifetime_component::lifetime_component(float time)
        : _timer(time)
    {
    }

    void lifetime_component::update(float dt)
    {
        if (!_entity) {
            return;
        }

        _timer -= dt;

        if (_timer <= 0.f) {
            if (auto* entity = find_entity()) {
                entity->destroy();
            }
        }
    }
}

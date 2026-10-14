#include "move_component.hpp"

#include <core/component/storage.hpp>
#include <core/context/context.hpp>
#include <core/math/math.hpp>

namespace liqelligence::game
{
    move_component::move_component(float offset)
        : _degree(offset)
    {
    }

    void move_component::update(float dt)
    {
        _degree += dt * (std::numbers::pi * 2.f / 10.f);

        const auto& storage = core::context::get<core::component::storage>();
        constexpr vector2d screen_size{ 1280, 720 };

        constexpr auto size = vector2d{ 100, 100 };
        const auto middle = (screen_size - size) / vector2d{ 2, 2 };
        const auto offset = vector2d{ 300, 300 } *vector2d{ std::cos(_degree), std::sin(_degree) };

        auto transform = get_transform();
        transform.set_pos(middle + offset);
    }
}

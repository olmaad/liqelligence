#pragma once

#include <core/context/item.hpp>
#include <core/draw/types.hpp>
#include <core/draw/layer.hpp>

namespace liqelligence::core::draw
{
    class drawer : public context_item
    {
    public:
        drawer();

        template<typename t_unit>
        void draw(priority_t priority, t_unit&& unit)
        {
            auto& layer = _layers[priority];
            layer.draw(std::forward<t_unit>(unit));
        }

        void flush();

    private:
        void set_stencil_state(bool state);
        void set_blending_state(bool state);

    private:
        std::unordered_map<priority_t, layer> _layers;

    };
}

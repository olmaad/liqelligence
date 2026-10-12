#pragma once

#include <core/draw/types.hpp>
#include <core/draw/layer.hpp>
#include <unordered_map>

namespace liqelligence::core::draw
{
    class drawer
    {
    public:
        drawer();

        static drawer& get();

        template<typename t_unit>
        void draw(priority_t priority, t_unit&& unit)
        {
            auto& layer = _layers[priority];
            layer.draw(std::forward<t_unit>(unit));
        }

        void flush();

    private:
        std::unordered_map<priority_t, layer> _layers;

    };
}

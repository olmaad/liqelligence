#include "drawer.hpp"

#include <core/resource/types/sprite.hpp>
#include <core/resource/types/shader.hpp>
#include <core/draw/unit.hpp>
#include <algorithm>
#include <ranges>

namespace liqelligence::core::draw
{
    drawer::drawer()
    {
        _layers.reserve(100u);
    }

    drawer& drawer::get()
    {
        static drawer instance;
        return instance;
    }

    void drawer::flush()
    {
        auto layers_sorted = _layers
            | std::views::transform([](const auto& it) { return std::make_pair(it.first, &it.second); })
            | std::ranges::to<std::vector>();

        std::ranges::stable_sort(layers_sorted, [](const auto& left, const auto& right) { return left.first < right.first; });

        for (const auto& [_, layer] : layers_sorted) {
            for (const auto& action : layer->flush()) {
                action.apply();
            }
        }

        _layers.clear();
    }
}

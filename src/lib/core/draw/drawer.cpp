#include "drawer.hpp"

#include <gl/glew.h>
#include <core/resource/types/sprite.hpp>
#include <core/resource/types/shader.hpp>
#include <core/draw/unit.hpp>

namespace liqelligence::core::draw
{
    drawer::drawer()
    {
        _layers.reserve(100u);

        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glStencilMask(0xFF);
        glStencilFunc(GL_EQUAL, 0, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

        set_stencil_state(false);
        set_blending_state(true);
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

    void drawer::set_stencil_state(bool state)
    {
        if (state) {
            glEnable(GL_STENCIL_TEST);
        }
        else {
            glDisable(GL_STENCIL_TEST);
        }
    }

    void drawer::set_blending_state(bool state)
    {
        if (state) {
            glEnable(GL_BLEND);
        }
        else {
            glDisable(GL_BLEND);
        }
    }
}

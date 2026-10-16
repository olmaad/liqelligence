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
    }

    void drawer::flush(settings settings)
    {
        setup_pass(settings.pass_type);

        auto layers_sorted = _layers
            | std::views::transform([](const auto& it) { return std::make_pair(it.first, &it.second); })
            | std::ranges::to<std::vector>();

        std::ranges::stable_sort(layers_sorted, [type = settings.pass_type](const auto& left, const auto& right)
            {
                return type == pass::blend
                    ? left.first < right.first
                    : left.first > right.first;
            });

        for (const auto& [_, layer] : layers_sorted) {
            for (const auto& action : layer->flush()) {
                action.apply(settings);
            }
        }

        _layers.clear();

        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void drawer::setup_pass(pass type)
    {
        set_stencil_state(type == pass::stencil);
        set_blending_state(type == pass::blend);
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

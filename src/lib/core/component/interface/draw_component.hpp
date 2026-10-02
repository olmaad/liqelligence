#pragma once

namespace liqelligence::core::component
{
    class i_draw_component
    {
    public:
        virtual void draw() const = 0;
    };
}

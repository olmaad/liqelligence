#pragma once

namespace liqelligence::core::component
{
    /*!
    * Drawable component interface. Must be used with interface_adapter
    */
    class i_draw_component
    {
    public:
        virtual void draw() const = 0;
    };
}

#pragma once

namespace liqelligence::core::component
{
    /*!
    * Updateable component interface. Must be used with interface_adapter
    */
    class i_update_component
    {
    public:
        virtual void update(float dt) = 0;
    };
}

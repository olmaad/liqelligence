#pragma once

namespace liqelligence::core::component
{
    class i_update_component
    {
    public:
        virtual void update(float dt) = 0;
    };
}

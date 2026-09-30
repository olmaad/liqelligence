#pragma once

#include "component_ref.hpp"

namespace liqelligence::core::component
{
    class component
    {
        template<typename t_component>
        friend class bucket;

    public:
        virtual void update(float dt);
        virtual void draw();

        component_ref get_ref() const;

    private:
        component_full_ref _ref;

    };
}

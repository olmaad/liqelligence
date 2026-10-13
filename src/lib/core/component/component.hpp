#pragma once

#include "component_ref.hpp"

namespace liqelligence::core::component
{
    class entity;

    class component
    {
        template<typename t_component>
        friend class bucket;

    public:
        component() = default;
        component(component&&) = default;
        component(const component&) = delete;
        component& operator=(component&&) = default;
        component& operator=(const component&) = delete;

        component_ref get_ref() const;

        component_ref get_entity() const;
        void set_entity(component_ref value);

        entity* find_entity() const;

    protected:
        component_ref _entity;

    private:
        component_full_ref _ref;

    };
}

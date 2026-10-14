#pragma once

#include <core/component/component_ref.hpp>
#include <core/math/types/transform.hpp>

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

        transform_proxy<const transform> get_transform() const;
        transform_proxy<transform> get_transform();

    protected:
        component_ref _entity;

    private:
        component_full_ref _ref;

    };
}

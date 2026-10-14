#include "component.hpp"

#include <core/component/storage.hpp>
#include <core/component/entity.hpp>
#include <core/context/context.hpp>

namespace liqelligence::core::component
{
    component_ref component::get_ref() const
    {
        return _ref;
    }

    component_ref component::get_entity() const
    {
        return _entity;
    }

    void component::set_entity(component_ref value)
    {
        _entity = value;
    }

    entity* component::find_entity() const
    {
        return _entity ? context::get<storage>().find<entity>(_entity) : nullptr;
    }

    transform_proxy<const transform> component::get_transform() const
    {
        const auto* entity = find_entity();
        return entity ? transform_proxy<const transform>(entity->get_transform()) : transform_proxy<const transform>{};
    }

    transform_proxy<transform> component::get_transform()
    {
        auto* entity = find_entity();
        return entity ? transform_proxy<transform>(entity->get_transform()) : transform_proxy<transform>{};
    }
}

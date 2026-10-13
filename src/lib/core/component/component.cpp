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
        return context::get<storage>().find<entity>(_entity);
    }
}

#include "component_ref.hpp"

namespace liqelligence::core::component
{
    component_ref::component_ref()
    {
    }

    component_ref::component_ref(component_type_t type, component_id_t id)
        : _type(type)
        , _id(id)
    {
    }

    component_ref::operator bool() const
    {
        return valid();
    }

    bool component_ref::valid() const
    {
        return _type && _id;
    }

    component_type_t component_ref::get_type() const
    {
        return _type;
    }

    component_id_t component_ref::get_id() const
    {
        return _id;
    }

    void component_ref::set_type(component_type_t value)
    {
        _type = value;
    }

    void component_ref::set_id(component_id_t value)
    {
        _id = value;
    }

    component_bucket_index_t component_full_ref::get_bucket_index() const
    {
        return _bucket_index;
    }

    void component_full_ref::set_bucket_index(component_bucket_index_t value)
    {
        _bucket_index = value;
    }
}

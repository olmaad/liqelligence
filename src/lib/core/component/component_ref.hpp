#pragma once

#include <core/component/component_type.hpp>

namespace liqelligence::core::component
{
    using component_id_t = size_t;

    class component_ref
    {
        template<typename t_component>
        friend class bucket;

    public:
        component_ref();
        component_ref(component_type_t type, component_id_t id);

        operator bool() const;

        bool valid() const;

        component_type_t get_type() const;
        component_id_t get_id() const;

    protected:
        void set_type(component_type_t value);
        void set_id(component_id_t value);

    protected:
        component_type_t _type = 0u;
        component_id_t _id = 0u;
    };

    using component_bucket_index_t = size_t;

    class component_full_ref : public component_ref
    {
        template<typename t_component>
        friend class bucket;

    protected:
        component_bucket_index_t get_bucket_index() const;
        void set_bucket_index(component_bucket_index_t value);

    protected:
        component_bucket_index_t _bucket_index = 0u;
    };
}

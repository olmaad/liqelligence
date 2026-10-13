#pragma once

#include <core/utils/multitype_container.hpp>
#include <core/context/item.hpp>

namespace liqelligence::core
{
    class context
    {
    public:
        using instance_type = multitype_container<context_item>;

    public:
        template<multitype_container_item_type<instance_type::base_type> t_item>
        static t_item& get()
        {
            return instance().get<t_item>();
        }

        static instance_type& instance();
        static void recreate();

    private:
        static std::unique_ptr<instance_type> _instance;

    };
}

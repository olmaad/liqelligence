#pragma once

#include <core/utils/multitype_container.hpp>
#include <core/context/item.hpp>

namespace liqelligence::core
{
    class context
    {
    public:
        using container_type = multitype_container<context_item>;

    public:
        context();
        ~context() noexcept;

        static bool available();

        template<multitype_container_item_type<container_type::base_type> t_item>
        static t_item& get()
        {
            return instance()._container.get<t_item>();
        }

        template<multitype_container_item_type<container_type::base_type> t_item>
        static t_item* find()
        {
            if (auto* ptr = instance_ptr()) {
                return ptr->_container.find<t_item>();
            }

            return {};
        }

        static void recreate();

    private:
        static context& instance();
        static context* instance_ptr();

    private:
        static bool _available;
        static std::unique_ptr<context> _instance;

        container_type _container;

    };
}

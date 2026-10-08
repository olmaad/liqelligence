#pragma once

#include <core/component/component_type.hpp>
#include <type_traits>
#include <generator>
#include <concepts>

namespace liqelligence::core::component
{
    template<typename t_interface, typename... t_components>
    class interface_adapter;

    template<typename t_interface>
    class interface_adapter<t_interface>
    {
        template<typename t_interface, typename... t_components>
        friend class interface_adapter;

    private:
        interface_adapter() {}

        template<typename t_storage>
        std::generator<t_interface&> get_all(const t_storage&) const { co_return; }
    };

    template<typename t_interface, component_type t_component, typename... t_components> requires std::derived_from<t_component, t_interface>
    class interface_adapter<t_interface, t_component, t_components...>
    {
    public:
        interface_adapter()
        {
        }

        template<typename t_storage>
        std::generator<t_interface&> get_all(const t_storage& storage)
        {
            auto current = storage.get_all<t_component>();
            for (auto& it : current) {
                co_yield static_cast<t_interface&>(it);
            }

            interface_adapter<t_interface, t_components...> tail;
            for (auto& it : tail.get_all(storage)) {
                co_yield static_cast<t_interface&>(it);
            }
        }

    };

    template<typename t> struct is_interface_adapter_type : std::false_type {};
    template<typename... t_args> struct is_interface_adapter_type<interface_adapter<t_args...>> : std::true_type {};
    template<typename t_adapter> concept interface_adapter_type = is_interface_adapter_type<t_adapter>::value
        && std::is_default_constructible_v<t_adapter>;

}

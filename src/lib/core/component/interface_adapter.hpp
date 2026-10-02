#pragma once

#include <generator>

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

    template<typename t_interface, typename t_component, typename... t_components>
    class interface_adapter<t_interface, t_component, t_components...>
    {
        static_assert(std::derived_from<t_component, component>, "t_component must be derived from component");
        static_assert(std::derived_from<t_component, t_interface>, "t_component must be derived from t_interface");

    public:
        using interface_type = t_interface;

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
    template<typename t_adapter> concept interface_adapter_type = is_interface_adapter_type<t_adapter>::value;

}

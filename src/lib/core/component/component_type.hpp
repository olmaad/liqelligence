#pragma once

#include <concepts>

namespace liqelligence::core::component
{
    class component;

    using component_type_t = size_t;

    namespace detail
    {
        extern component_type_t type_count;
        constexpr component_type_t type_count_max = 128u;
    }

    template<typename t_component>
    component_type_t get_type_of()
    {
        static auto id = detail::type_count++;
        return id;
    }

    template<typename t_component>
    concept component_type = std::derived_from<t_component, component>
        && std::swappable<t_component>;
}

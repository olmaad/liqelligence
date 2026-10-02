#pragma once

namespace liqelligence::core::component
{
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
    class component_type
    {
    public:
        component_type()
            : _id(get_type_of<t_component>())
        {
        }

        operator component_type_t() const
        {
            return _id;
        }

    private:
        const component_type_t _id;
    };
}

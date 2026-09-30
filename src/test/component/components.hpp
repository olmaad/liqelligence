#pragma once

#include <core/component/component.hpp>

namespace liqelligence::test
{
    class simple_component : public core::component::component
    {
    };

    class non_existing_component : public core::component::component
    {
    };

    class component_a : public core::component::component
    {
    public:
        component_a(int i_a, char i_b)
            : a(i_a)
            , b(i_b)
        {
        }

        bool operator==(const component_a& other) const
        {
            return a == other.a && b == other.b;
        }

    public:
        int a;
        char b;
    };

    class component_b : public core::component::component
    {
    public:
        component_b()
            : a(6)
            , b('9')
        {
        }

        component_b(int i_a, char i_b)
            : a(i_a)
            , b(i_b)
        {
        }

        bool operator==(const component_b& other) const
        {
            return a == other.a && b == other.b;
        }

    public:
        int a;
        char b;
    };

    template<typename t_arg>
    class simple_templated_component : public core::component::component
    {
    };

    template<typename t_arg>
    class templated_component : public core::component::component
    {
    public:
        templated_component(t_arg i_a)
            : a(i_a)
        {
        }

        bool operator==(const templated_component<t_arg>& other) const
        {
            return a == other.a;
        }

    public:
        t_arg a;
    };
}
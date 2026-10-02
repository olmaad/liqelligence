#pragma once

#include <core/component/interface/update_component.hpp>
#include <core/component/interface/draw_component.hpp>
#include <core/component/component.hpp>

namespace liqelligence::test
{
    class simple_component : public core::component::component
    {
    };

    class non_existing_component : public core::component::component
    {
    };

    class draw_component_a : public core::component::component, public core::component::i_draw_component
    {
    public:
        void draw() const override {}

    };

    class draw_component_b : public core::component::component, public core::component::i_draw_component
    {
    public:
        void draw() const override {}
    };

    class update_component_a : public core::component::component, public core::component::i_update_component
    {
    public:
        void update(float dt) override { ++update_count; };

    public:
        uint32_t update_count = 0u;
    };

    class update_component_b : public core::component::component, public core::component::i_update_component
    {
    public:
        void update(float dt) override { ++update_count; };

    public:
        uint32_t update_count = 0u;
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
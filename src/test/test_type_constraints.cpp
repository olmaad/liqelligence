#include <catch2/catch_test_macros.hpp>

#include <component/components.hpp>
#include <core/component/storage.hpp>
#include <core/component/interface_adapter.hpp>

namespace liqelligence::test
{
    TEST_CASE("Concepts", "[type_constrains]")
    {
        SECTION("Component type")
        {
            REQUIRE(core::component::component_type<core::component::component>);
            REQUIRE(core::component::component_type<simple_component>);
            REQUIRE(core::component::component_type<update_component_a>);
            REQUIRE(core::component::component_type<simple_templated_component<int>>);

            REQUIRE(!core::component::component_type<core::component::i_draw_component>);
            REQUIRE(!core::component::component_type<not_component_a>);
            REQUIRE(!core::component::component_type<not_component_b>);
            REQUIRE(!core::component::component_type<int>);
        }

        SECTION("Component interface adapter type")
        {
            REQUIRE(core::component::interface_adapter_type<core::component::interface_adapter<core::component::i_draw_component, draw_component_a>>);
            REQUIRE(core::component::interface_adapter_type<core::component::interface_adapter<core::component::i_draw_component, draw_component_a, draw_component_b>>);

            REQUIRE(!core::component::interface_adapter_type<core::component::storage>);
            REQUIRE(!core::component::interface_adapter_type<core::component::range<simple_component>>);
            REQUIRE(!core::component::interface_adapter_type<core::component::interface_adapter<simple_component>>);
            REQUIRE(!core::component::interface_adapter_type<core::component::interface_adapter<core::component::i_draw_component>>);
        }
    }
}

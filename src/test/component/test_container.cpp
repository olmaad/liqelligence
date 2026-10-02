#include <catch2/catch_test_macros.hpp>

#include <component/components.hpp>
#include <core/component/storage.hpp>
#include <core/component/interface_adapter.hpp>

namespace
{
    using namespace liqelligence;

    core::component::storage create_test_storage() {
        auto storage = core::component::storage();

        for (int it = 0; it < 3; ++it) {
            storage.add<test::draw_component_a>();
        }

        for (int it = 0; it < 10; ++it) {
            storage.add<test::component_a>(1 + it, 'a' + it);
        }

        for (int it = 0; it < 7; ++it) {
            storage.add<test::draw_component_b>();
        }

        for (int it = 0; it < 5; ++it) {
            storage.add<test::update_component_a>();
        }

        for (int it = 0; it < 20; ++it) {
            storage.add<test::component_b>(1 + it, 'a' + it);
        }

        for (int it = 0; it < 15; ++it) {
            storage.add<test::update_component_b>();
        }

        return storage;
    }

    using drawable_components = core::component::interface_adapter<core::component::i_draw_component, test::draw_component_a, test::draw_component_b>;
    using update_components = core::component::interface_adapter<core::component::i_update_component, test::update_component_a, test::update_component_b>;
}

namespace liqelligence::test
{
    TEST_CASE("Interface adapter", "[component][container]")
    {
        const auto storage = create_test_storage();

        SECTION("Adapter get single type")
        {
            std::vector<const core::component::i_draw_component*> compare_to;
            compare_to.append_range(storage.get_all<draw_component_b>() | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }));

            const auto components = core::component::interface_adapter<core::component::i_draw_component, test::draw_component_b>().get_all(storage) | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }) | std::ranges::to<std::vector>();
            REQUIRE(compare_to.size() == components.size());

            for (const auto [compare, it] : std::views::zip(compare_to, components)) {
                REQUIRE(compare == it);
            }
        }

        SECTION("Adapter get multiple types")
        {
            std::vector<const core::component::i_draw_component*> compare_to;
            compare_to.append_range(storage.get_all<draw_component_a>() | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }));
            compare_to.append_range(storage.get_all<draw_component_b>() | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }));

            const auto components = drawable_components().get_all(storage) | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }) | std::ranges::to<std::vector>();
            REQUIRE(compare_to.size() == components.size());

            for (const auto [compare, it] : std::views::zip(compare_to, components)) {
                REQUIRE(compare == it);
            }
        }

        SECTION("Adapter vs storage")
        {
            const auto adapter_components = drawable_components().get_all(storage) | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }) | std::ranges::to<std::vector>();
            const auto storage_components = storage.get_all<drawable_components>() | std::views::transform([](const auto& it) -> const core::component::i_draw_component* { return &it; }) | std::ranges::to<std::vector>();
            REQUIRE(adapter_components.size() == storage_components.size());

            for (const auto [adapter_comp, storage_comp] : std::views::zip(adapter_components, storage_components)) {
                REQUIRE(adapter_comp == storage_comp);
            }
        }

        SECTION("Non const get")
        {
            for (const auto& it : storage.get_all<update_component_a>()) {
                REQUIRE(it.update_count == 0u);
            }

            size_t size = 0u;
            for (auto& it : storage.get_all<update_components>()) {
                ++size;
                it.update(1.f);
            }

            REQUIRE(size == 20u);

            for (const auto& it : storage.get_all<update_component_a>()) {
                REQUIRE(it.update_count == 1u);
            }
        }
    }
}

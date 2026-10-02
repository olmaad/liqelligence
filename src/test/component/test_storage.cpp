#include <catch2/catch_test_macros.hpp>

#include <component/components.hpp>
#include <core/component/storage.hpp>

namespace
{
    using namespace liqelligence;

    core::component::storage create_test_storage() {
        auto storage = core::component::storage();

        for (int it = 0; it < 4; ++it) {
            storage.add<test::simple_component>();
        }

        for (int it = 0; it < 10; ++it) {
            storage.add<test::component_a>(1 + it, 'a' + it);
        }

        storage.add<test::component_b>();
        storage.add<test::component_b>(98, 'g');

        for (int it = 0; it < 5; ++it) {
            storage.add<test::simple_templated_component<int>>();
        }

        for (int it = 0; it < 10; ++it) {
            storage.add<test::simple_templated_component<char>>();
        }

        for (int it = 0; it < 15; ++it) {
            storage.add<test::templated_component<int>>(it);
        }

        return storage;
    }
}

namespace liqelligence::test
{
    TEST_CASE("Component storage add", "[component][storage]")
    {
        const auto storage = create_test_storage();

        SECTION("Simple component check")
        {
            REQUIRE(storage.get_all<simple_component>().size() == 4u);
        }

        SECTION("Component a check")
        {
            const auto components = storage.get_all<component_a>();
            REQUIRE(components.size() == 10u);
            for (int it = 0; it < components.size(); ++it) {
                const auto& component = components[it];
                REQUIRE(component.a == 1 + it);
                REQUIRE(component.b == 'a' + it);
            }
        }

        SECTION("Component b check")
        {
            const auto components = storage.get_all<component_b>();
            REQUIRE(components.size() == 2u);
            REQUIRE(components[0].a == 6);
            REQUIRE(components[0].b == '9');
            REQUIRE(components[1].a == 98);
            REQUIRE(components[1].b == 'g');
        }

        SECTION("Simple templated component check")
        {
            REQUIRE(storage.get_all<simple_templated_component<int>>().size() == 5u);
            REQUIRE(storage.get_all<simple_templated_component<char>>().size() == 10u);
        }

        SECTION("Templated component check")
        {
            const auto components = storage.get_all<templated_component<int>>();
            REQUIRE(components.size() == 15u);
            for (int it = 0; it < components.size(); ++it) {
                REQUIRE(components[it].a == it);
            }
        }
    }

    TEST_CASE("Component storage find", "[component][storage]")
    {
        auto storage = create_test_storage();

        SECTION("Empty find")
        {
            const auto* found = storage.find<simple_component>(core::component::component_ref{});
            REQUIRE_FALSE(found);
        }

        SECTION("Wrong type find")
        {
            const auto ref = storage.get_all<simple_component>().front().get_ref();
            REQUIRE(ref);

            const auto* found = storage.find<component_a>(ref);
            REQUIRE_FALSE(found);
        }

        SECTION("Non existing find")
        {
            const auto ref = storage.get_all<simple_component>().front().get_ref();
            REQUIRE(ref);

            const auto* found = storage.find<non_existing_component>(ref);
            REQUIRE_FALSE(found);
        }

        SECTION("Find removed")
        {
            const auto ref1 = storage.get_all<simple_component>().front().get_ref();
            REQUIRE(ref1);

            storage.remove(ref1);

            const auto* found1 = storage.find<simple_component>(ref1);
            REQUIRE_FALSE(found1);

            const auto ref2 = storage.get_all<simple_component>().front().get_ref();
            REQUIRE(ref2);

            storage.remove_all<simple_component>();

            const auto* found2 = storage.find<simple_component>(ref2);
            REQUIRE_FALSE(found2);
        }

        SECTION("Find comparsion")
        {
            const auto components = storage.get_all<component_a>();
            for (const auto& it : components) {
                const auto ref = it.get_ref();
                REQUIRE(ref);

                const auto* found = storage.find<component_a>(ref);
                REQUIRE(found);
                REQUIRE(it == (*found));
            }
        }

        SECTION("Find consistency")
        {
            const auto components = storage.get_all<component_a>();

            const auto front = components.front();
            const auto front_ref = front.get_ref();
            REQUIRE(front_ref);
            const auto back = components.back();
            const auto back_ref = back.get_ref();
            REQUIRE(back_ref);

            const auto ref = components[3].get_ref();
            REQUIRE(ref);

            storage.remove(ref);

            const auto* found_front = storage.find<component_a>(front_ref);
            REQUIRE(found_front);
            REQUIRE(front == (*found_front));

            const auto* found_back = storage.find<component_a>(back_ref);
            REQUIRE(found_back);
            REQUIRE(back == (*found_back));
        }
    }

    TEST_CASE("Component storage remove", "[component][storage]")
    {
        auto storage = create_test_storage();

        SECTION("Remove empty ref")
        {
            REQUIRE_NOTHROW(storage.remove(core::component::component_ref{}));
        }

        SECTION("Remove non existing")
        {
            REQUIRE_NOTHROW(storage.remove(non_existing_component{}));
            REQUIRE_NOTHROW(storage.remove_all<non_existing_component>());
        }

        SECTION("Double remove")
        {
            const auto before = storage.get_all<simple_component>();
            REQUIRE(before.size() == 4u);

            const auto ref = before.front().get_ref();
            REQUIRE(ref);

            storage.remove(ref);
            REQUIRE_NOTHROW(storage.remove(ref));

            const auto after = storage.get_all<simple_component>();
            REQUIRE(after.size() == 3u);
        }

        SECTION("Remove count")
        {
            const auto before = storage.get_all<simple_component>();
            REQUIRE(before.size() == 4u);

            storage.remove(before.front());

            const auto after = storage.get_all<simple_component>();
            REQUIRE(after.size() == 3u);
        }

        SECTION("Remove all count")
        {
            const auto before = storage.get_all<simple_component>();
            REQUIRE(before.size() == 4u);

            storage.remove_all<simple_component>();

            const auto after = storage.get_all<simple_component>();
            REQUIRE(after.empty());
        }

        SECTION("Remove all side effects")
        {
            const auto check_a = [&storage]() {
                const auto components = storage.get_all<component_a>();
                REQUIRE(components.size() == 10u);
                for (int it = 0; it < components.size(); ++it) {
                    const auto& component = components[it];
                    REQUIRE(component.a == 1 + it);
                    REQUIRE(component.b == 'a' + it);
                }
                };

            const auto check_t = [&storage]() {
                const auto components = storage.get_all<templated_component<int>>();
                REQUIRE(components.size() == 15u);
                for (int it = 0; it < components.size(); ++it) {
                    REQUIRE(components[it].a == it);
                }
                };

            check_a();
            check_t();

            storage.remove_all<simple_component>();
            storage.remove_all<component_b>();

            check_a();
            check_t();
        }

        SECTION("Reset count")
        {
            const auto before = storage.get_all<simple_component>();
            REQUIRE(before.size() == 4u);

            storage.reset();

            const auto after = storage.get_all<simple_component>();
            REQUIRE(after.empty());
        }
    }
}
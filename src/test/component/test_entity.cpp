#include <catch2/catch_test_macros.hpp>

#include <component/components.hpp>
#include <core/component/storage.hpp>
#include <core/component/entity.hpp>
#include <core/context/context.hpp>

namespace
{
    using namespace liqelligence;

    void prepare()
    {
        core::context::recreate();
    }
}

namespace liqelligence::test
{
    TEST_CASE("Component entity", "[component][entity]")
    {
        prepare();

        auto& storage = core::context::get<core::component::storage>();

        SECTION("Simple entity")
        {
            auto& entity = storage.add<core::component::entity>();
            const auto ref1 = entity.get_or_add<simple_component>().get_ref();
            const auto ref2 = entity.get_or_add<component_a>(11, '2').get_ref();
            const auto ref3 = entity.get_or_add<component_b>().get_ref();

            REQUIRE(entity.has<simple_component>());
            REQUIRE(storage.has(ref1));
            REQUIRE(entity.has<component_a>());
            REQUIRE(storage.has(ref2));
            REQUIRE(entity.has<component_b>());
            REQUIRE(storage.has(ref3));
        }

        SECTION("Entity destruction")
        {
            auto& entity = storage.add<core::component::entity>();

            const auto entity_ref = entity.get_ref();
            const auto ref1 = entity.get_or_add<simple_component>().get_ref();
            const auto ref2 = entity.get_or_add<draw_component_a>().get_ref();

            REQUIRE(storage.has(entity_ref));
            REQUIRE(storage.has(ref1));
            REQUIRE(storage.has(ref2));

            storage.remove(entity_ref);

            REQUIRE(!storage.has(entity_ref));
            REQUIRE(!storage.has(ref1));
            REQUIRE(!storage.has(ref2));
        }

        SECTION("Recurse entity")
        {
            auto& root_entity = storage.add<core::component::entity>();
            const auto root_ref = root_entity.get_ref();

            auto ref = root_ref;
            for (size_t it = 0u; it < 50u; ++it) {
                if (auto* entity = storage.find<core::component::entity>(ref)) {
                    entity->get_or_add<simple_component>();
                    entity->get_or_add<draw_component_a>();

                    ref = entity->get_or_add<core::component::entity>().get_ref();
                }
            }

            REQUIRE(storage.get_all<core::component::entity>().size() == 51u);

            ref = root_ref;
            for (size_t it = 0u; it < 50u; ++it) {
                if (auto* entity = storage.find<core::component::entity>(ref)) {
                    REQUIRE(entity->has<simple_component>());
                    REQUIRE(entity->has<draw_component_a>());

                    const auto* child = entity->find<core::component::entity>();
                    REQUIRE(child);

                    ref = child->get_ref();
                }
            }

            auto* entity = storage.find<core::component::entity>(ref);
            REQUIRE(entity);
            REQUIRE(!entity->has<simple_component>());
            REQUIRE(!entity->has<draw_component_a>());
        }

        SECTION("Recurse entity destruction")
        {
            auto& root_entity = storage.add<core::component::entity>();
            const auto root_ref = root_entity.get_ref();

            auto ref = root_ref;
            for (size_t it = 0u; it < 2u; ++it) {
                if (auto* entity = storage.find<core::component::entity>(ref)) {
                    entity->get_or_add<simple_component>();

                    ref = entity->get_or_add<core::component::entity>().get_ref();
                }
            }
            REQUIRE(storage.get_all<core::component::entity>().size() == 3u);

            storage.remove(root_ref);
            REQUIRE(storage.get_all<core::component::entity>().size() == 0u);
        }

        SECTION("Entity get or add")
        {
            auto& entity = storage.add<core::component::entity>();

            const auto ref1 = entity.get_or_add<component_a>(1, '1').get_ref();
            const auto ref2 = entity.get_or_add<component_a>(2, '2').get_ref();

            REQUIRE(storage.get_all<component_a>().size() == 1u);
            REQUIRE(ref1 == ref2);

            const auto* component = storage.find<component_a>(ref1);
            REQUIRE(component->a == 1);
            REQUIRE(component->b == '1');
        }

        SECTION("Entity ownership")
        {
            auto& root_entity = storage.add<core::component::entity>();
            const auto root_ref = root_entity.get_ref();

            const auto ref1 = root_entity.get_or_add<simple_component>().get_ref();
            const auto ref2 = root_entity.get_or_add<component_a>(4, '2').get_ref();
            const auto ref3 = root_entity.get_or_add<component_b>().get_ref();

            auto& child_entity = root_entity.get_or_add<core::component::entity>();
            const auto child_ref = child_entity.get_ref();

            const auto ref4 = child_entity.get_or_add<update_component_a>().get_ref();
            const auto ref5 = child_entity.get_or_add<update_component_b>().get_ref();

            const auto check_owner = [&storage](core::component::component_ref owner, core::component::component* component) -> bool
                {
                    return component && component->get_entity() == owner;
                };

            REQUIRE(check_owner(root_ref, storage.find<simple_component>(ref1)));
            REQUIRE(check_owner(root_ref, storage.find<component_a>(ref2)));
            REQUIRE(check_owner(root_ref, storage.find<component_b>(ref3)));

            REQUIRE(check_owner(root_ref, storage.find<update_component_a>(ref4)));
            REQUIRE(check_owner(root_ref, storage.find<update_component_b>(ref5)));

            for (size_t it = 0u; it < 10u; ++it) {
                storage.add<simple_component>();
            }

            REQUIRE(std::ranges::any_of(storage.get_all<simple_component>(), [](const auto& it) { return it.get_entity(); }));

            storage.remove(root_ref);

            REQUIRE(std::ranges::none_of(storage.get_all<simple_component>(), [](const auto& it) { return it.get_entity(); }));
        }
    }
}

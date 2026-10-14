#pragma once

#include <core/math/types/transform.hpp>
#include <core/component/component.hpp>
#include <core/component/storage.hpp>
#include <core/context/context.hpp>

namespace liqelligence::core::component
{
    class entity final : public component
    {
    public:
        entity() = default;
        entity(entity&&) = default;
        entity& operator=(entity&&) = default;

        ~entity() noexcept
        {
            if (!context::available()) {
                return;
            }

            auto& storage = get_storage();
            auto asdf = _components | std::views::values | std::ranges::to<std::vector>();
            for (const auto ref : asdf) {
                storage.remove(ref);
            }
        }

        template<component_type t_component>
        bool has() const
        {
            if (const auto it = _components.find(typeid(t_component)); it != _components.end()) {
                const auto& storage = get_storage();
                return storage.has(it->second);
            }

            return false;
        }

        template<component_type t_component, typename... t_args>
            requires std::constructible_from<t_component, t_args...>
        t_component& get_or_add(t_args&&... args)
        {
            if (auto* component = find<t_component>()) {
                return *component;
            }

            _components.erase(typeid(t_component));

            const auto self_ref = get_ref();
            auto& storage = get_storage();
            auto& component = storage.add<t_component>(std::forward<t_args>(args)...);
            component.set_entity(self_ref);

            if constexpr (std::is_same_v<entity, t_component>) {
                if (auto* self = storage.find<entity>(self_ref)) {
                    self->_components.emplace(typeid(entity), component.get_ref());
                }
            }
            else {
                _components.emplace(typeid(t_component), component.get_ref());
            }

            return component;
        }

        template<component_type t_component>
        t_component* find()
        {
            if (const auto it = _components.find(typeid(t_component)); it != _components.end()) {
                const auto& storage = get_storage();
                return storage.find<t_component>(it->second);
            }

            return {};
        }

        template<component_type t_component>
        void remove()
        {
            if (const auto it = _components.find(typeid(t_component)); it != _components.end()) {
                auto& storage = get_storage();
                storage.remove(it->second);
            }
        }

        void destroy()
        {
            auto& storage = get_storage();
            storage.schedule_remove(get_ref());
        }

        transform& get_transform() { return _transform; }
        const transform& get_transform() const { return _transform; }

    private:
        static storage& get_storage()
        {
            return context::get<storage>();
        }

    private:
        transform_value _transform;

        std::unordered_map<std::type_index, component_ref> _components;

    };
}

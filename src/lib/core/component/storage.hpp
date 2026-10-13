#pragma once

#include <core/component/interface_adapter.hpp>
#include <core/component/component.hpp>
#include <core/component/bucket.hpp>
#include <core/context/item.hpp>

namespace liqelligence::core::component
{
    class storage : public context_item
    {
    public:
        template<component_type t_component, typename ...t_args>
            requires std::constructible_from<t_component, t_args...>
        t_component& add(t_args&&... args)
        {
            auto& bucket = get_bucket_for<t_component>();
            return bucket.add(std::forward<t_args>(args)...);
        }

        template<component_type t_component>
        t_component* find(component_ref ref) const
        {
            if (!ref) {
                return {};
            }

            if (auto* bucket = find_bucket_for<t_component>()) {
                return bucket->find(ref);
            }

            return {};
        }

        void remove(component_ref ref)
        {
            if (!ref) {
                return;
            }

            if (auto* bucket = find_generic_bucket_for(ref.get_type())) {
                bucket->remove(ref);
            }
        }

        template<component_type t_component>
        void remove(const t_component& it)
        {
            if (auto* bucket = find_bucket_for<t_component>()) {
                bucket->remove(it);
            }
        }

        template<component_type t_component>
        range<t_component> get_all() const
        {
            if (auto* bucket = find_bucket_for<t_component>()) {
                return bucket->get_range();
            }

            return {};
        }

        template<interface_adapter_type t_adapter>
        auto get_all() const
        {
            return t_adapter().get_all(*this);
        }

        template<component_type t_component>
        void remove_all()
        {
            const auto type = get_type_of<t_component>();
            _buckets.at(type).reset();
        }

    private:
        template<component_type t_component>
        bucket<t_component>* find_bucket_for() const
        {
            const auto type = get_type_of<t_component>();
            return reinterpret_cast<bucket<t_component>*>(find_generic_bucket_for(type));
        }

        generic_bucket* find_generic_bucket_for(component_type_t type) const
        {
            return _buckets.at(type).get();
        }

        template<component_type t_component>
        bucket<t_component>& get_bucket_for()
        {
            const auto type = get_type_of<t_component>();

            auto& ptr = _buckets.at(type);
            if (!ptr) {
                ptr = std::make_shared<bucket<t_component>>();
            }

            return reinterpret_cast<bucket<t_component>&>(*ptr);
        }

    private:
        std::array<std::shared_ptr<generic_bucket>, detail::type_count_max> _buckets;

    };
}

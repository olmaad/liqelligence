#pragma once

#include <core/component/component.hpp>
#include <core/component/bucket.hpp>
#include <memory>
#include <array>

namespace liqelligence::core::component
{
    class storage
    {
    public:
        static storage& get();
        void reset();

        template<typename t_component, typename ...t_args>
        t_component& add(t_args&&... args)
        {
            auto& bucket = get_bucket_for<t_component>();
            return bucket.add(args...);
        }

        template<typename t_component>
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

        template<typename t_component>
        void remove(const t_component& it)
        {
            if (auto* bucket = find_bucket_for<t_component>()) {
                bucket->remove(it);
            }
        }

        template<typename t_component>
        range<t_component> get_all() const
        {
            if (auto* bucket = find_bucket_for<t_component>()) {
                return bucket->get_range();
            }

            return {};
        }

        template<typename t_component>
        void remove_all()
        {
            const auto type = component_type<t_component>();
            _buckets.at(type).reset();
        }

    private:
        template<typename t_component>
        bucket<t_component>* find_bucket_for() const
        {
            const auto type = component_type<t_component>();
            return reinterpret_cast<bucket<t_component>*>(find_generic_bucket_for(type));
        }

        generic_bucket* find_generic_bucket_for(component_type_t type) const
        {
            return _buckets.at(type).get();
        }

        template<typename t_component>
        bucket<t_component>& get_bucket_for()
        {
            const auto type = component_type<t_component>();

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

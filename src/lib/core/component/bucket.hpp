#pragma once

#include <core/component/component_ref.hpp>
#include <core/component/container.hpp>
#include <vector>
#include <algorithm>
#include <iterator>

namespace liqelligence::core::component
{
    class generic_bucket
    {
    public:
        virtual void remove(component_ref ref) = 0;
    };

    template<typename t_component>
    class bucket : public generic_bucket
    {
    public:
        template<typename ...t_args>
        t_component& add(t_args&&... args)
        {
            const auto index = _components.size();
            auto& added = _components.emplace_back(args...);

            auto& added_ref = added._ref;
            added_ref.set_type(get_type_of<t_component>());
            added_ref.set_bucket_index(index);

            const auto id = _id_count++;
            added_ref.set_id(id);

            _components_index.resize(_id_count);
            _components_index.at(id) = index;

            return added;
        }

        t_component* find(component_ref ref)
        {
            if (!ref || ref.get_type() != component_type<t_component>() || ref.get_id() >= _components_index.size()) {
                return {};
            }

            const auto index = _components_index.at(ref.get_id());
            if (index >= _components.size()) {
                return {};
            }

            return &_components.at(index);
        }

        void remove(const t_component& it)
        {
            remove(it.get_ref());
        }

        void remove(component_ref ref) override
        {
            if (auto* ptr = find(ref)) {
                do_remove(*ptr);
            }
        }

        range<t_component> get_range() { return range<t_component>(_components); }

    private:
        void do_remove(t_component& it)
        {
            const auto& it_ref = it._ref;
            _components_index[it_ref.get_id()] = std::numeric_limits<size_t>::max();

            const auto index = it_ref.get_bucket_index();
            if (index < _components.size() - 1u) {
                auto& swap = _components.back();
                auto& swap_ref = swap._ref;

                swap_ref.set_bucket_index(index);
                _components_index[swap_ref.get_id()] = index;

                std::swap(it, swap);
            }

            _components.pop_back();

            if (_components.empty()) {
                _components_index.clear();
            }
        }

    private:
        component_id_t _id_count = 1u;
        container_type<t_component> _components;
        std::vector<component_id_t> _components_index;

    };
}

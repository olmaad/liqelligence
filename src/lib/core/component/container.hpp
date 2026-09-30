#pragma once

#include <vector>
#include <ranges>

namespace liqelligence::core::component
{
    template<typename t_component>
    using container_type = std::vector<t_component>;

    template<typename t_component>
    class range : public std::ranges::view_interface<range<t_component>>
    {
    public:
        range() {}
        range(container_type<t_component>& container)
            : _container(&container)
        {
        }

        container_type<t_component>::iterator begin()
        {
            if (_container) { return _container->begin(); }
            return {};
        }

        container_type<t_component>::iterator end()
        {
            if (_container) { return _container->end(); }
            return {};
        }

        container_type<t_component>::const_iterator begin() const
        {
            if (_container) { return _container->cbegin(); }
            return {};
        }

        container_type<t_component>::const_iterator end() const
        {
            if (_container) { return _container->cend(); }
            return {};
        }

    private:
        container_type<t_component>* _container = {};
    };
}

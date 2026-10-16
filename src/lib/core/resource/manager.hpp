#pragma once

#include <core/context/item.hpp>

namespace liqelligence::core::resource
{
    class resource_loader;
    class data_loader;

    class manager : public context_item
    {
    public:
        enum class load_mode {
            all = 0
        };

    public:
        manager();

        void load(load_mode mode);
        void unload();

        template<std::derived_from<resource_loader> t_loader>
        const t_loader* find_resource(const std::string& name)
        {
            return dynamic_cast<const t_loader*>(find_resource(name));
        }

        const resource_loader* find_resource(const std::string& name);

    private:
        void list();

    private:
        std::shared_ptr<data_loader> _loader;
        std::unordered_map<std::string, std::shared_ptr<resource_loader>> _resources_by_name;
    };
}

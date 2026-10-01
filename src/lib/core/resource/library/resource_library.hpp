#pragma once

#include <unordered_map>
#include <memory>
#include <string>

namespace liqelligence::core::resource
{
    class base_library
    {
    public:
        virtual ~base_library() noexcept = default;
    };

    template<typename t_resource>
    class resource_library : public base_library
    {
    public:
        ~resource_library() noexcept override = default;

        bool has(const std::string& name) const
        {
            return _library.contains(name);
        }

        void add(const std::string& name, std::shared_ptr<t_resource> resource)
        {
            _library.emplace(name, resource);
        }

        void remove(const std::string& name)
        {
            _library.erase(name);
        }

        std::shared_ptr<t_resource> find(const std::string& name) const
        {
            if (const auto it = _library.find(name); it != _library.end()) {
                return it->second;
            }

            return {};
        }

    protected:
        std::unordered_map<std::string, std::shared_ptr<t_resource>> _library;
    };
}

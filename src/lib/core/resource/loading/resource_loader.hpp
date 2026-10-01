#pragma once

#include <filesystem>

namespace liqelligence::core::resource
{
    class data_loader;

    class resource_loader
    {
    public:
        resource_loader(std::shared_ptr<data_loader> loader, std::filesystem::path path);
        virtual ~resource_loader() noexcept = default;

        virtual bool valid() const = 0;
        virtual bool loaded() const = 0;

        virtual void load() = 0;
        virtual void unload() = 0;

        std::string get_name() const;
        std::filesystem::path get_path() const;

    protected:
        std::shared_ptr<data_loader> _loader;
        std::filesystem::path _path;
    };
}

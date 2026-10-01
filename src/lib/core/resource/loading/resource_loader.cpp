#include "resource_loader.hpp"

#include <core/resource/helpers.hpp>

namespace liqelligence::core::resource
{
    resource_loader::resource_loader(std::shared_ptr<data_loader> loader, std::filesystem::path path)
        : _loader(loader)
        , _path(path)
    {
    }

    std::string resource_loader::get_name() const
    {
        return helpers::get_name(_path);
    }

    std::filesystem::path resource_loader::get_path() const
    {
        return _path;
    }
}

#include "sprite_resource_loader.hpp"

#include <core/resource/types/sprite.hpp>
#include <core/resource/loading/data_loader.hpp>
#include <core/resource/library/sprite_library.hpp>

namespace liqelligence::core::resource
{
    bool sprite_resource_loader::valid() const
    {
        return std::filesystem::exists(_path);
    }

    bool sprite_resource_loader::loaded() const
    {
        return library::get<sprite_library>().has(get_name());
    }

    void sprite_resource_loader::load()
    {
        if (!_loader || !valid()) {
            return;
        }

        auto data = _loader->read_data(_path);

        auto resource = std::make_shared<sprite>(std::move(data));
        if (!resource->valid()) {
            return;
        }

        library::get<sprite_library>().add(get_name(), std::move(resource));
    }

    void sprite_resource_loader::unload()
    {
        library::get<sprite_library>().remove(get_name());
    }
}

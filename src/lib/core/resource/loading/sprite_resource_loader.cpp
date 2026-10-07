#include "sprite_resource_loader.hpp"

#include <core/resource/types/sprite.hpp>
#include <core/resource/loading/data_loader.hpp>
#include <core/resource/library/sprite_library.hpp>
#include <core/math/types.hpp>
#include <lodepng.h>

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

        lodepng::State state;
        state.decoder.ignore_crc = true;

        uvector2d size{ 0u, 0u };
        std::vector<uint8_t> decoded;

        const auto result = lodepng::decode(decoded, size.x, size.y, state, data);
        if (result) {
            //auto error = lodepng_error_text(result);
            return;
        }

        auto resource = std::make_shared<sprite>(size, std::move(decoded));
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

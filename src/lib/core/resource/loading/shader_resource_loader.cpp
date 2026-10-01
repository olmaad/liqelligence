#include "shader_resource_loader.hpp"

#include <core/glwrappers/shader.hpp>
#include <core/resource/loading/data_loader.hpp>
#include <core/resource/library/shader_library.hpp>

namespace liqelligence::core::resource
{
    bool shader_resource_loader::valid() const
    {
        const auto paths = break_path();
        return std::filesystem::exists(paths.fragment) && std::filesystem::exists(paths.vertex);
    }

    bool shader_resource_loader::loaded() const
    {
        return library::get<shader_library>().has(get_name());
    }

    void shader_resource_loader::load()
    {
        if (!_loader || !valid()) {
            return;
        }

        const auto paths = break_path();
        auto fragment_data = _loader->read_data(paths.fragment);
        auto vertex_data = _loader->read_data(paths.vertex);

        auto resource = std::make_shared<gl::shader>(std::move(fragment_data), std::move(vertex_data));
        if (!resource->valid()) {
            return;
        }

        library::get<shader_library>().add(get_name(), std::move(resource));
    }

    void shader_resource_loader::unload()
    {
        library::get<shader_library>().remove(get_name());
    }

    shader_resource_loader::paths shader_resource_loader::break_path() const
    {
        auto result = paths{ _path, _path };
        result.fragment.replace_extension("frag");
        result.vertex.replace_extension("vert");

        return result;
    }
}

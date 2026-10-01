#include "manager.hpp"

#include <core/resource/loading/file_data_loader.hpp>
#include <core/resource/loading/shader_resource_loader.hpp>
#include <core/resource/loading/sprite_resource_loader.hpp>
#include <core/resource/helpers.hpp>
#include <filesystem>
#include <functional>

namespace liqelligence::core::resource
{
    manager::manager()
        : _loader(std::make_shared<file_data_loader>())
    {
        list();
    }

    void manager::load(load_mode mode)
    {
        switch (mode) {
        case load_mode::all: {
            for (const auto& [_, it] : _resources_by_name) {
                if (!it->loaded()) {
                    it->load();
                }
            }

            break;
        }
        default: {
            break;
        }
        }
    }

    void manager::unload()
    {
        for (const auto& [_, it] : _resources_by_name) {
            it->unload();
        }
    }

    void manager::list()
    {
        const std::unordered_map<std::string, std::function<std::shared_ptr<resource_loader>(std::filesystem::path)>> factories{
            { "shader", [this](std::filesystem::path path) -> std::shared_ptr<resource_loader> { return std::make_shared<shader_resource_loader>(_loader, path); } },
            { "sprite", [this](std::filesystem::path path) -> std::shared_ptr<resource_loader> { return std::make_shared<sprite_resource_loader>(_loader, path); } }
        };

        std::filesystem::path resources_dir("res");
        for (const auto& dir : std::filesystem::directory_iterator(resources_dir)) {
            if (!dir.is_directory()) {
                continue;
            }

            const auto& factory_it = factories.find(dir.path().filename().stem().string());
            if (factory_it == factories.end()) {
                continue;
            }

            const auto& factory = factory_it->second;

            for (const auto& file : std::filesystem::recursive_directory_iterator(dir)) {
                if (file.is_directory()) {
                    continue;
                }

                auto name = helpers::get_name(file);
                if (_resources_by_name.contains(name)) {
                    continue;
                }

                auto resource = factory(file);
                if (!resource || !resource->valid()) {
                    continue;
                }

                _resources_by_name.emplace(std::move(name), std::move(resource));
            }
        }
    }
}

#pragma once

#include <core/resource/loading/resource_loader.hpp>

namespace liqelligence::core::resource
{
    class shader_resource_loader : public resource_loader
    {
    public:
        using resource_loader::resource_loader;
        ~shader_resource_loader() noexcept override = default;

        bool valid() const override;
        bool loaded() const override;

        void load() const override;
        void unload() const override;

        std::vector<uint8_t> load_data() const override;

    private:
        struct paths
        {
            std::filesystem::path fragment;
            std::filesystem::path vertex;
        };

    private:
        paths break_path() const;
    };
}

#pragma once

#include <core/resource/loading/resource_loader.hpp>
#include <core/math/types.hpp>

namespace liqelligence::core::resource
{
    class sprite_resource_loader : public resource_loader
    {
    public:
        struct load_result {
            uvector2d size;
            std::vector<uint8_t> data;
        };

    public:
        using resource_loader::resource_loader;
        ~sprite_resource_loader() noexcept override = default;

        bool valid() const override;
        bool loaded() const override;

        void load() const override;
        void unload() const override;

        std::vector<uint8_t> load_data() const override;
        load_result load_data_impl() const;

    };
}

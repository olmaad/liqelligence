#pragma once

#include <core/resource/loading/data_loader.hpp>

namespace liqelligence::core::resource
{
    class file_data_loader : public data_loader
    {
    public:
        ~file_data_loader() noexcept override = default;

        std::vector<uint8_t> read_data(std::filesystem::path path) const override;
    };
}

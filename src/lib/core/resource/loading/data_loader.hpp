#pragma once

#include <filesystem>
#include <vector>

namespace liqelligence::core::resource
{
    class data_loader
    {
    public:
        virtual ~data_loader() noexcept = default;

        virtual std::vector<uint8_t> read_data(std::filesystem::path path) const = 0;
    };
}

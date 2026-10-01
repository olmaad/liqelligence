#include "file_data_loader.hpp"

#include <fstream>

namespace liqelligence::core::resource
{
    std::vector<uint8_t> file_data_loader::read_data(std::filesystem::path path) const
    {
        std::basic_ifstream<uint8_t> file(path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            return {};
        }

        auto begin = std::istreambuf_iterator<uint8_t>(file);
        auto end = std::istreambuf_iterator<uint8_t>();
        std::vector<uint8_t> result(begin, end);

        return result;
    }
}

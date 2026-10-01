#pragma once

#include <filesystem>
#include <string>

namespace liqelligence::core::resource::helpers
{
    std::string get_name(std::filesystem::path path);
}

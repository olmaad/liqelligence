#include "helpers.hpp"

namespace liqelligence::core::resource::helpers
{
    std::string get_name(std::filesystem::path path)
    {
        return path.stem().string();
    }
}

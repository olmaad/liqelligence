#include "library.hpp"

namespace liqelligence::core::resource
{
    library& library::instance()
    {
        static library instance;
        return instance;
    }

    void library::reset()
    {
        _libraries.clear();
    }
}

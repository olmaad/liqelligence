#include "storage.hpp"

namespace liqelligence::core::component
{
    storage& storage::get()
    {
        static storage instance;
        return instance;
    }

    void storage::reset()
    {
        _buckets = {};
    }
}

#include "layer.hpp"

namespace liqelligence::core::draw
{
    std::generator<const action&> layer::flush() const
    {
        for (const auto& [_, batch] : _batches) {
            for (const auto& it : batch->flush()) {
                co_yield it;
            }
        }
    }
}

#include "action.hpp"

namespace liqelligence::core::draw
{
    lambda_action::lambda_action(std::function<void(settings)> function)
        : _function(std::move(function))
    {
    }

    void lambda_action::apply(settings settings) const
    {
        if (_function) {
            _function(settings);
        }
    }
}

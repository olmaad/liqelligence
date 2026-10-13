#include "context.hpp"

namespace liqelligence::core
{
    std::unique_ptr<context::instance_type> context::_instance{};

    context::instance_type& context::instance()
    {
        if (!_instance) {
            recreate();
        }

        return *_instance;
    }

    void context::recreate()
    {
        _instance.reset();
        _instance = std::make_unique<instance_type>();
    }
}

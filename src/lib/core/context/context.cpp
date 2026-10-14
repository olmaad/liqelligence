#include "context.hpp"

namespace liqelligence::core
{
    bool context::_available = false;
    std::unique_ptr<context> context::_instance;

    context::context()
    {
        _available = true;
    }

    context::~context() noexcept
    {
        _available = false;
    }

    bool context::available()
    {
        return _available;
    }

    void context::update()
    {
        if (auto* ptr = instance_ptr()) {
            ptr->update_items();
        }
    }

    void context::recreate()
    {
        _instance.reset();
    }

    context& context::instance()
    {
        if (!_instance) {
            _instance = std::make_unique<context>();
        }

        return *_instance;
    }

    context* context::instance_ptr()
    {
        if (_available) {
            return _instance.get();
        }

        return {};
    }

    void context::update_items()
    {
        for (const auto& it : _container | std::views::values) {
            it->update();
        }
    }
}

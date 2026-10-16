#pragma once

#include <core/draw/settings.hpp>

namespace liqelligence::core::draw
{
    class action
    {
    public:
        virtual void apply(settings) const = 0;

    };

    class lambda_action : public action
    {
    public:
        lambda_action(std::function<void(settings)> function);

        void apply(settings settings) const override;

    private:
        std::function<void(settings)> _function;

    };
}

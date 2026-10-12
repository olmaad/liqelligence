#pragma once

#include <functional>

namespace liqelligence::core::draw
{
    class action
    {
    public:
        virtual void apply() const = 0;

    };

    class lambda_action : public action
    {
    public:
        lambda_action(std::function<void()> function);

        void apply() const override;

    private:
        std::function<void()> _function;

    };
}

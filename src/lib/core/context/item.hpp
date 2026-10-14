#pragma once

namespace liqelligence::core
{
    class context_item
    {
    public:
        virtual ~context_item() noexcept = default;

        virtual void update();

    };
}

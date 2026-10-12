#pragma once

#include <core/draw/unit.hpp>

namespace liqelligence::core::draw
{
    class batch
    {
    public:
        virtual std::generator<const action&> flush() const = 0;

    };

    template<typename t_unit>
    class batch_of : public batch
    {
    public:
        void draw(t_unit&& unit)
        {
            _units.emplace_back(std::forward<t_unit>(unit));
        }

        std::generator<const action&> flush() const override
        {
            for (const auto& it : core::draw::flush(_units)) {
                co_yield it;
            }
        }

    private:
        std::vector<t_unit> _units;

    };
}

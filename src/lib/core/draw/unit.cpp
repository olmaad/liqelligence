#include "unit.hpp"

namespace liqelligence::core::draw
{
    unit_description unit::get_description() const
    {
        return unit_description(typeid(*this), get_hash());
    }

    void unit::apply(settings) const
    {
    }
}

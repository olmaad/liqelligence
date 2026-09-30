#include "component.hpp"

namespace liqelligence::core::component
{
    void component::update(float /*dt*/)
    {
    }

    void component::draw()
    {
    }

    component_ref component::get_ref() const
    {
        return _ref;
    }
}

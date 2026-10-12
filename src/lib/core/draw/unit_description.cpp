#include "unit_description.hpp"

namespace liqelligence::core::draw
{
    unit_description::unit_description(std::type_index type, size_t hash)
        : _type(type)
        , _hash(hash)
    {
    }

    bool unit_description::operator==(const unit_description& other) const
    {
        return _type == other._type && _hash == other._hash;
    }
}

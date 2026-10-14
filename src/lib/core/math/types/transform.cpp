#include "transform.hpp"

namespace liqelligence
{
    transform_value::transform_value(fvector2d pos, fvector2d scale, float rotation)
        : _pos(pos)
        , _scale(scale)
        , _rotation(rotation)
    {
    }

    vector2d transform_value::get_pos() const
    {
        return _pos;
    }

    void transform_value::set_pos(vector2d value)
    {
        _pos = value;
    }

    fvector2d transform_value::get_scale() const
    {
        return _scale;
    }

    void transform_value::set_scale(fvector2d value)
    {
        _scale = value;
    }

    float transform_value::get_rotation() const
    {
        return _rotation;
    }

    void transform_value::set_rotation(float value)
    {
        _rotation = value;
    }
}

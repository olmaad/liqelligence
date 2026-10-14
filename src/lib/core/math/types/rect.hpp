#pragma once

#include <core/math/types/vector.hpp>

namespace liqelligence
{
    template<typename t_value, typename t_vector>
        requires std::integral<t_value> || std::floating_point<t_value> && std::constructible_from<t_vector, t_value, t_value>&& requires(t_vector vector) { vector.x; vector.y; }
    class rect
    {
    public:
        rect() = default;
        rect(t_value i_x, t_value i_y, t_value i_width, t_value i_height)
            : x(i_x)
            , y(i_y)
            , width(i_width)
            , height(i_height)
        {
        }

        rect(t_vector start, t_vector size)
            : x(start.x)
            , y(start.y)
            , width(size.x)
            , height(size.y)
        {
        }

        t_vector get_size() const
        {
            return t_vector(width, height);
        }

        void set_size(t_vector value)
        {
            width = value.x;
            height = value.y;
        }

        t_vector get_pos() const
        {
            return t_vector(x, y);
        }

        void set_pos(t_vector value)
        {
            x = value.x;
            y = value.y;
        }

    public:
        t_value x{};
        t_value y{};
        t_value width{};
        t_value height{};

    };

    using rect2d = rect<int, vector2d>;
    using urect2d = rect<uint32_t, uvector2d>;
    using frect2d = rect<float, fvector2d>;
}

#pragma once

#include <core/math/types/vector.hpp>

namespace liqelligence
{
    class transform
    {
    public:
        virtual vector2d get_pos() const = 0;
        virtual void set_pos(vector2d value) = 0;
        virtual fvector2d get_scale() const = 0;
        virtual void set_scale(fvector2d value) = 0;
        virtual float get_rotation() const = 0;
        virtual void set_rotation(float value) = 0;

    };

    class transform_value : public transform
    {
    public:
        transform_value(vector2d pos = { 0, 0 }, fvector2d scale = { 1.f, 1.f }, float rotation = 0.f);

        vector2d get_pos() const override;
        void set_pos(vector2d value) override;
        fvector2d get_scale() const override;
        void set_scale(fvector2d value) override;
        float get_rotation() const override;
        void set_rotation(float value) override;

    private:
        vector2d _pos;
        fvector2d _scale;
        float _rotation = 0.f;

    };

    template<typename t_transform>
        requires std::is_same_v<t_transform, transform> || std::is_same_v<t_transform, const transform>
    class transform_proxy : public transform
    {
    public:
        transform_proxy() = default;
        transform_proxy(t_transform& origin)
            : _origin(&origin)
        {
        }

        vector2d get_pos() const override { return _origin ? _origin->get_pos() : vector2d{}; }
        void set_pos(vector2d value) override { if constexpr (!std::is_const_v<t_transform>) { if (_origin) { _origin->set_pos(value); } } }
        fvector2d get_scale() const override { return _origin ? _origin->get_scale() : fvector2d{}; }
        void set_scale(fvector2d value) override { if constexpr (!std::is_const_v<t_transform>) { if (_origin) { _origin->set_scale(value); } } }
        float get_rotation() const override { return _origin ? _origin->get_rotation() : 0.f; }
        void set_rotation(float value) override { if constexpr (!std::is_const_v<t_transform>) { if (_origin) { _origin->set_rotation(value); } } }

    private:
        t_transform* _origin = nullptr;

    };
}

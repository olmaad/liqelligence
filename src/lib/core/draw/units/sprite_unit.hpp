#pragma once

#include <core/draw/types.hpp>
#include <core/math/types.hpp>
#include <core/draw/unit.hpp>

namespace liqelligence::core::resource
{
    class sprite;
    class shader;
}

namespace liqelligence::core::draw
{
    class sprite_unit : public unit
    {
    public:
        sprite_unit(fvector2d pos, vector2d size, const resource::sprite& sprite, const resource::shader& shader);

        fvector2d get_pos() const;
        vector2d get_size() const;
        const resource::sprite& get_sprite() const;
        const resource::shader& get_shader() const;

        hash_t get_hash() const override;

    private:
        const fvector2d _pos;
        const vector2d _size;

        const resource::sprite& _sprite;
        const resource::shader& _shader;

    };

    std::generator<const action&> flush(const std::vector<sprite_unit>& units);

}

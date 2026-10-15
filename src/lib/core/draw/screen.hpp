#pragma once

#include <core/context/item.hpp>
#include <core/math/types.hpp>

namespace liqelligence::core::resource
{
    class shader;
}

namespace liqelligence::core::draw
{
    class screen : public context_item
    {
    public:
        vector2d get_size() const;
        void set_size(vector2d value);

        void fill_uniforms(const resource::shader& shader) const;

    private:
        vector2d _size;

    };
}

#pragma once

#include <core/component/interface/draw_component.hpp>
#include <core/component/component.hpp>
#include <core/draw/types.hpp>
#include <core/math/types.hpp>
#include <memory>
#include <string>

namespace liqelligence::core::resource
{
    class sprite;
    class shader;
}

namespace liqelligence::game
{
    class sprite_component : public core::component::component, public core::component::i_draw_component
    {
    public:
        sprite_component(const std::string& sprite, const std::string& shader);

        void draw() const override;

        core::draw::priority_t get_priority() const;
        void set_priority(core::draw::priority_t value);
        vector2d get_size() const;
        void set_size(vector2d value);

    private:
        core::draw::priority_t _priority = 0u;
        vector2d _size;

        std::shared_ptr<core::resource::sprite> _sprite;
        std::shared_ptr<core::resource::shader> _shader;

    };
}

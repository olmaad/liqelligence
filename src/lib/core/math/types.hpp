#pragma once

#include <glm/glm.hpp>
#include <core/math/types/rect.hpp>

namespace liqelligence
{
    using vector2d = glm::vec2;
    using uvector2d = glm::uvec2;
    using fvector2d = glm::fvec2;

    using vector3d = glm::vec3;
    using uvector3d = glm::uvec3;
    using fvector3d = glm::fvec3;

    using rect2d = rect<int, vector2d>;
    using urect2d = rect<uint32_t, uvector2d>;
    using frect2d = rect<float, fvector2d>;
}

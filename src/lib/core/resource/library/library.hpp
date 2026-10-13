#pragma once

#include <core/resource/library/resource_library.hpp>
#include <core/utils/multitype_container.hpp>
#include <core/context/item.hpp>

namespace liqelligence::core::resource
{
    class base_library;

    class library : public context_item, public multitype_container<base_library>
    {
    };
}

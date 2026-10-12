#pragma once

#include <core/draw/unit_description.hpp>
#include <core/draw/action.hpp>
#include <generator>
#include <utility>
#include <vector>
#include <memory>

namespace liqelligence::core::draw
{
    class unit : public action
    {
    public:
        using hash_t = size_t;

    public:
        virtual ~unit() noexcept = default;

        unit_description get_description() const;

        virtual hash_t get_hash() const = 0;

        void apply() const override;

    };

    template<std::derived_from<unit> t_unit>
    std::generator<const action&> flush(const std::vector<t_unit>&)
    {
        return {};
    }

}

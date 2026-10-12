#pragma once

namespace liqelligence::core::draw
{
    class unit_description
    {
    public:
        unit_description(std::type_index type, size_t hash);

        bool operator==(const unit_description& other) const;

    private:
        const std::type_index _type;
        const size_t _hash = 0u;

    };
}

template<>
struct std::hash<liqelligence::core::draw::unit_description>
{
    size_t operator()(const liqelligence::core::draw::unit_description& description) const noexcept
    {
        return 0u;
    }
};

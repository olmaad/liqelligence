#pragma once

#include <core/draw/unit_description.hpp>
#include <core/draw/action.hpp>
#include <core/draw/batch.hpp>

namespace liqelligence::core::draw
{
    class layer
    {
    public:
        template<typename t_unit>
        void draw(t_unit&& unit)
        {
            const auto description = unit.get_description();

            if (auto it = _batches.find(description); it != _batches.end()) {
                auto& batch = static_cast<batch_of<t_unit>&>(*it->second);
                batch.draw(std::forward<t_unit>(unit));
            }
            else {
                auto batch = std::make_unique<batch_of<t_unit>>();
                batch->draw(std::forward<t_unit>(unit));

                _batches.emplace(description, std::move(batch));
            }
        }

        std::generator<const action&> flush() const;

    private:
        std::unordered_map<unit_description, std::unique_ptr<batch>> _batches;

    };
}

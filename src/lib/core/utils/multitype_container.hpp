#pragma once

namespace liqelligence::core
{
    template<typename t_item, typename t_base>
    concept multitype_container_item_type = std::derived_from<t_item, t_base>&& std::constructible_from<t_item>;

    template<typename t_base>
    class multitype_container
    {
    public:
        using base_type = t_base;

    public:
        virtual ~multitype_container() noexcept = default;

        template<multitype_container_item_type<t_base> t_item>
        t_item& get()
        {
            std::type_index id = typeid(t_item);

            auto it = _items.find(id);
            if (it == _items.end()) {
                auto ptr = std::make_unique<t_item>();
                auto& item = *ptr;

                _items.emplace(id, std::move(ptr));

                return item;
            }
            else {
                return static_cast<t_item&>(*it->second);
            }
        }

        template<multitype_container_item_type<t_base> t_item>
        t_item* find()
        {
            if (auto it = _items.find(typeid(t_item)); it != _items.end()) {
                return it->second.get();
            }
        }

    protected:
        std::unordered_map<std::type_index, std::unique_ptr<t_base>> _items;

    };
}

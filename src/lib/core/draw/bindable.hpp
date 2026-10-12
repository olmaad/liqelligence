#pragma once

namespace liqelligence::core::draw
{
    template<typename t_bindable>
    concept bindable_type = requires(t_bindable bindable) {
        bindable.bind();
        bindable.unbind();
    };

    template<bindable_type t_bindable>
    class scoped_bind
    {
    public:
        scoped_bind(t_bindable& bindable)
            : _bindable(bindable)
        {
            _bindable.bind();
        }

        ~scoped_bind()
        {
            _bindable.unbind();
        }

        t_bindable* operator->()
        {
            return &_bindable;
        }

        const t_bindable* operator->() const
        {
            return &_bindable;
        }

    private:
        t_bindable& _bindable;

    };
}

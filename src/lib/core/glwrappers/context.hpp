#pragma once

namespace liqelligence::core::gl
{
    class context
    {
    public:
        context();
        ~context();

        operator bool() const;

        bool valid() const;

    private:
        int _init_result = 0;
    };
}

#include <prototype/prototype.hpp>
#include <core/application/window.hpp>

int main()
{
    using namespace liqelligence;

    core::application::window window(
        prototype::create_delegate(),
        {
            .size = { 1280, 720 },
            .fill_color = { 0.f, 0.f, 0.f, 1.f }
        });

    if (window.valid()) {
        window.show();
        return 0;
    }

    return 1;
}
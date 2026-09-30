#include <core/glwrappers/context.hpp>
#include <core/glwrappers/window.hpp>

int main() {
    using namespace liqelligence;

    core::gl::context cnxt;
    if (!cnxt) {
        return 1;
    }

    core::gl::window wnd;
    if (!wnd) {
        return 2;
    }

    do {
        wnd.process();
        wnd.draw();
    } while (!wnd.need_close());

    return 0;
}
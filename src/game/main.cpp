#include <core/resource/manager.hpp>
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

    core::resource::manager resources;
    resources.load(core::resource::manager::load_mode::all);

    do {
        wnd.process();
        wnd.draw();
    } while (!wnd.need_close());

    return 0;
}
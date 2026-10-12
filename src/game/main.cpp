#include <prototype/prototype.hpp>
#include <core/resource/manager.hpp>
#include <core/glwrappers/context.hpp>
#include <core/glwrappers/window.hpp>
#include <chrono>

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

    prototype::setup_scene();

    auto last_update = std::chrono::system_clock::now();

    do {
        const auto dt = (std::exchange(last_update, std::chrono::system_clock::now()) - last_update) * -1;

        prototype::update_scene(std::chrono::duration<float>(dt).count());

        wnd.draw(prototype::draw_scene);
        wnd.process();
    } while (!wnd.need_close());

    return 0;
}
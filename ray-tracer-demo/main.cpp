#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <rt/math/vec3.h>
#include <rt/graphics/image.h>
#include <rt/graphics/renderer.h>
#include <rt/graphics/camera/perspective_camera.h>
#include <rt/objects/sphere.h>
#include <rt/materials/diffuse.h>
#include <rt/objects/plane.h>

void setup_logger();

int main() {
    setup_logger();

    rt::renderer renderer(1280, 0, 10);
    rt::perspective_camera camera(rt::vec3(0, 0, 5), rt::vec3(0, 0, 0), rt::vec3(0, 1, 0), 60, 16.0 / 9.0);
    rt::scene scene;

    scene.add(std::make_shared<rt::sphere>(std::make_shared<rt::diffuse>(rt::color3::ORANGE()), rt::vec3(0, 0, 0), 1));
    scene.add(std::make_shared<rt::plane>(std::make_shared<rt::diffuse>(rt::color3::LAWNGREEN()), rt::vec3(0, -1, 0)));

    rt::image render = renderer.render(scene, camera);

    render.process([](rt::color3 c) { return c.gamma_correction(2.2); });

    render.write("image.png");

    return 0;
}

void setup_logger() {
    spdlog::set_default_logger(spdlog::basic_logger_mt("ray_tracer", "log/ray_tracer.log"));
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    spdlog::flush_on(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5));
    spdlog::info("Logger set up and running. Log level is set to {}.", spdlog::level::to_string_view(spdlog::get_level()));
}

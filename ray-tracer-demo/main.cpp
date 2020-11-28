#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>
#include <rt/math/vec3.h>
#include <rt/math/color3.h>
#include <rt/graphics/image.h>

void setup_logger();

int main() {
    setup_logger();

    rt::vec3 a(1, 2, 3);
    std::cout << -a << std::endl;
    std::cout << rt::color3::LAVENDER().inverted().brighter().brighter() << std::endl;

    rt::image image(5, 6);
    image(2, 2) = rt::color3(51, 153, 204);

    std::cout << image(2, 2) << std::endl;

    image.write("file.png");

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

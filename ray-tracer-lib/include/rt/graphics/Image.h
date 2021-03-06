#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <memory>
#include <rt/math/Color3.h>
#include <vector>
#include <ostream>

namespace rt {
    class Image {
    public:
        Image(int width, int height);
        Image(const Image& img);

        Color3& operator()(int w, int h);

        [[nodiscard]] int get_width() const;
        [[nodiscard]] int get_height() const;

        void process(const std::function<Color3 (Color3)>& function);

        void write(const std::string& path) const;
    private:
        int width, height;
        std::unique_ptr<std::unique_ptr<Color3[]>[]> data;
    };
}


#endif //RAYTRACER_IMAGE_H

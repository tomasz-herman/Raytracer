#include <cmath>
#include "rt/objects/sphere.h"

namespace rt {
    sphere::sphere(std::shared_ptr<material> material_ptr, vec3 position, double radius) : material_ptr(std::move(material_ptr)), position(position), radius(radius) { }
    sphere::sphere(std::shared_ptr<material> material_ptr, double x, double y, double z, double radius) : material_ptr(std::move(material_ptr)), position(vec3(x, y, z)), radius(radius) {}

    bool sphere::hit_test(const ray& ray, hit& hit, double from, double to) const {
        vec3 oc = ray.origin - position;
        double a = ray.direction.length_squared();
        double half_b = oc.dot(ray.direction);
        double c = oc.length_squared() - radius*radius;

        double discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        double sqrtd = sqrt(discriminant);

        double root = (-half_b - sqrtd) / a;
        if (root < from || to < root) {
            root = (-half_b + sqrtd) / a;
            if (root < from || to < root)
                return false;
        }

        hit.distance = root;
        hit.position = ray(hit.distance);
        hit.material_ptr = material_ptr;
        hit.normal = (hit.position - position) / radius;

        return true;
    }
}
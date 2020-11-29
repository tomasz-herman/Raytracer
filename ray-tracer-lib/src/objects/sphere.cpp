#include <cmath>
#include "rt/objects/sphere.h"

namespace rt {
    sphere::sphere(vec3 position, double radius) : position(position), radius(radius) { }
    sphere::sphere(double x, double y, double z, double radius) : position(vec3(x, y, z)), radius(radius) {}

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
        hit.normal = (hit.position - position) / radius;

        return true;
    }
}
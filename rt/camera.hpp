#ifndef CAMERAH
#define CAMERAH

#include <random>
#include <cmath>

#include "Ray.hpp"

double random_number()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

Vector3 random_in_unit_disk() {
    Vector3 p;
    do {
        p = 2.0 * Vector3(random_number(), random_number(), 0.0) - Vector3(1,1,0);
    } while (dot(p,p) >= 1.0);
    return p;
}

constexpr double const pi = 3.14159265359;

class Camera {
    public:
        Camera(Vector3 const& lookfrom, Vector3 const& lookat, Vector3 const& vup, float vfov, float aspect) {
            float theta = vfov * pi/180;
            float half_height = std::tan(theta/2);
            float half_width = aspect * half_height;
            origin = lookfrom;
            Vector3 w = unit_vector(lookfrom - lookat);
            Vector3 u = unit_vector(cross(vup, w));
            Vector3 v = cross(w, u);
            lower_left_corner = origin  - half_width*u -half_height*v - w;
            horizontal = 2*half_width*u;
            vertical = 2*half_height*v;
        }
        Ray get_ray(float s, float t) {
            return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        }

        Vector3 origin;
        Vector3 lower_left_corner;
        Vector3 horizontal;
        Vector3 vertical;

};
#endif

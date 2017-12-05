#ifndef SPHEREH
#define SPHEREH

#include "hitable.hpp"

class Sphere: public Hitable  {
    public:
        Sphere() {}
        Sphere(Vector3 cen, float r) : center(cen), radius(r) {};
        virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const;
        Vector3 center;
        float radius;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    // TODO: Fill out function
    return false;
}

#endif

#ifndef HITABLEH
#define HITABLEH

#include "Ray.hpp"

struct HitRecord
{
    float t;
    Vector3 p;
    Vector3 normal;
    Vector3 const* color;
};

class Hitable  {
    public:
        virtual bool hit(Ray const& r, float t_min, float t_max, HitRecord & rec) const = 0;
        Vector3 color = Vector3(0.5f, 0.5f, 0.5f);
};

#endif





#ifndef HITABLEH
#define HITABLEH

#include "Ray.hpp"

struct HitRecord
{
    float t;
    Vector3 p;
    Vector3 normal;
};

class Hitable  {
    public:
        virtual bool hit(Ray const& r, float t_min, float t_max, HitRecord & rec) const = 0;
};

#endif





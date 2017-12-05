#ifndef RAYH
#define RAYH

#include "vector3.hpp"

class Ray
{
    public:
        Ray() {}
        Ray(Vector3 const& a, Vector3 const& b) : orig(a), dir(b) {}
        Vector3 const& origin() const       { return orig; }
        Vector3 const& direction() const    { return dir; }
        Vector3 point_at_parameter(float t) const { return orig + t*dir; }
    private:
        Vector3 orig;
        Vector3 dir;
};

#endif



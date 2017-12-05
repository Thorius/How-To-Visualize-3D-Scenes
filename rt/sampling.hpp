#ifndef SAMPLINGH
#define SAMPLINGH

#include <random>

#include "vector3.hpp"

inline double random_number()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

inline Vector3 random_in_unit_sphere() {
    Vector3 p;
    do {
        p = 2.0f * Vector3(random_number(), random_number(), random_number()) - Vector3(1,1,1);
    } while (dot(p,p) >= 1.0f);
    return p;
}

#endif

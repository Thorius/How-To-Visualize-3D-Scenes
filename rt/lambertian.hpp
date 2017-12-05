#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "material.hpp"
#include "vector3.hpp"
#include "ray.hpp"

class Lambertian : public Material {
public:
    Lambertian(Vector3 const& attenuation) : albedo(attenuation) {}
    bool scatter(Ray const& ray, HitRecord const& record, Vector3 & attenuation, Ray & scattered) const override;

private:
    Vector3 albedo;
};

bool Lambertian::scatter(Ray const& ray, HitRecord const& record, Vector3 & attenuation, Ray & scattered) const
{
    // TODO: Refactor shading from the scene_color function here.
    return false;
}

#endif

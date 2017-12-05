#ifndef COMPOSITEH
#define COMPOSITEH

#include "hitable.hpp"

#include <vector>

class Composite : public Hitable  {
    public:
        Composite() {}
        virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const;
        void add_hitable(Hitable & h) {
            hitables.push_back(&h);
        }
        std::vector<Hitable *> hitables;
};

bool Composite::hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = tmax;
    for (auto & curr : hitables) {
        if (curr->hit(r, tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif

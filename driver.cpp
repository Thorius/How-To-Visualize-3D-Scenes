#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

#include "rt/vector3.hpp"
#include "rt/camera.hpp"
#include "rt/hitable.hpp"
#include "rt/sphere.hpp"
#include "rt/composite.hpp"
#include "rt/sampling.hpp"

using Film = std::vector<std::vector<Vector3>>;

void resize_film(Film & film, unsigned const width, unsigned height)
{
    film.resize(height);
    for (auto & row : film) {
        row.resize(width);
    }
}

void output_ppm_image(std::string const& filename, Film const& image)
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Unable to open file\n";
        return;
    }
    out << "P3\n" << image.front().size() << ' ' << image.size() << "\n255\n";
    for (auto curr = image.rbegin(); curr != image.rend(); ++ curr) {
        for (auto & pixel : *curr) {
            out << static_cast<int>(pixel.r()) << ' '
                << static_cast<int>(pixel.g()) << ' '
                << static_cast<int>(pixel.b()) << '\n';
        }
    }
}

// Color function
Vector3 scene_color(Ray const& r, Hitable & world)
{
    HitRecord record;
    if (world.hit(r, 0.0f, std::numeric_limits<float>::max(), record)) {
        // TODO: Add a recursive call to the function, by tracing a reflected ray
        //       whose direction is randomly perturbed in a unit sphere. Use the random_in_unit_sphere().
        return 0.5f * (*record.color);
    } else {
        // Sky color
        Vector3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * Vector3(1, 1, 1) + t * Vector3(0.45, 0.65, 1.0);
    }
}

int main()
{
    // Image parameters
    unsigned const nx = 600;
    unsigned const ny = 300;
    Film output;
    resize_film(output, nx, ny);
    // Camera parameters
    Vector3 origin(0, 0, 0);
    Vector3 lookat(0, 0, -4);
    Vector3 up(0, 1, 0);
    Camera cam(origin, lookat, up, 90, float(nx) / float(ny));
    // Actual scene
    Composite world;
    Sphere sphere_small(Vector3(0, 0, -2), 0.5);
    sphere_small.color = Vector3(0.4, 0.4, 0.4);
    Sphere sphere_large(Vector3(0, -100.5, 1), 100);
    sphere_large.color = Vector3(0.1, 0.8, 0.2);
    world.add_hitable(sphere_small);
    world.add_hitable(sphere_large);
    // Render loop
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            auto u = static_cast<float>(i) / static_cast<float>(nx);
            auto v = static_cast<float>(j) / static_cast<float>(ny);
            auto col = scene_color(cam.get_ray(u, v), world);
            output[j][i] = 255.99f * col;
        }
    }
    output_ppm_image("sphere_hit.ppm", output);
    return 0;
}

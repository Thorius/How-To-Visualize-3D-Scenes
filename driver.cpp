#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

#include "rt/vector3.hpp"
#include "rt/camera.hpp"
#include "rt/hitable.hpp"
#include "rt/sphere.hpp"
#include "rt/composite.hpp"
#include "rt/sampling.hpp"
#include "rt/material.hpp"
#include "rt/lambertian.hpp"
#include "rt/metal.hpp"

using Film = std::vector<std::vector<Vector3>>;
using Color = Vector3;

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

constexpr int const max_depth = 30;

// Color function
Vector3 scene_color(Ray const& r, Hitable & world, int depth)
{
    HitRecord record;
    if (world.hit(r, 0.001f, std::numeric_limits<float>::max(), record)) {
        Ray scattered;
        Vector3 attenuation;
        Vector3 target = record.p + record.normal + random_in_unit_sphere();
        if (depth < max_depth && record.material->scatter(r, record, attenuation, scattered)) {
            return attenuation*scene_color(scattered, world, depth + 1);
        } else {
            return Vector3(0, 0, 0);
        }
    } else {
        // Sky color
        Vector3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * Vector3(1, 1, 1) + t * Vector3(0.45, 0.65, 1.0);
    }
}

// Gamma correction - a lot of image viewers assume that the output is gamma corrected.
// For our purposes, just applying sqrt to each of the values is sufficient.
Vector3 gamma_correction(Vector3 const& color)
{
    return Vector3(std::sqrt(color.r()), std::sqrt(color.g()), std::sqrt(color.b()));
}

int main()
{
    // Image parameters
    int const nx = 900;
    int const ny = 500;
    int const ns = 50;
    Film output;
    resize_film(output, nx, ny);
    // Camera parameters
    Vector3 origin(0, 0.5, 1);
    Vector3 lookat(0, 0, -4);
    Vector3 up(0, 1, 0);
    Camera cam(origin, lookat, up, 100, float(nx) / float(ny));
    // Actual scene
    Composite world;
    Lambertian sphere_mat_1(Vector3(0.8f, 0.2f, 0.2f));
    Sphere sphere_small_1(Vector3(0.0f, 0.0f, -1.0f), 0.5f, sphere_mat_1);
    Metal sphere_mat_2(Vector3(0.7f, 0.8f, 0.2f));
    Sphere sphere_small_2(Vector3(-1.1f, 0.0f, -1.0f), 0.5f, sphere_mat_2);
    Metal sphere_mat_3(Vector3(0.7f, 0.7f, 0.9f));
    Sphere sphere_small_3(Vector3(1.1f, 0.0f, -1.0f), 0.5f, sphere_mat_3);
    Lambertian sphere_mat_4(Vector3(0.9f, 0.1f, 0.2f));
    Sphere sphere_small_4(Vector3(3.1f, 2.0f, 4.0f), 0.5f, sphere_mat_4);
    Lambertian sphere_large_mat_1(Vector3(0.8f, 0.9f, 0.1f));
    Sphere sphere_large_1(Vector3(0.0f, -50.5f, 1.0f), 50.0f, sphere_large_mat_1);
    Metal sphere_large_mat_2(Vector3(0.3f, 0.3f, 0.9f));
    Sphere sphere_large_2(Vector3(5.0f, 26.5f, -7.0f), 25.0f, sphere_large_mat_2);
    world.add_hitable(sphere_small_1);
    world.add_hitable(sphere_small_2);
    world.add_hitable(sphere_small_3);
    world.add_hitable(sphere_small_4);
    world.add_hitable(sphere_large_1);
    world.add_hitable(sphere_large_2);
    // Progress monitoring variables
    std::cout << "Progress:\n|" << std::string(30, '=') << "|\n|";
    auto tenth_row = ny / 30;
    // Render loop
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            Vector3 accum(0, 0, 0);
            for (int s = 0; s != ns; ++s) {
                auto u = static_cast<float>(i + random_number()) / static_cast<float>(nx);
                auto v = static_cast<float>(j + random_number()) / static_cast<float>(ny);
                accum += scene_color(cam.get_ray(u, v), world, 0);
            }
            accum /= static_cast<float>(ns);
            output[j][i] = 255.99f * gamma_correction(accum);
        }
        if (j % tenth_row == 0) {
            std::cout << '=';
        }
    }
    std::cout << "|\n";
    output_ppm_image("simple_scene.ppm", output);
    return 0;
}

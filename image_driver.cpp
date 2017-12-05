#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "rt/vector3.hpp"

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
    }
    out << "P3\n" << image.front().size() << ' ' << image.size() << "\n255\n";
    for (auto & curr = image.rbegin(); curr != image.rend(); ++ curr) {
        for (auto & pixel : *curr) {
            out << static_cast<int>(pixel.r()) << ' '
                << static_cast<int>(pixel.g()) << ' '
                << static_cast<int>(pixel.b()) << '\n';
        }
    }
}

int main()
{
    unsigned const nx = 200;
    unsigned const ny = 100;
    Film output;
    resize_film(output, nx, ny);
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            auto r = static_cast<float>(i) / static_cast<float>(nx);
            auto g = static_cast<float>(j) / static_cast<float>(ny);
            auto b = 0.2f;
            output[j][i] = Vector3(255.99f*r, 255.99f*g, 255.99f*b);
        }
    }
    output_ppm_image("hello.ppm", output);
    return 0;
}

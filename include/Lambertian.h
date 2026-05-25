#pragma once

#include <Material.h>
namespace Nyra
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const raymath::color& albedo);
        ~Lambertian();

        std::pair<raymath::color, std::optional<Nyra::Ray>> Scatter(const Nyra::Ray& ray, const Nyra::HitRecord& hitRecord) const override;
    };
}
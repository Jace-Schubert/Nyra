#pragma once

#include <Material.h>

namespace Nyra
{
    class Lambertian : public Material
    {
    public:
        Lambertian(glm::vec3 albedo);
        ~Lambertian();

        std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const override;
    };
}
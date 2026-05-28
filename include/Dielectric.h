#pragma once

#include <Material.h>

namespace Nyra
{
    class Dielectric : public Material
    {
    public:
        Dielectric(float refractiveIndex);
        ~Dielectric();

        std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const override;

    private:
        float m_refractiveIndex;

        float CalculateReflectance(float cosTheta, float refractiveIndex) const;
    };
}
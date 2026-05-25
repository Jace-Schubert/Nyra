#pragma once

#include <Material.h>

namespace Nyra
{
    class Dielectric : public Material
    {
    public:
        Dielectric(double refractiveIndex);
        ~Dielectric();

        std::pair<raymath::color, std::optional<Nyra::Ray>> Scatter(const Nyra::Ray& ray, const Nyra::HitRecord& hitRecord) const override;

    private:
        double m_refractiveIndex;

        double CalculateReflectance(double cosTheta, double refractiveIndex) const;
    };
}
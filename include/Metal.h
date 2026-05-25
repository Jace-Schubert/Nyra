#pragma once

#include <Material.h>

namespace Nyra
{
    class Metal : public Material
    {
    public:
        Metal(const raymath::color& albedo, double fuzz);
        ~Metal();

        std::pair<raymath::color, std::optional<Nyra::Ray>> Scatter(const Nyra::Ray& ray, const Nyra::HitRecord& hitRecord) const override;

    private:
        double m_fuzz;
    };
}
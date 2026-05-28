#pragma once

#include <Material.h>

namespace Nyra
{
    class Metal : public Material
    {
    public:
        Metal(glm::vec3 albedo, float fuzz);
        ~Metal();

        std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const override;

    private:
        float m_fuzz;
    };
}
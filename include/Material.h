#pragma once

#include <NyraPCH.h>

#include <Ray.h>
#include <Hittable.h>

namespace Nyra
{
    class Material
    {
    public:
        virtual ~Material() = default;

        virtual std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const = 0;

    protected:
        Material(glm::vec3 albedo) : m_albedo(albedo) {}

        glm::vec3 m_albedo;
    };
}
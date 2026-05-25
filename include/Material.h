#pragma once

#include <utility>
#include <vec3.h>
#include <Ray.h>
#include <Hittable.h>

namespace Nyra
{
    class Material
    {
    public:
        virtual ~Material() = default;

        virtual std::pair<raymath::color, std::optional<Nyra::Ray>> Scatter(const Nyra::Ray& ray, const Nyra::HitRecord& hitRecord) const = 0;

    protected:
        Material(const raymath::color& albedo) : m_albedo(albedo) {}

        raymath::color m_albedo;
    };
}
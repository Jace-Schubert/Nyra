#pragma once

#include <Hittable.h>
#include <Material.h>
#include <Texture.h>

namespace Nyra
{
    class ConstantMedium : public Hittable
    {
    public:
        ConstantMedium(std::shared_ptr<Hittable> boundary, float density, std::shared_ptr<Texture> texture);
        ~ConstantMedium();

        // Hittable overrides
        virtual std::optional<HitRecord> Hit(const Ray& ray, Interval interval) const override;
        virtual AABB GetBoundingBox() const override;

    private:
        std::shared_ptr<Hittable> m_boundary;
        std::shared_ptr<Material> m_phaseFunction;
        float m_negativeInverseDensity;
    };
}
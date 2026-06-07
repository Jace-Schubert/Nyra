#pragma once

#include <AABB.h>
#include <Hittable.h>

namespace Nyra
{
    class RotateY : public Hittable
    {
    public:
        RotateY(std::shared_ptr<Hittable> hittable, float angle);
        ~RotateY();

        virtual std::optional<HitRecord> Hit(const Ray& ray, Interval interval) const override;

        virtual AABB GetBoundingBox() const override;

    private:
        AABB m_boundingBox;
        std::shared_ptr<Hittable> m_hittable;
        float m_sinTheta;
        float m_cosTheta;
    };
}
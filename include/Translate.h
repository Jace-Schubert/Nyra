#pragma once

#include <Hittable.h>

namespace Nyra
{
    class Translate : public Hittable
    {
    public:
        Translate(std::shared_ptr<Hittable> hittable, glm::vec3 offset);
        ~Translate();

        virtual std::optional<HitRecord> Hit(const Ray& ray, Interval interval) const override;
        virtual AABB GetBoundingBox() const override;

    private:
        AABB m_boundingBox;
        std::shared_ptr<Hittable> m_hittable;
        glm::vec3 m_offset;
    };
}
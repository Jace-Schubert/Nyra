#pragma once

#include <Hittable.h>
#include <vector>
#include <memory>

namespace Nyra
{
    class HittableList : public Hittable
    {
    public:
        HittableList();
        HittableList(std::shared_ptr<Hittable> hittable);
        ~HittableList();

        // Hittable overrides
        std::optional<HitRecord> Hit(const Nyra::Ray& ray, Interval interval) const override;
        AABB GetBoundingBox() const override;

        void Add(std::shared_ptr<Hittable> hittable);
        void Clear();

        std::vector<std::shared_ptr<Hittable>>& GetObjects();

    private:
        std::vector<std::shared_ptr<Hittable>> m_hittables;
        AABB m_boundingBox;
    };
}
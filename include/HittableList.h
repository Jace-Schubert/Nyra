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
        ~HittableList();

        std::optional<HitRecord> Hit(const Nyra::Ray& ray, Interval interval) const override;

        void PushBack(std::shared_ptr<Hittable> hittable);
        void Clear();

    private:
        std::vector<std::shared_ptr<Hittable>> m_hittables;
    };
}
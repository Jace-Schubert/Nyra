#include "HittableList.h"

namespace Nyra
{
    HittableList::HittableList()
    {
    }

    HittableList::~HittableList()
    {
    }

    std::optional<HitRecord> HittableList::Hit(const Nyra::Ray& ray, Interval interval) const
    {
        std::optional<HitRecord> closestHit;
        double closestT = interval.GetMax();

        for (const std::shared_ptr<Hittable>& hittable : m_hittables)
        {
            std::optional<HitRecord> hitRecord = hittable->Hit(ray, Interval(interval.GetMin(), closestT));
            if (hitRecord.has_value())
            {
                closestT = hitRecord.value().t;
                closestHit = hitRecord;
            }
        }

        return closestHit;
    }

    void HittableList::PushBack(std::shared_ptr<Hittable> hittable)
    {
        m_hittables.push_back(std::move(hittable));
    }

    void HittableList::Clear()
    {
        m_hittables.clear();
    }
}
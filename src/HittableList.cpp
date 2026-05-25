#include "HittableList.h"

using namespace Nyra;

HittableList::HittableList()
    : m_boundingBox(Interval(0, 0), Interval(0, 0), Interval(0, 0))
{
}

HittableList::HittableList(std::shared_ptr<Hittable> hittable)
    : m_hittables({std::move(hittable)}), m_boundingBox(m_hittables[0]->GetBoundingBox())
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

AABB HittableList::GetBoundingBox() const
{
    return m_boundingBox;
}

void HittableList::Add(std::shared_ptr<Hittable> hittable)
{
    m_boundingBox = AABB(m_boundingBox, hittable->GetBoundingBox());
    m_hittables.push_back(std::move(hittable));
}

void HittableList::Clear()
{
    m_hittables.clear();
    m_boundingBox = AABB(Interval(0, 0), Interval(0, 0), Interval(0, 0));
}

std::vector<std::shared_ptr<Hittable>>& HittableList::GetObjects()
{
    return m_hittables;
}
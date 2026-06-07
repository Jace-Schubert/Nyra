#include <NyraPCH.h>
#include <Translate.h>

using namespace Nyra;

Translate::Translate(std::shared_ptr<Hittable> hittable, glm::vec3 offset)
    : m_boundingBox(hittable->GetBoundingBox()), m_hittable(hittable), m_offset(offset)
{
    m_boundingBox.Offset(offset);
}

Translate::~Translate()
{
}

std::optional<HitRecord> Translate::Hit(const Ray& ray, Interval interval) const
{
    Ray movedRay(ray.GetOrigin() - m_offset, ray.GetDirection(), ray.GetTime());
    std::optional<HitRecord> hitRecord = m_hittable->Hit(movedRay, interval);
    if (!hitRecord.has_value())
    {
        return std::nullopt;
    }

    HitRecord movedHitRecord = hitRecord.value();
    movedHitRecord.hitPoint += m_offset;
    return movedHitRecord;
}

AABB Translate::GetBoundingBox() const
{
    return m_boundingBox;
}
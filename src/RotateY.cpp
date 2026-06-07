#include <NyraPCH.h>
#include <RotateY.h>

using namespace Nyra;

RotateY::RotateY(std::shared_ptr<Hittable> hittable, float angle)
    : m_boundingBox(hittable->GetBoundingBox()), m_hittable(std::move(hittable)), m_sinTheta(std::sin(glm::radians(angle))), m_cosTheta(std::cos(glm::radians(angle)))
{
    constexpr float infinity = std::numeric_limits<float>::max();
    glm::vec3 min(infinity, infinity, infinity);
    glm::vec3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                float x = i * m_boundingBox.GetXInterval().GetMax() + ((1 - i) * m_boundingBox.GetXInterval().GetMin());
                float y = j * m_boundingBox.GetYInterval().GetMax() + ((1 - j) * m_boundingBox.GetYInterval().GetMin());
                float z = k * m_boundingBox.GetZInterval().GetMax() + ((1 - k) * m_boundingBox.GetZInterval().GetMin());

                float newX = (x * m_cosTheta) + (z * m_sinTheta);
                float newZ = (-x * m_sinTheta) + (z * m_cosTheta);

                glm::vec3 tester(newX, y, newZ);

                for (int c = 0; c < 3; c++)
                {
                    min[c] = std::fmin(min[c], tester[c]);
                    max[c] = std::fmax(max[c], tester[c]);
                }
            }
        }
    }

    m_boundingBox = AABB(min, max);
}

RotateY::~RotateY()
{
}

std::optional<HitRecord> RotateY::Hit(const Ray& ray, Interval interval) const
{
    glm::vec3 origin(
        (m_cosTheta * ray.GetOrigin().x) - (m_sinTheta * ray.GetOrigin().z),
        ray.GetOrigin().y,
        (m_sinTheta * ray.GetOrigin().x) + (m_cosTheta * ray.GetOrigin().z)
    );

    glm::vec3 direction(
        (m_cosTheta * ray.GetDirection().x) - (m_sinTheta * ray.GetDirection().z),
        ray.GetDirection().y,
        (m_sinTheta * ray.GetDirection().x) + (m_cosTheta * ray.GetDirection().z)
    );

    Ray rotatedRay(origin, direction, ray.GetTime());

    std::optional<HitRecord> hitRecord = m_hittable->Hit(rotatedRay, interval);
    if (!hitRecord.has_value())
    {
        return std::nullopt;
    }

    hitRecord.value().hitPoint = glm::vec3(
        (m_cosTheta * hitRecord.value().hitPoint.x) + (m_sinTheta * hitRecord.value().hitPoint.z),
        hitRecord.value().hitPoint.y,
        (-m_sinTheta * hitRecord.value().hitPoint.x) + (m_cosTheta * hitRecord.value().hitPoint.z)
    );

    hitRecord.value().surfaceNormal = glm::vec3(
        (m_cosTheta * hitRecord.value().surfaceNormal.x) + (m_sinTheta * hitRecord.value().surfaceNormal.z),
        hitRecord.value().surfaceNormal.y,
        (-m_sinTheta * hitRecord.value().surfaceNormal.x) + (m_cosTheta * hitRecord.value().surfaceNormal.z)
    );

    return hitRecord;
}

AABB RotateY::GetBoundingBox() const
{
    return m_boundingBox;
}
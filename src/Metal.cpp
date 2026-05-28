#include <NyraPCH.h>
#include <Metal.h>

#include <Random.h>

using namespace Nyra;

Metal::Metal(glm::vec3 albedo, float fuzz)
    : Material(albedo), m_fuzz(fuzz)
{
}

Metal::~Metal()
{
}

std::pair<glm::vec3, std::optional<Ray>> Metal::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    // Reflect ray in direction of perfect reflection from hit point
    glm::vec3 reflectedDir = glm::reflect(ray.GetDirection(), hitRecord.surfaceNormal);

    // Add fuzziness to reflected ray
    reflectedDir = glm::normalize(reflectedDir) + m_fuzz * Random::GenerateUnitVec();
    
    if (glm::dot(reflectedDir, hitRecord.surfaceNormal) <= 0)
    {
        // Reflected ray is below the surface, so ignore it
        return std::make_pair(glm::vec3(0, 0, 0), std::nullopt);
    }

    Ray reflectedRay(hitRecord.hitPoint, reflectedDir, ray.GetTime());

    return std::make_pair(m_albedo, reflectedRay);
}
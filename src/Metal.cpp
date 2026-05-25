#include <Metal.h>
#include <Random.h>

using namespace Nyra;

Metal::Metal(const raymath::color& albedo, double fuzz)
    : Material(albedo), m_fuzz(fuzz)
{
}

Metal::~Metal()
{
}

std::pair<raymath::color, std::optional<Ray>> Metal::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    // Reflect ray in direction of perfect reflection from hit point
    raymath::vec3 reflectedDir = raymath::reflect(ray.GetDirection(), hitRecord.surfaceNormal);

    // Add fuzziness to reflected ray
    reflectedDir = raymath::unitize(reflectedDir) + m_fuzz * Random::GenerateUnitVector();
    
    if (raymath::dot(reflectedDir, hitRecord.surfaceNormal) <= 0)
    {
        // Reflected ray is below the surface, so ignore it
        return std::make_pair(raymath::color(0, 0, 0), std::nullopt);
    }

    Ray reflectedRay(hitRecord.hitPoint, reflectedDir, ray.GetTime());

    return std::make_pair(m_albedo, reflectedRay);
}
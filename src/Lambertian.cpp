#include <NyraPCH.h>
#include <Lambertian.h>

#include <Random.h>
#include <Math.h>

using namespace Nyra;

Lambertian::Lambertian(glm::vec3 albedo)
    : Material(albedo)
{
}

Lambertian::~Lambertian()
{
}

std::pair<glm::vec3, std::optional<Ray>> Lambertian::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    // Scatter ray in random direction from hit point so we can send it out later to see what it hits next (i.e. bounce ray around the scene).
    // NOTE: We add a random unit vector to the surface normal to get a random reflection direction in the hemisphere above the hit point that
    // has a bias toward the surface normal. This is known as the Lambertian model.
    Ray reflectedRay(hitRecord.hitPoint, hitRecord.surfaceNormal + Random::GenerateUnitVec(), ray.GetTime());

    // Handle degenerate scatter direction (i.e. when the random unit vector happens to be exactly opposite the surface normal)
    if (Math::NearZero(reflectedRay.GetDirection()))
    {
        reflectedRay.SetDirection(hitRecord.surfaceNormal);
    }

    return std::make_pair(m_albedo, reflectedRay);
}
#include <NyraPCH.h>
#include <Dielectric.h>

#include <Math.h>
#include <Random.h>

using namespace Nyra;

Dielectric::Dielectric(float refractiveIndex)
    : Material(glm::vec3(1.0, 1.0, 1.0)), m_refractiveIndex(refractiveIndex)
{
}

Dielectric::~Dielectric()
{
}

std::pair<glm::vec3, std::optional<Ray>> Dielectric::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    float refractiveIndex = hitRecord.frontFace ? (1.0 / m_refractiveIndex) : m_refractiveIndex;
    glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
    float cosTheta = std::fmin(glm::dot(-unitDirection, hitRecord.surfaceNormal), 1.0);
    float sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

    bool cannotRefract = refractiveIndex * sinTheta > 1.0;
    glm::vec3 scatteredDir;
    
    if (cannotRefract || CalculateReflectance(cosTheta, refractiveIndex) > Random::GenerateFloat(0, 1))
    {
        // Total internal reflection, so reflect ray instead
        scatteredDir = glm::reflect(unitDirection, hitRecord.surfaceNormal);
    }
    else
    {
        // Refract ray
        scatteredDir = glm::refract(unitDirection, hitRecord.surfaceNormal, refractiveIndex);
    }

    Ray scatteredRay(hitRecord.hitPoint, scatteredDir, ray.GetTime());

    return std::make_pair(m_albedo, scatteredRay);
}

float Dielectric::CalculateReflectance(float cosTheta, float refractiveIndex) const
{
    // Use Schlick's approximation for reflectance
    float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosTheta), 5);
}
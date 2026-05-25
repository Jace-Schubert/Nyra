#include <Dielectric.h>
#include <Math.h>
#include <Random.h>

using namespace Nyra;

Dielectric::Dielectric(double refractiveIndex)
    : Material(raymath::color(1.0, 1.0, 1.0)), m_refractiveIndex(refractiveIndex)
{
}

Dielectric::~Dielectric()
{
}

std::pair<raymath::color, std::optional<Ray>> Dielectric::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    double refractiveIndex = hitRecord.frontFace ? (1.0 / m_refractiveIndex) : m_refractiveIndex;
    raymath::vec3 unitDirection = raymath::unitize(ray.GetDirection());
    double cosTheta = std::fmin(raymath::dot(-unitDirection, hitRecord.surfaceNormal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

    bool cannotRefract = refractiveIndex * sinTheta > 1.0;
    raymath::vec3 scatteredDir;
    
    if (cannotRefract || CalculateReflectance(cosTheta, refractiveIndex) > Random::GenerateDouble(0, 1))
    {
        // Total internal reflection, so reflect ray instead
        scatteredDir = raymath::reflect(unitDirection, hitRecord.surfaceNormal);
    }
    else
    {
        // Refract ray
        scatteredDir = Math::Refract(unitDirection, hitRecord.surfaceNormal, refractiveIndex);
    }

    Ray scatteredRay(hitRecord.hitPoint, scatteredDir, ray.GetTime());

    return std::make_pair(m_albedo, scatteredRay);
}

double Dielectric::CalculateReflectance(double cosTheta, double refractiveIndex) const
{
    // Use Schlick's approximation for reflectance
    double r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosTheta), 5);
}
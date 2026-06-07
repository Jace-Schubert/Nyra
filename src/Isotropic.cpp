#include <NyraPCH.h>
#include <Isotropic.h>

#include <Random.h>

using namespace Nyra;

Isotropic::Isotropic(std::shared_ptr<Texture> texture)
    : Material(glm::vec3(0.0f, 0.0f, 0.0f)), m_texture(std::move(texture))
{
}

Isotropic::~Isotropic()
{
}

std::pair<glm::vec3, std::optional<Ray>> Isotropic::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    glm::vec3 attenuation = m_texture->GetColor(hitRecord.uTextureCoordinate, hitRecord.vTextureCoordinate, hitRecord.hitPoint);
    Ray scatteredRay(hitRecord.hitPoint, Random::GenerateUnitVec(), ray.GetTime());
    return std::make_pair(attenuation, scatteredRay);
}
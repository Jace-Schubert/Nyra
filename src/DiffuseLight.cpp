#include <NyraPCH.h>
#include <DiffuseLight.h>

using namespace Nyra;

DiffuseLight::DiffuseLight(std::shared_ptr<Texture> texture)
    : Material(glm::vec3(0)), m_texture(texture)
{
}

DiffuseLight::~DiffuseLight()
{
}

std::pair<glm::vec3, std::optional<Ray>> DiffuseLight::Scatter(const Ray& ray, const HitRecord& hitRecord) const
{
    return std::make_pair(glm::vec3(0, 0, 0), std::nullopt); // Light is not reflected or transmitted in any direction since it is a pure emitter, so return nullopt for scattered ray
}

glm::vec3 DiffuseLight::GetEmittedLight(float u, float v, glm::vec3 point) const
{
    return m_texture->GetColor(u, v, point);
}
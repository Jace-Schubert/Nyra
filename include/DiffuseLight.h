#pragma once

#include <Material.h>
#include <Texture.h>

namespace Nyra
{
    class DiffuseLight : public Material
    {
    public:
        DiffuseLight(std::shared_ptr<Texture> texture);
        ~DiffuseLight();

        virtual std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const override;

        virtual glm::vec3 GetEmittedLight(float u, float v, glm::vec3 point) const override;

    private:
        std::shared_ptr<Texture> m_texture;
    };
}
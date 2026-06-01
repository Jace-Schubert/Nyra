#pragma once

#include <Material.h>
#include <Texture.h>

namespace Nyra
{
    class Lambertian : public Material
    {
    public:
        Lambertian(glm::vec3 albedo);
        Lambertian(std::shared_ptr<Texture> texture);

        ~Lambertian();

        std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const override;

    private:
        std::shared_ptr<Texture> m_texture;
    };
}
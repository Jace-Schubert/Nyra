#pragma once

#include <Material.h>
#include <Texture.h>

namespace Nyra
{
    class Isotropic : public Material
    {
    public:
        Isotropic(std::shared_ptr<Texture> texture);
        ~Isotropic();

        virtual std::pair<glm::vec3, std::optional<Ray>> Scatter(const Ray& ray, const HitRecord& hitRecord) const override;

    private:
        std::shared_ptr<Texture> m_texture;
    };
}
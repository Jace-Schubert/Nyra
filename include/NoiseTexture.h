#pragma once

#include <Texture.h>
#include <Perlin.h>

namespace Nyra
{
    class NoiseTexture : public Texture
    {
    public:
        NoiseTexture(float scale);
        ~NoiseTexture();

        virtual glm::vec3 GetColor(float u, float v, glm::vec3 point) const override;

    private:
        Perlin m_noise;
        float m_scale;
    };
}
#pragma once

#include <NyraPCH.h>

namespace Nyra
{
    class Perlin
    {
    public:
        Perlin();
        ~Perlin();

        float GenerateNoise(glm::vec3 point) const;

        float GenerateTurbulence(glm::vec3 point, int depth) const;

    private:
        std::array<glm::vec3, 256> m_randomVecs;
        std::array<int, 256> m_xPermute;
        std::array<int, 256> m_yPermute;
        std::array<int, 256> m_zPermute;
    };
}
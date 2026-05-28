#pragma once

#include <random>

#include <Math.h>

namespace Nyra::Random
{
    inline float GenerateFloat(float min, float max)
    {
        thread_local static std::mt19937 generator(std::random_device{}());
        thread_local static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        
        return distribution(generator) * (max - min) + min;
    }

    inline int GenerateInt(int min, int max)
    {
        return static_cast<int>(GenerateFloat(min, max + 1));
    }

    inline glm::vec3 GenerateVec3(float min, float max)
    {
        return glm::vec3(GenerateFloat(min, max), GenerateFloat(min, max), GenerateFloat(min, max));
    }

    inline glm::vec3 GenerateUnitVec()
    {
        while (true)
        {
            glm::vec3 vec = GenerateVec3(-1, 1);
            float lSquared = Math::LengthSquared(vec);
            if (1e-160 < lSquared && lSquared <= 1)
            {
                return vec / std::sqrt(lSquared);
            }
        }
    }

    inline glm::vec3 GenerateVecInUnitDisk()
    {
        while (true)
        {
            glm::vec3 vec = glm::vec3(GenerateFloat(-1, 1), GenerateFloat(-1, 1), 0);
            if (Math::LengthSquared(vec) < 1)
            {
                return vec;
            }
        }
    }
}
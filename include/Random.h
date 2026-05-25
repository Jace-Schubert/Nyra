#pragma once

#include <random>

#include <vec3.h>

namespace Nyra::Random
{
    inline double GenerateDouble(double min, double max)
    {
        thread_local static std::mt19937 generator(std::random_device{}());
        thread_local static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        
        return distribution(generator) * (max - min) + min;
    }

    inline int GenerateInt(int min, int max)
    {
        return static_cast<int>(GenerateDouble(min, max + 1));
    }

    inline raymath::vec3 GenerateVector3(double min, double max)
    {
        return raymath::vec3(GenerateDouble(min, max), GenerateDouble(min, max), GenerateDouble(min, max));
    }

    inline raymath::vec3 GenerateUnitVector()
    {
        while (true)
        {
            raymath::vec3 vec = GenerateVector3(-1, 1);
            double lSquared = vec.length_squared();
            if (1e-160 < lSquared && lSquared <= 1)
            {
                return vec / std::sqrt(lSquared);
            }
        }
    }

    inline raymath::vec3 GenerateVectorInUnitDisk()
    {
        while (true)
        {
            raymath::vec3 vec = raymath::vec3(GenerateDouble(-1, 1), GenerateDouble(-1, 1), 0);
            if (vec.length_squared() < 1)
            {
                return vec;
            }
        }
    }
}
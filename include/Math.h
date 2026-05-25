#pragma once

#include <vec3.h>

namespace Nyra::Math
{
    inline raymath::vec3 Refract(const raymath::vec3& uv, const raymath::vec3& normal, double etaRatio)
    {
        double cosTheta = std::fmin(raymath::dot(-uv, normal), 1.0);
        raymath::vec3 rOutPerp = etaRatio * (uv + cosTheta * normal);
        raymath::vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.length_squared())) * normal;
        return rOutPerp + rOutParallel;
    }

    constexpr inline double radians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }
}
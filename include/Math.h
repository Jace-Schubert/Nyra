#pragma once

namespace Nyra::Math
{
    inline bool NearZero(glm::vec3 v) { return (std::fabs(v.x) < 1e-8) && (std::fabs(v.y) < 1e-8) && (std::fabs(v.z) < 1e-8); }
    
    inline float LengthSquared(glm::vec3 v) { return glm::dot(v, v); }
}
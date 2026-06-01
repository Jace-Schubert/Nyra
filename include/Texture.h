#pragma once

#include <NyraPCH.h>

class Texture
{
public:
    virtual ~Texture() = default;

    virtual glm::vec3 GetColor(float u, float v, glm::vec3 point) const = 0;
};
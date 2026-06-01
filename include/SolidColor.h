#pragma once

#include "Texture.h"

class SolidColor : public Texture
{
public:
    SolidColor(glm::vec3 color);
    ~SolidColor();

    virtual glm::vec3 GetColor(float u, float v, glm::vec3 point) const override;

private:
    glm::vec3 m_color;
};
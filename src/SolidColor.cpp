#include <NyraPCH.h>
#include <SolidColor.h>

SolidColor::SolidColor(glm::vec3 color)
    : m_color(color)
{
}

SolidColor::~SolidColor()
{
}

glm::vec3 SolidColor::GetColor(float u, float v, glm::vec3 point) const
{
    return m_color;
}
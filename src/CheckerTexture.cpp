#include <NyraPCH.h>
#include <CheckerTexture.h>

CheckerTexture::CheckerTexture(float scale, std::shared_ptr<Texture> evenTexture, std::shared_ptr<Texture> oddTexture)
    : m_inverseScale(1 / scale), m_evenTexture(std::move(evenTexture)), m_oddTexture(std::move(oddTexture))
{
}

CheckerTexture::~CheckerTexture()
{
}

glm::vec3 CheckerTexture::GetColor(float u, float v, glm::vec3 point) const
{
    int xInteger = int(std::floor(m_inverseScale * point.x));
    int yInteger = int(std::floor(m_inverseScale * point.y));
    int zInteger = int(std::floor(m_inverseScale * point.z));

    bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;
    return isEven ? m_evenTexture->GetColor(u, v, point) : m_oddTexture->GetColor(u, v, point);
}
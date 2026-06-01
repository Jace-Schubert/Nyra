#include <NyraPCH.h>
#include <NoiseTexture.h>

using namespace Nyra;

NoiseTexture::NoiseTexture(float scale)
    : m_noise(), m_scale(scale)
{
}

NoiseTexture::~NoiseTexture()
{
}

glm::vec3 NoiseTexture::GetColor(float u, float v, glm::vec3 point) const
{
    return glm::vec3(0.5f, 0.5f, 0.5f) * (1 + std::sin(m_scale * point.z + 10 * m_noise.GenerateTurbulence(point, 7)));    
}
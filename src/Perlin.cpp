#include <NyraPCH.h>
#include <Perlin.h>

#include <Random.h>

using namespace Nyra;

namespace
{
    void GeneratePermute(std::array<int, 256>& buffer)
    {
        for (int i = buffer.size() - 1; i > 0; i--)
        {
            int randomInt = Random::GenerateInt(0, 255);
            std::swap(buffer[i], buffer[randomInt]);
        }
    }
}

Perlin::Perlin()
    : m_randomVecs(), m_xPermute(), m_yPermute(), m_zPermute()
{
    for (glm::vec3& vec : m_randomVecs)
    {
        vec = glm::normalize(Random::GenerateVec3(-1.0f, 1.0f));
    }

    std::iota(m_xPermute.begin(), m_xPermute.end(), 0);
    std::iota(m_yPermute.begin(), m_yPermute.end(), 0);
    std::iota(m_zPermute.begin(), m_zPermute.end(), 0);

    GeneratePermute(m_xPermute);
    GeneratePermute(m_yPermute);
    GeneratePermute(m_zPermute);
}

Perlin::~Perlin()
{
}

float Perlin::GenerateNoise(glm::vec3 point) const
{
    float u = point.x - std::floor(point.x);
    float v = point.y - std::floor(point.y);
    float w = point.z - std::floor(point.z);

    float uu = u*u*(3 - 2*u);
    float vv = v*v*(3 - 2*v);
    float ww = w*w*(3 - 2*w);

    int i = int(std::floor(point.x));
    int j =  int(std::floor(point.y));
    int k =  int(std::floor(point.z));

    float total = 0.0f;

    for (int di = 0; di < 2; di++)
    {
        for (int dj = 0; dj < 2; dj++)
        {
            for (int dk = 0; dk < 2; dk++)
            {
                glm::vec3 weight(u - di, v - dj, w - dk);
                total += (di*uu + (1 - di) * (1 - uu))
                         * (dj*vv + (1 - dj) * (1 - vv))
                         * (dk*ww + (1 - dk) * (1 - ww))
                         * glm::dot(m_randomVecs[m_xPermute[(i + di) & 255] ^ m_yPermute[(j + dj) & 255] ^ m_zPermute[(k + dk) & 255]], weight);

            }
        }
    }

    return total;
}

float Perlin::GenerateTurbulence(glm::vec3 point, int depth) const
{
    float total = 0.0f;
    float weight = 1.0f;

    for (int i = 0; i < depth; i++)
    {
        total += weight * GenerateNoise(point);
        weight *= 0.5f;
        point *= 2.0f;
    }

    return std::fabs(total);
}
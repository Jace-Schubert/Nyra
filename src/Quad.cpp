#include <NyraPCH.h>
#include <Quad.h>

using namespace Nyra;

namespace 
{
    AABB ComputeBoundingBox(glm::vec3 Q, glm::vec3 u, glm::vec3 v)
    {
        AABB boundingBox1(Q, Q + u + v);
        AABB boundingBox2(Q + u, Q + v);
        return AABB(boundingBox1, boundingBox2);
    }
}

Quad::Quad(glm::vec3 Q, glm::vec3 u, glm::vec3 v, std::shared_ptr<Material> material)
    : m_boundingBox(ComputeBoundingBox(Q, u, v)), m_Q(Q), m_u(u), m_v(v), m_w(glm::cross(u, v) / glm::dot(glm::cross(u, v), glm::cross(u, v))), m_normal(glm::normalize(glm::cross(u, v))), m_material(material), m_D(glm::dot(m_normal, Q))
{
}

Quad::~Quad()
{
}

AABB Quad::GetBoundingBox() const
{
    return m_boundingBox;
}

std::optional<HitRecord> Quad::Hit(const Ray& ray, Interval interval) const
{
    // Compute plane normal and intersection point with plane
    float denominator = glm::dot(ray.GetDirection(), m_normal);
    if (std::abs(denominator) < 0.0001f)
    {
        return std::nullopt; // Ray is parallel to plane, so no hit
    }

    float t = (m_D - glm::dot(m_normal, ray.GetOrigin())) / denominator;
    if (!interval.Contains(t))
    {
        return std::nullopt; // Intersection with plane is outside of valid interval, so no hit
    }

    glm::vec3 hitPoint = ray.At(t);
    glm::vec3 planarHitPointVector = hitPoint - m_Q;
    float alpha = glm::dot(m_w, glm::cross(planarHitPointVector, m_v));
    float beta = glm::dot(m_w, glm::cross(m_u, planarHitPointVector));

    Interval unitInterval(0.0f, 1.0f);
    if (!unitInterval.Contains(alpha) || !unitInterval.Contains(beta))
    {
        return std::nullopt; // Hit point is outside of quad bounds, so no hit
    }

    // Hit point is valid, so create hit record
    HitRecord hitRecord;
    hitRecord.t = t;
    hitRecord.material = m_material;
    hitRecord.hitPoint = hitPoint;
    hitRecord.SetFaceNormal(ray, m_normal);
    hitRecord.uTextureCoordinate = alpha;
    hitRecord.vTextureCoordinate = beta;

    return hitRecord;
}
#include <NyraPCH.h>
#include <Sphere.h>

#include <Math.h>

using namespace Nyra;

namespace
{
    // Initialization helpers
    AABB ComputeBoundingBox(glm::vec3 center, float radius)
    {
        glm::vec3 radiusVec(radius, radius, radius);
        return AABB(center - radiusVec, center + radiusVec);
    }

    AABB ComputeBoundingBox(glm::vec3 centerAtStart, glm::vec3 centerAtEnd, float radius)
    {
        glm::vec3 radiusVec(radius, radius, radius);
        AABB boxAtStart(centerAtStart - radiusVec, centerAtStart + radiusVec);
        AABB boxAtEnd(centerAtEnd - radiusVec, centerAtEnd + radiusVec);
        return AABB(boxAtStart, boxAtEnd);
    }

    std::array<float, 2> MapPointToTextureCoordinates(glm::vec3 point)
    {
        float pi = std::numbers::pi_v<float>;

        float y = std::clamp(-point.y, -1.0f, 1.0f);

        float theta = std::acos(y);
        float phi = std::atan2(-point.z, point.x) + pi;

        float uTextureCoordinate = phi / (2*pi);
        float vTextureCoordinate = theta / pi;

        return std::array<float, 2>({ uTextureCoordinate, vTextureCoordinate });
    }
}

Sphere::Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material)
    : m_boundingBox(ComputeBoundingBox(center, radius)), m_center(center, glm::vec3(0, 0, 0)), m_material(std::move(material)), m_radius(radius)
{
}

Sphere::Sphere(glm::vec3 center1, glm::vec3 center2, float radius, std::shared_ptr<Material> material)
    : m_boundingBox(ComputeBoundingBox(center1, center2, radius)), m_center(center1, center2 - center1), m_material(std::move(material)), m_radius(radius)
{
}

Sphere::~Sphere() 
{
}

std::optional<HitRecord> Sphere::Hit(const Nyra::Ray& ray, Interval interval) const
{
    glm::vec3 currentCenter = m_center.At(ray.GetTime());
    glm::vec3 oc = currentCenter - ray.GetOrigin();
    float a = Math::LengthSquared(ray.GetDirection());
    float h = glm::dot(ray.GetDirection(), oc);
    float c = Math::LengthSquared(oc) - (m_radius * m_radius);
    float discriminant = h*h - a*c;
    if (discriminant < 0)
    {
        // Miss
        return std::nullopt;
    }

    // Find the nearest root that lies in the acceptable range
    float root = (h - std::sqrt(discriminant)) / a;
    if (!interval.Surrounds(root))
    {
        root = (h + std::sqrt(discriminant)) / a;
        if (!interval.Surrounds(root))
        {
            // Miss
            return std::nullopt;
        }
    }

    HitRecord record;
    record.material = m_material;
    record.t = root;
    record.hitPoint = ray.At(record.t);
    glm::vec3 outwardNormal = (record.hitPoint - currentCenter) / m_radius;
    record.SetFaceNormal(ray, outwardNormal);

    std::array<float, 2> textureCoordinates = MapPointToTextureCoordinates(outwardNormal);
    record.uTextureCoordinate = textureCoordinates[0];
    record.vTextureCoordinate = textureCoordinates[1];

    return record;
}

AABB Sphere::GetBoundingBox() const
{
    return m_boundingBox;
}

// Setters & Getters
const Ray& Sphere::GetCenter() const
{
    return m_center;
}
void Sphere::SetCenter(const Ray& center)
{
    m_center = center;
}

float Sphere::GetRadius() const
{
    return m_radius;
}
void Sphere::SetRadius(float radius)
{
    m_radius = radius;
}

const std::shared_ptr<Material>& Sphere::GetMaterial() const
{
    return m_material;
}
void Sphere::SetMaterial(std::shared_ptr<Material> material)
{
    m_material = std::move(material);
}
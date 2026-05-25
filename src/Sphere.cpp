#include <Sphere.h>

using namespace Nyra;

namespace
{
    // Initialization helpers
    AABB ComputeBoundingBox(raymath::point3 center, double radius)
    {
        raymath::vec3 radiusVec(radius, radius, radius);
        return AABB(center - radiusVec, center + radiusVec);
    }

    AABB ComputeBoundingBox(raymath::point3 centerAtStart, raymath::point3 centerAtEnd, double radius)
    {
        raymath::vec3 radiusVec(radius, radius, radius);
        return AABB(centerAtStart - radiusVec, centerAtEnd + radiusVec);
    }
}

Sphere::Sphere(const raymath::point3& center, double radius, std::shared_ptr<Material> material)
    : m_boundingBox(ComputeBoundingBox(center, radius)), m_center(center, raymath::vec3(0, 0, 0)), m_radius(radius), m_material(std::move(material))
{
}

Sphere::Sphere(const raymath::point3& center1, const raymath::point3& center2, double radius, std::shared_ptr<Material> material)
    : m_boundingBox(ComputeBoundingBox(center1, center2, radius)), m_center(center1, center2 - center1), m_radius(radius), m_material(std::move(material))
{
}

Sphere::~Sphere() 
{
}

std::optional<HitRecord> Sphere::Hit(const Nyra::Ray& ray, Interval interval) const
{
    raymath::point3 currentCenter = m_center.At(ray.GetTime());
    raymath::vec3 oc = currentCenter - ray.GetOrigin();
    double a = ray.GetDirection().length_squared();
    double h = raymath::dot(ray.GetDirection(), oc);
    double c = oc.length_squared() - m_radius*m_radius;
    double discriminant = h*h - a*c;
    if (discriminant < 0)
    {
        // Miss
        return std::nullopt;
    }

    // Find the nearest root that lies in the acceptable range
    double root = (h - std::sqrt(discriminant)) / a;
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
    record.SetFaceNormal(ray, (record.hitPoint - currentCenter) / m_radius);
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

double Sphere::GetRadius() const
{
    return m_radius;
}
void Sphere::SetRadius(double radius)
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
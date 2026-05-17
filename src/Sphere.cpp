#include "Sphere.h"

namespace Nyra
{
    Sphere::Sphere(const raymath::point3& center, double radius)
    : m_center(center), m_radius(radius)
    {
    }

    Sphere::~Sphere() 
    {
    }

    std::optional<HitRecord> Sphere::Hit(const Nyra::Ray& ray, Interval interval) const
    {
        raymath::vec3 oc = m_center - ray.GetOrigin();
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
        record.t = root;
        record.hitPoint = ray.At(record.t);
        record.SetFaceNormal(ray, raymath::unitize(record.hitPoint - m_center));
        return record;
    }
}
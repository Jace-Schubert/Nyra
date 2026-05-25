#pragma once

#include <Hittable.h>
#include <vec3.h>

namespace Nyra
{
    class Sphere : public Hittable
    {
    public:
        Sphere(const raymath::point3& center, double radius, std::shared_ptr<Material> material);
        Sphere(const raymath::point3& center1, const raymath::point3& center2, double radius, std::shared_ptr<Material> material);
        ~Sphere();

        // Hittable overrides
        virtual std::optional<HitRecord> Hit(const Nyra::Ray& ray, Interval interval) const override;
        virtual AABB GetBoundingBox() const override;

        // Setters & Getters
        const Ray& GetCenter() const;
        void SetCenter(const Ray& center);

        double GetRadius() const;
        void SetRadius(double radius);

        const std::shared_ptr<Material>& GetMaterial() const;
        void SetMaterial(std::shared_ptr<Material> material);

    private:
        AABB m_boundingBox;
        Ray m_center;
        std::shared_ptr<Material> m_material;
        double m_radius;
    };
}
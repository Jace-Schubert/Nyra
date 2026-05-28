#pragma once

#include <Hittable.h>

namespace Nyra
{
    class Sphere : public Hittable
    {
    public:
        Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material);
        Sphere(glm::vec3 center1, glm::vec3 center2, float radius, std::shared_ptr<Material> material);
        ~Sphere();

        // Hittable overrides
        virtual std::optional<HitRecord> Hit(const Ray& ray, Interval interval) const override;
        virtual AABB GetBoundingBox() const override;

        // Setters & Getters
        const Ray& GetCenter() const;
        void SetCenter(const Ray& center);

        float GetRadius() const;
        void SetRadius(float radius);

        const std::shared_ptr<Material>& GetMaterial() const;
        void SetMaterial(std::shared_ptr<Material> material);

    private:
        AABB m_boundingBox;
        Ray m_center;
        std::shared_ptr<Material> m_material;
        float m_radius;
    };
}
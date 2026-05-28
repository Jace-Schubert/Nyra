#pragma once

#include <AABB.h>
#include <Ray.h>
#include <Interval.h>

namespace Nyra
{
    class Material;

    struct HitRecord
    {
        glm::vec3 hitPoint;
        glm::vec3 surfaceNormal;
        std::shared_ptr<Material> material;
        float t;
        bool frontFace;

        // Sets the surface normal to always point against the ray direction (i.e. towards the ray origin)
        // NOTE: outwardNormal should be unitized before being passed in
        void SetFaceNormal(const Ray& ray, glm::vec3 outwardNormal)
        {
            frontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
            surfaceNormal = frontFace ? outwardNormal : -outwardNormal;
        }
    };

    class Hittable 
    {
    public:
        virtual ~Hittable() = default;

        virtual std::optional<HitRecord> Hit(const Ray& ray, Interval interval) const = 0;

        virtual AABB GetBoundingBox() const = 0;
    };
}
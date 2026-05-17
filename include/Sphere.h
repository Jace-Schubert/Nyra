#pragma once

#include <Hittable.h>
#include <vec3.h>

namespace Nyra
{
    class Sphere : public Hittable
    {
    public:
        Sphere(const raymath::point3& center, double radius);
        ~Sphere();

        virtual std::optional<HitRecord> Hit(const Nyra::Ray& ray, Interval interval) const override;

        const raymath::point3& GetCenter() const;
        void SetCenter(const raymath::point3& center);

        double GetRadius() const;
        void SetRadius(double radius);

    private:
        raymath::point3 m_center;
        double m_radius;
    };
}
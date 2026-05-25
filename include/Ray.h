#pragma once

#include <vec3.h>

namespace Nyra
{
    class Ray
    {
    public:
        Ray(const raymath::point3& origin, const raymath::vec3& direction, double time);
        Ray(const raymath::point3& origin, const raymath::vec3& direction);

        raymath::vec3 At(double t) const;

        const raymath::point3& GetOrigin() const;
        void SetOrigin(const raymath::point3& origin);

        const raymath::vec3& GetDirection() const;
        void SetDirection(const raymath::vec3& direction);
        
        double GetTime() const;
        void SetTime(double time);

    private:
        raymath::point3 m_origin;
        raymath::vec3 m_dir;
        double m_time;
    };
}
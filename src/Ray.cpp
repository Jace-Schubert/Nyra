#pragma once

#include <Ray.h>

namespace Nyra
{
    Ray::Ray(const raymath::point3& origin, const raymath::vec3& direction)
        : m_origin(origin), m_dir(direction)
    {
    }

    raymath::vec3 Ray::At(double t) const
    {
        return m_origin + (t * m_dir);
    }

    // Getters & Setters
    const raymath::point3& Ray::GetOrigin() const
    {
        return m_origin;
    }
    void Ray::SetOrigin(const raymath::point3& origin)
    {
        m_origin = origin;
    }

    const raymath::vec3& Ray::GetDirection() const
    {
        return m_dir;
    }
    void Ray::SetDirection(const raymath::vec3& direction)
    {
        m_dir = direction;
    }
}
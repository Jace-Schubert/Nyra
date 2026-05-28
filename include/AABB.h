#pragma once

#include <NyraPCH.h>

#include <Interval.h>
#include <Ray.h>

namespace Nyra
{
    class AABB
    {
    public:
        AABB(Interval xInterval, Interval yInterval, Interval zInterval);
        AABB(glm::vec3 point1, glm::vec3 point2);
        AABB(const AABB& lhs, const AABB& rhs);
        ~AABB();

        bool Hit(const Ray& ray, Interval interval) const;

        // returns the index of the longest axis of the bounding box (0 = x, 1 = y, 2 = z)
        int ComputeLongestAxis() const;

        // Getters & Setters
        Interval GetXInterval() const;
        void SetXInterval(Interval xInterval);
        Interval GetYInterval() const;
        void SetYInterval(Interval yInterval);
        Interval GetZInterval() const;
        void SetZInterval(Interval zInterval);

        // Operators for convenient access to intervals by index (0 = x, 1 = y, 2 = z)
        Interval operator[](int i) const;
        Interval& operator[](int i);

    private:
        std::array<Interval, 3> m_intervals;
    };
}
#include <NyraPCH.h>
#include <AABB.h>

using namespace Nyra;

AABB::AABB(Interval xInterval, Interval yInterval, Interval zInterval)
    : m_intervals({xInterval, yInterval, zInterval})
{
    PadNearEmptyIntervals();
}

AABB::AABB(glm::vec3 point1, glm::vec3 point2)
    : m_intervals({Interval(std::fmin(point1.x, point2.x), std::fmax(point1.x, point2.x)),
                   Interval(std::fmin(point1.y, point2.y), std::fmax(point1.y, point2.y)),
                   Interval(std::fmin(point1.z, point2.z), std::fmax(point1.z, point2.z))})
{
    PadNearEmptyIntervals();
}

AABB::AABB(const AABB& lhs, const AABB& rhs)
    : m_intervals({Interval(lhs.GetXInterval(), rhs.GetXInterval()),
                   Interval(lhs.GetYInterval(), rhs.GetYInterval()),
                   Interval(lhs.GetZInterval(), rhs.GetZInterval())})
{
}

AABB::~AABB()
{
}

bool AABB::Hit(const Ray& ray, Interval interval) const
{
    // Check if ray hits all 3 axes
    for (int i = 0; i < 3; i++)
    {
        float inverseDirection = 1.0 / ray.GetDirection()[i];
        float t0 = (m_intervals[i].GetMin() - ray.GetOrigin()[i]) * inverseDirection;
        float t1 = (m_intervals[i].GetMax() - ray.GetOrigin()[i]) * inverseDirection;

        if (inverseDirection < 0.0)
        {
            std::swap(t0, t1);
        }

        // Confirm intervals overlap, otherwise ray misses box
        interval = Interval(std::fmax(t0, interval.GetMin()), std::fmin(t1, interval.GetMax()));
        if (interval.GetMin() >= interval.GetMax())
        {
            return false;
        }
    }

    return true;
}

int AABB::ComputeLongestAxis() const
{
    float xLength = m_intervals[0].GetMax() - m_intervals[0].GetMin();
    float yLength = m_intervals[1].GetMax() - m_intervals[1].GetMin();
    float zLength = m_intervals[2].GetMax() - m_intervals[2].GetMin();

    if (xLength > yLength && xLength > zLength)
    {
        return 0;
    }
    else if (yLength > zLength)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

// Setters & Getters
Interval AABB::GetXInterval() const
{
    return m_intervals[0];
}
void AABB::SetXInterval(Interval xInterval)
{
    m_intervals[0] = xInterval;
}

Interval AABB::GetYInterval() const
{
    return m_intervals[1];
}
void AABB::SetYInterval(Interval yInterval)
{
    m_intervals[1] = yInterval;
}

Interval AABB::GetZInterval() const
{
    return m_intervals[2];
}
void AABB::SetZInterval(Interval zInterval)
{
    m_intervals[2] = zInterval;
}

Interval AABB::operator[](int i) const
{
    return m_intervals[i];
}

Interval& AABB::operator[](int i)
{
    return m_intervals[i];
}

//===============//
// Private Utils //
//===============//
void AABB::PadNearEmptyIntervals()
{
    float min = 0.001f;
    for (Interval& interval : m_intervals)
    {
        if (interval.GetRange() < min)
        {
            interval.Expand(min);
        }
    }
}
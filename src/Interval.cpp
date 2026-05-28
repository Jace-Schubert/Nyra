#include <NyraPCH.h>
#include <Interval.h>

using namespace Nyra;

Interval::Interval(float min, float max)
    : m_min(min), m_max(max)
{
}  

Interval::Interval(Interval lhs, Interval rhs)
    : m_min(std::fmin(lhs.GetMin(), rhs.GetMin())), m_max(std::fmax(lhs.GetMax(), rhs.GetMax()))
{
}

Interval::~Interval()
{
}

bool Interval::Contains(float value) const
{
    return value >= m_min && value <= m_max;
}

bool Interval::Surrounds(float value) const
{
    return value > m_min && value < m_max;
}

float Interval::Clamp(float value) const
{
    if (value < m_min)
    {
        return m_min;
    }

    else if (value > m_max)
    {
        return m_max;
    }

    return value;
}

void Interval::Expand(float delta)
{
    m_min -= delta / 2;
    m_max += delta / 2;
}

float Interval::GetMin() const
{
    return m_min;
}

float Interval::GetMax() const
{
    return m_max;
}
#include <Interval.h>

#include <cmath>

using namespace Nyra;

Interval::Interval(double min, double max)
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

bool Interval::Contains(double value) const
{
    return value >= m_min && value <= m_max;
}

bool Interval::Surrounds(double value) const
{
    return value > m_min && value < m_max;
}

double Interval::Clamp(double value) const
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

void Interval::Expand(double delta)
{
    m_min -= delta / 2;
    m_max += delta / 2;
}

double Interval::GetMin() const
{
    return m_min;
}

double Interval::GetMax() const
{
    return m_max;
}
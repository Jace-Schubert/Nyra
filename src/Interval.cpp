#include <Interval.h>

Interval::Interval(double min, double max)
    : m_min(min), m_max(max)
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

double Interval::GetMin() const
{
    return m_min;
}

double Interval::GetMax() const
{
    return m_max;
}
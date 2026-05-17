#pragma once

class Interval 
{
public:
    Interval(double min, double max);
    ~Interval();

    bool Contains(double value) const;
    bool Surrounds(double value) const;

    double GetMin() const;
    double GetMax() const;

private:
    double m_min;
    double m_max;
};

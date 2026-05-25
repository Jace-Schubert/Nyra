#pragma once

namespace Nyra
{
    class Interval 
    {
    public:
        Interval(double min, double max);

        // Constructs an interval that encompasses both input intervals
        Interval(Interval lhs, Interval rhs);
        
        ~Interval();

        bool Contains(double value) const;
        bool Surrounds(double value) const;
        double Clamp(double value) const;
        void Expand(double delta);

        double GetMin() const;
        double GetMax() const;

    private:
        double m_min;
        double m_max;
    };
}
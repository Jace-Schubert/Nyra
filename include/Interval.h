#pragma once

namespace Nyra
{
    class Interval 
    {
    public:
        Interval(float min, float max);

        // Constructs an interval that encompasses both input intervals
        Interval(Interval lhs, Interval rhs);
        
        ~Interval();

        bool Contains(float value) const;
        bool Surrounds(float value) const;
        float Clamp(float value) const;
        void Expand(float delta);

        float GetMin() const;
        float GetMax() const;

    private:
        float m_min;
        float m_max;
    };
}
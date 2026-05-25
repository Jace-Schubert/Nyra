#pragma once

#include <cmath>
#include <iostream>

namespace raymath
{    
    struct vec3
    {
        vec3() : x(0), y(0), z(0) {}
        vec3(double e0, double e1, double e2) : x(e0), y(e1), z(e2) {}

        double length() const { return std::sqrt(x*x + y*y + z*z); }
        double length_squared() const { return x*x + y*y + z*z; }
        bool near_zero() const { return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8) && (std::fabs(z) < 1e-8); }

        // Operators
        vec3 operator-() const { return vec3(-x, -y, -z); }
        double operator[](int i) const { return (&x)[i]; }
        double& operator[](int i) { return (&x)[i]; }

        vec3& operator+=(const vec3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        
        vec3& operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        
        vec3& operator/=(double scalar)
        {
            return *this *= 1/scalar;
        }
        
        union
        {
            struct { double x, y, z; };
            struct { double r, g, b; };
        };
    };
    
    // Aliases
    using point3 = vec3;
    using color = vec3;
    
    // Operator utils
    inline vec3 operator+(const vec3& lhs, const vec3& rhs) { return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

    inline vec3 operator-(const vec3& lhs, const vec3& rhs) { return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

    inline vec3 operator*(const vec3& lhs, const vec3& rhs) { return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
    inline vec3 operator*(const vec3& v, double scalar) { return vec3(v.x * scalar, v.y * scalar, v.z * scalar); }
    inline vec3 operator*(double scalar, const vec3& v) { return v * scalar; }

    inline vec3 operator/(const vec3& v, double scalar) { return v * (1/scalar); }

    // Utils
    inline double dot(const vec3& lhs, const vec3& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }

    inline vec3 cross(const vec3& lhs, const vec3& rhs) 
    {
        return vec3(
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        );
    }

    inline vec3 unitize(const vec3& v) { return v / v.length(); }

    inline vec3 reflect(const vec3& v, const vec3& n)
    {
        return v - (2 * dot(v, n) * n);
    }
}
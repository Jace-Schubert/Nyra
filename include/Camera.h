#pragma once

#include <vec3.h>
#include <Ray.h>
#include <HittableList.h>

class Camera
{
public:
    Camera();
    ~Camera();

    void render(const Nyra::HittableList& world) const;

private:
    raymath::color CalculateRayColor(const Nyra::Ray& ray, const Nyra::HittableList& world) const;
    void WriteColor(const raymath::color& pixelColor) const;

private:
    // Image
    int m_imageWidth;
    int m_imageHeight;

    // Camera
    raymath::point3 m_center;
    raymath::vec3 m_pixelDeltaU;
    raymath::vec3 m_pixelDeltaV;
    raymath::point3 m_pixel00Loc;
};
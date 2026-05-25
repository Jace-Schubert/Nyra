#pragma once

#include <vec3.h>
#include <Ray.h>
#include <HittableList.h>

namespace Nyra
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void render(const Nyra::HittableList& world) const;

    private:
        Nyra::Ray GenerateRay(double i, double j) const;
        raymath::point3 GenerateDefocusDiskSample() const;
        raymath::point3 GenerateRandomPixelOffset() const;
        raymath::color CalculateRayColor(const Nyra::Ray& ray, uint32_t depth, const Nyra::HittableList& world) const;
        void CreatePPMFromBuffer(const std::vector<uint8_t>& buffer, const std::string& filename) const;
        raymath::color LinearToGamma(const raymath::color& linearColor) const;

    private:
        // Image
        int m_imageWidth;
        int m_imageHeight;

        // Camera
        raymath::point3 m_center;
        raymath::vec3 m_pixelDeltaU;
        raymath::vec3 m_pixelDeltaV;
        raymath::point3 m_pixel00Loc;
        raymath::vec3 m_defocusDiskU;
        raymath::vec3 m_defocusDiskV;
        double m_defocusAngle;
        uint32_t m_maxRayDepth;
        int m_samplesPerPixel;
    };
}
#pragma once

#include <Ray.h>
#include <HittableList.h>

namespace Nyra
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void render(const HittableList& world) const;

        void SetBackgroundColor(glm::vec3 backgroundColor);

    private:
        Nyra::Ray GenerateRay(float i, float j) const;
        glm::vec3 GenerateDefocusDiskSample() const;
        glm::vec3 GenerateRandomPixelOffset() const;
        glm::vec3 CalculateRayColor(const Ray& ray, uint32_t depth, const HittableList& world) const;
        void CreatePPMFromBuffer(const std::vector<uint8_t>& buffer, const std::string& filename) const;
        glm::vec3 LinearToGamma(glm::vec3 linearColor) const;

    private:
        // Image
        int m_imageWidth;
        int m_imageHeight;

        // Camera
        glm::vec3 m_center;
        glm::vec3 m_pixelDeltaU;
        glm::vec3 m_pixelDeltaV;
        glm::vec3 m_pixel00Loc;
        glm::vec3 m_defocusDiskU;
        glm::vec3 m_defocusDiskV;
        glm::vec3 m_backgroundColor;
        float m_defocusAngle;
        uint32_t m_maxRayDepth;
        int m_samplesPerPixel;
    };
}
#include <NyraPCH.h>
#include <ImageTexture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace Nyra;

ImageTexture::ImageTexture(const std::filesystem::path& filepath)
    : m_pixelData(), m_imageWidth(0), m_imageHeight(0)
{
    int bytesPerPixel = 3;
    float* pixelDataAsFloats = stbi_loadf(filepath.string().c_str(), &m_imageWidth, &m_imageHeight, &bytesPerPixel, bytesPerPixel);
    if (pixelDataAsFloats == nullptr)
    {
        std::cerr << "Failed to load image: " << filepath << "\n";
        return;
    }

    int totalBytes = m_imageWidth * m_imageHeight * bytesPerPixel;
    m_pixelData.reserve(totalBytes);

    for (int i = 0; i < totalBytes; i++)
    {
        if (pixelDataAsFloats[i] >= 1.0f)
        {
            m_pixelData.push_back(255);
            continue;
        }

        m_pixelData.push_back(static_cast<uint8_t>(pixelDataAsFloats[i] * 256.0f));
    }

    // Cleanup
    STBI_FREE(pixelDataAsFloats);
}

ImageTexture::~ImageTexture()
{
}

glm::vec3 ImageTexture::GetColor(float u, float v, glm::vec3 point) const
{
    u = std::clamp(u, 0.0f, 1.0f);
    v = 1.0f - std::clamp(v, 0.0f, 1.0f);

    float colorScale = 1.0f / 255.0f;

    int x = int(u * m_imageWidth);
    x = std::clamp(x, 0, m_imageWidth - 1);

    int y = int(v * m_imageHeight);
    y = std::clamp(y, 0, m_imageHeight - 1);

    constexpr int bytesPerPixel = 3;
    int bytesPerScanline = m_imageWidth * bytesPerPixel;
    int pixelIndex = x*bytesPerPixel + y*bytesPerScanline;

    uint8_t pixelX = m_pixelData[pixelIndex];
    uint8_t pixelY = m_pixelData[pixelIndex + 1];
    uint8_t pixelZ = m_pixelData[pixelIndex + 2];

    return glm::vec3(colorScale*pixelX, colorScale*pixelY, colorScale*pixelZ);
}
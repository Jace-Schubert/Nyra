#pragma once

#include <Texture.h>

namespace Nyra
{
    class ImageTexture : public Texture
    {
    public:
        ImageTexture(const std::filesystem::path& filepath);
        ~ImageTexture();

        virtual glm::vec3 GetColor(float u, float v, glm::vec3 point) const override;

    private:
        std::vector<uint8_t> m_pixelData;
        int m_imageWidth;
        int m_imageHeight;
    };
}
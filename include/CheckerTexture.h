#pragma once

#include <Texture.h>

class CheckerTexture : public Texture
{
public:
    CheckerTexture(float scale, std::shared_ptr<Texture> evenTexture, std::shared_ptr<Texture> oddTexture);
    ~CheckerTexture();

    virtual glm::vec3 GetColor(float u, float v, glm::vec3 point) const override;

private:
    float m_inverseScale;
    std::shared_ptr<Texture> m_evenTexture;
    std::shared_ptr<Texture> m_oddTexture;
};
#pragma once

#include <NyraPCH.h>

namespace Nyra
{
    class Ray
    {
    public:
        Ray(glm::vec3 origin, glm::vec3 direction, float time);
        Ray(glm::vec3 origin, glm::vec3 direction);

        glm::vec3 At(float t) const;

        glm::vec3 GetOrigin() const;
        void SetOrigin(glm::vec3 origin);

        glm::vec3 GetDirection() const;
        void SetDirection(glm::vec3 direction);
        
        float GetTime() const;
        void SetTime(float time);

    private:
        glm::vec3 m_origin;
        glm::vec3 m_dir;
        float m_time;
    };
}
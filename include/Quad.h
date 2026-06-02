#pragma once

#include <NyraPCH.h>
#include <Material.h>

namespace Nyra
{
    class Quad : public Hittable
    {
    public:
        Quad(glm::vec3 Q, glm::vec3 u, glm::vec3 v, std::shared_ptr<Material> material);
        ~Quad();

        virtual std::optional<HitRecord> Hit(const Ray& ray, Interval interval) const override;

        virtual AABB GetBoundingBox() const override;

    private:
        AABB m_boundingBox;
        glm::vec3 m_Q; // A corner point of the quad
        glm::vec3 m_u; // Edge vector 1 (from Q to adjacent corner)
        glm::vec3 m_v; // Edge vector 2 (from Q to adjacent corner)
        glm::vec3 m_w;
        glm::vec3 m_normal; // Normal vector of the quad's plane
        std::shared_ptr<Material> m_material;
        float m_D;
    };
}
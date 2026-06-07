#pragma once

#include <HittableList.h>
#include <Material.h>

namespace Nyra
{
    class Box : public HittableList
    {
    public:
        Box(glm::vec3 p0, glm::vec3 p1, std::shared_ptr<Material> material);
        ~Box();
    };
}
#include <NyraPCH.h>
#include <Box.h>

#include <Quad.h>

using namespace Nyra;

Box::Box(glm::vec3 point0, glm::vec3 point1, std::shared_ptr<Material> material)
{
    glm::vec3 temp = point0;
    point0 = glm::min(point0, point1);
    point1 = glm::max(temp, point1);

    Add(std::make_shared<Quad>(glm::vec3(point0.x, point0.y, point0.z), glm::vec3(point1.x - point0.x, 0, 0), glm::vec3(0, point1.y - point0.y, 0), material)); // Front face
    Add(std::make_shared<Quad>(glm::vec3(point1.x, point0.y, point1.z), glm::vec3(-point1.x + point0.x, 0, 0), glm::vec3(0, point1.y - point0.y, 0), material)); // Back face
    Add(std::make_shared<Quad>(glm::vec3(point1.x, point0.y, point0.z), glm::vec3(0, 0, point1.z - point0.z), glm::vec3(0, point1.y - point0.y, 0), material)); // Right face
    Add(std::make_shared<Quad>(glm::vec3(point0.x, point0.y, point1.z), glm::vec3(0, 0, -point1.z + point0.z), glm::vec3(0, point1.y - point0.y, 0), material)); // Left face
    Add(std::make_shared<Quad>(glm::vec3(point0.x, point1.y, point1.z), glm::vec3(point1.x - point0.x, 0, 0), glm::vec3(0, 0, -point1.z + point0.z), material)); // Top face
    Add(std::make_shared<Quad>(glm::vec3(point0.x, point0.y, point1.z), glm::vec3(point1.x - point0.x, 0, 0), glm::vec3(0, 0, -point1.z + point0.z), material)); // Bottom face
}

Box::~Box()
{
}
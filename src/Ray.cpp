#include <NyraPCH.h>
#include <Ray.h>

using namespace Nyra;

Ray::Ray(glm::vec3 origin, glm::vec3 direction, float time)
    : m_origin(origin), m_dir(direction), m_time(time)
{
}

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
    : m_origin(origin), m_dir(direction), m_time(0)
{
}

glm::vec3 Ray::At(float t) const
{
    return m_origin + (t * m_dir);
}

// Getters & Setters
glm::vec3 Ray::GetOrigin() const
{
    return m_origin;
}
void Ray::SetOrigin(glm::vec3 origin)
{
    m_origin = origin;
}

glm::vec3 Ray::GetDirection() const
{
    return m_dir;
}
void Ray::SetDirection(glm::vec3 direction)
{
    m_dir = direction;
}

float Ray::GetTime() const
{
    return m_time;
}
void Ray::SetTime(float time)
{    
    m_time = time;
}
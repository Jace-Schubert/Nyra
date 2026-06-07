#include <NyraPCH.h>
#include <ConstantMedium.h>

#include <Isotropic.h>
#include <Random.h>

using namespace Nyra;

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, float density, std::shared_ptr<Texture> texture)
    : m_boundary(std::move(boundary)), m_phaseFunction(std::make_shared<Isotropic>(texture)), m_negativeInverseDensity(-1 / density)
{
}

ConstantMedium::~ConstantMedium()
{
}

std::optional<HitRecord> ConstantMedium::Hit(const Ray& ray, Interval interval) const
{
    constexpr float infinity = std::numeric_limits<float>::max();
    Interval universe(-infinity, infinity);

    std::optional hitRecord = m_boundary->Hit(ray, universe);
    if (!hitRecord.has_value())
    {
        return std::nullopt;
    }

    std::optional hitRecord2 = m_boundary->Hit(ray, Interval(hitRecord.value().t + 0.0001f, infinity));
    if (!hitRecord2.has_value())
    {
        return std::nullopt;
    }

    HitRecord hr1 = hitRecord.value();
    HitRecord hr2 = hitRecord2.value();

    if (hr1.t < interval.GetMin())
    {
        hr1.t = interval.GetMin();
    }

    if (hr2.t > interval.GetMax())
    {
        hr2.t = interval.GetMax();
    }

    if (hr1.t >= hr2.t)
    {
        return std::nullopt;
    }

    if (hr1.t < 0)
    {
        hr1.t = 0;
    }

    float rayLength = ray.GetDirection().length();
    float distanceInsideBoundary = (hr2.t - hr1.t) * rayLength;
    float hitDistance = m_negativeInverseDensity * std::log(Random::GenerateFloat(0.0001f, 1.0f));

    if (hitDistance > distanceInsideBoundary)
    {
        return std::nullopt;
    }

    HitRecord result;
    result.t = hr1.t + (hitDistance / rayLength);
    result.hitPoint = ray.At(result.t);
    result.surfaceNormal = glm::vec3(1.0f, 0.0f, 0.0f);
    result.frontFace = true;
    result.material = m_phaseFunction;

    return result;
}

AABB ConstantMedium::GetBoundingBox() const
{
    return m_boundary->GetBoundingBox();
}
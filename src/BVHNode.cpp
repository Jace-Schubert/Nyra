#include <NyraPCH.h>
#include <BVHNode.h>

#include <Random.h>

using namespace Nyra;

BVHNode::BVHNode(HittableList hittables)
    : BVHNode(hittables.GetObjects(), 0, hittables.GetObjects().size())
{
}

BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& hittables, size_t start, size_t end)
    : m_left(nullptr), m_right(nullptr), m_boundingBox(hittables[start]->GetBoundingBox())
{
    // Initialize bounding box for this node to encompass all hittables in the range
    for (size_t i = start + 1; i < end; i++)
    {
        m_boundingBox = AABB(m_boundingBox, hittables[i]->GetBoundingBox());
    }

    // Use longest axis for best division of space
    int axis = m_boundingBox.ComputeLongestAxis();

    // Lambda for comparing two hittables based on their bounding box's minimum value along the selected axis
    auto comparator = [axis](const std::shared_ptr<Hittable> lhs, const std::shared_ptr<Hittable> rhs)
    {
        return lhs->GetBoundingBox()[axis].GetMin() < rhs->GetBoundingBox()[axis].GetMin();
    };
    std::sort(hittables.begin() + start, hittables.begin() + end, comparator);

    size_t range = end - start;
    if (range == 1)
    {
        m_left = m_right = hittables[start];
    }
    else if (range == 2)
    {
        m_left = hittables[start];
        m_right = hittables[start + 1];
    }
    else
    {
        size_t middle = start + (range / 2);
        m_left = std::make_shared<BVHNode>(hittables, start, middle);
        m_right = std::make_shared<BVHNode>(hittables, middle, end);
    }
}

BVHNode::~BVHNode()
{
}

std::optional<HitRecord> BVHNode::Hit(const Ray& ray, Interval interval) const
{
    if (!m_boundingBox.Hit(ray, interval))
    {
        return std::nullopt;
    }

    std::optional<HitRecord> leftHit = m_left->Hit(ray, interval);
    std::optional<HitRecord> rightHit = m_right->Hit(ray, leftHit.has_value() ? Interval(interval.GetMin(), leftHit.value().t) : interval);

    if (rightHit.has_value())
    {
        return rightHit;
    }

    return leftHit;
}

AABB BVHNode::GetBoundingBox() const
{
    return m_boundingBox;
}
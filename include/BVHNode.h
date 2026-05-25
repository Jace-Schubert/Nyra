#include <Hittable.h>
#include <HittableList.h>

namespace Nyra
{
    class BVHNode : public Hittable
    {
    public:
        BVHNode(HittableList hittables);
        BVHNode(std::vector<std::shared_ptr<Hittable>>& hittables, size_t start, size_t end);
        ~BVHNode();

        // Hittable overrides
        std::optional<HitRecord> Hit(const Nyra::Ray& ray, Interval interval) const override;
        AABB GetBoundingBox() const override;

    private:
        std::shared_ptr<Hittable> m_left;
        std::shared_ptr<Hittable> m_right;
        AABB m_boundingBox;
    };
}
#include <Camera.h>

Camera::Camera()
{
    // Image
    constexpr double aspectRatio = 16.0 / 9.0;
    m_imageWidth = 400;
    m_imageHeight = int(m_imageWidth / aspectRatio);

    // Camera
    constexpr double focalLength = 1.0;
    constexpr double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * ((double)m_imageWidth / m_imageHeight); 
    m_center = raymath::point3(0, 0, 0);

    raymath::vec3 viewportU = raymath::vec3(viewportWidth, 0, 0);
    raymath::vec3 viewportV = raymath::vec3(0, -viewportHeight, 0);

    m_pixelDeltaU = viewportU / m_imageWidth;
    m_pixelDeltaV = viewportV / m_imageHeight;

    raymath::vec3 viewportUpperLeft = m_center - raymath::vec3(0, 0, focalLength) - (viewportU/2) - (viewportV/2);
    m_pixel00Loc = viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);
}

Camera::~Camera()
{
}

void Camera::render(const Nyra::HittableList& world) const
{
    std::cout << "P3\n" 
        << m_imageWidth << " " << m_imageHeight << "\n" 
        << "255\n";

    for (int j = 0; j < m_imageHeight; j++)
    {
        for (int i = 0; i < m_imageWidth; i++)
        {
            raymath::point3 pixelLoc = m_pixel00Loc + (i * m_pixelDeltaU) + (j * m_pixelDeltaV);
            Nyra::Ray ray(m_center, pixelLoc - m_center);
            raymath::color pixelColor = CalculateRayColor(ray, world);
            WriteColor(pixelColor);
        }
    }

    std::clog << "\rRender complete\n";
}

// Private Utils
raymath::color Camera::CalculateRayColor(const Nyra::Ray& ray, const Nyra::HittableList& world) const
{
    std::optional<Nyra::HitRecord> hitRecord = world.Hit(ray, Interval(0, std::numeric_limits<double>::infinity()));
    if (hitRecord.has_value())
    {
        const Nyra::HitRecord& record = hitRecord.value();
        return 0.5 * raymath::color(record.surfaceNormal.x + 1, record.surfaceNormal.y + 1, record.surfaceNormal.z + 1);
    }

    raymath::vec3 unitDir = raymath::unitize(ray.GetDirection());
    double t = 0.5 * (unitDir.y + 1.0);
    return ((1.0 - t) * raymath::color(1.0, 1.0, 1.0)) + (t * raymath::color(0.5, 0.7, 1.0));
}

// Color is expected to be sent in range [0, 1]
void Camera::WriteColor(const raymath::color& pixelColor) const
{
    int rByte = int(pixelColor.r * 255.999);
    int gByte = int(pixelColor.g * 255.999);
    int bByte = int(pixelColor.b * 255.999);

    std::cout << rByte << " " << gByte << " " << bByte << "\n";
}
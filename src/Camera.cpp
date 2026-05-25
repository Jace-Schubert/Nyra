#include <Camera.h>
#include <Random.h>
#include <Material.h>
#include <Math.h>

#include <chrono>
#include <fstream>

using namespace Nyra;

Camera::Camera()
{
    m_samplesPerPixel = 80;
    m_maxRayDepth = 10;

    // Image
    constexpr double aspectRatio = 16.0 / 9.0;
    m_imageWidth = 400;
    m_imageHeight = int(m_imageWidth / aspectRatio);

    // Camera
    raymath::vec3 lookFrom = raymath::point3(13, 2, 3);
    raymath::vec3 lookAt = raymath::point3(0, 0, 0);
    raymath::vec3 vup = raymath::vec3(0, 1, 0);

    m_defocusAngle = 0.6;
    double focusDistance = 10;

    constexpr double vfov = 20.0;
    double viewportHeight = 2.0 * std::tan(Nyra::Math::radians(vfov) / 2) * focusDistance;
    double viewportWidth = viewportHeight * ((double)m_imageWidth / m_imageHeight); 
    m_center = lookFrom;

    // Unit basis vectors for camera space (u, v, w) where w is forward, u is right, and v is up
    raymath::vec3 w = raymath::unitize(lookFrom - lookAt);
    raymath::vec3 u = raymath::unitize(raymath::cross(vup, w));
    raymath::vec3 v = raymath::cross(w, u);

    raymath::vec3 viewportU = viewportWidth * u;
    raymath::vec3 viewportV = viewportHeight * -v;

    m_pixelDeltaU = viewportU / m_imageWidth;
    m_pixelDeltaV = viewportV / m_imageHeight;

    raymath::vec3 viewportUpperLeft = m_center - (focusDistance * w) - (viewportU/2) - (viewportV/2);
    m_pixel00Loc = viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);

    double defocusRadius = focusDistance * std::tan(Nyra::Math::radians(m_defocusAngle / 2));
    m_defocusDiskU = defocusRadius * u;
    m_defocusDiskV = defocusRadius * v;
}

Camera::~Camera()
{
}

void Camera::render(const Nyra::HittableList& world) const
{
    // Start timer
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    // Create a buffer to hold pixel colors as bytes in range [0, 255] for PPM output
    std::vector<uint8_t> pixelColorBuffer(m_imageWidth * m_imageHeight * 3);
    int bufferIndex = 0;

    // Begin render
    for (int j = 0; j < m_imageHeight; j++)
    {
        // Output render progress
        std::clog << "\rRendering: " << int(100.0f * j / m_imageHeight)<< "%" << std::flush;

        for (int i = 0; i < m_imageWidth; i++)
        {
            raymath::color pixelColor(0, 0, 0);
            for (int s = 0; s < m_samplesPerPixel; s++)
            {
                Nyra::Ray ray = GenerateRay(i, j);
                pixelColor += CalculateRayColor(ray, m_maxRayDepth, world);
            }

            pixelColor /= static_cast<float>(m_samplesPerPixel);
            raymath::color gammaColor = LinearToGamma(pixelColor);

            // Convert color to bytes in range [0, 255] and write to buffer
            pixelColorBuffer[bufferIndex++] = static_cast<uint8_t>(gammaColor.r * 255.999);
            pixelColorBuffer[bufferIndex++] = static_cast<uint8_t>(gammaColor.g * 255.999);
            pixelColorBuffer[bufferIndex++] = static_cast<uint8_t>(gammaColor.b * 255.999);
        }
    }

    // Output render time
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds renderTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::chrono::minutes renderTimeMinutes = std::chrono::duration_cast<std::chrono::minutes>(renderTime);
    std::chrono::seconds renderTimeSeconds = std::chrono::duration_cast<std::chrono::seconds>(renderTime - renderTimeMinutes);
    std::clog << "\rRender complete in " << renderTimeMinutes.count() << " min " << renderTimeSeconds.count() << " sec\n";

    // Write buffer to PPM file
    std::clog << "Writing output to render.ppm...\n";
    CreatePPMFromBuffer(pixelColorBuffer, "render.ppm");
    std::clog << "Done!\n";
}


//===============//
// Private Utils //
//===============//
Ray Camera::GenerateRay(double i, double j) const
{
    raymath::point3 offset = GenerateRandomPixelOffset();
    raymath::point3 pixelLoc = m_pixel00Loc + ((i + offset.x) * m_pixelDeltaU) + ((j + offset.y) * m_pixelDeltaV);

    raymath::point3 rayOrigin = (m_defocusAngle <= 0) ? m_center : GenerateDefocusDiskSample();
    return Ray(rayOrigin, pixelLoc - rayOrigin, Random::GenerateDouble(0, 1));
}

// Returns a random point on the camera's defocus disk
raymath::point3 Camera::GenerateDefocusDiskSample() const
{
    raymath::vec3 diskSample = Random::GenerateVectorInUnitDisk();
    return m_center + (diskSample.x * m_defocusDiskU) + (diskSample.y * m_defocusDiskV);
}

// Generates a random offset in the range [-0.5, 0.5] for 2D pixel
raymath::point3 Camera::GenerateRandomPixelOffset() const
{
    return raymath::point3(Random::GenerateDouble(-0.5, 0.5), Random::GenerateDouble(-0.5, 0.5), 0);
}

raymath::color Camera::CalculateRayColor(const Nyra::Ray& ray, uint32_t depth, const Nyra::HittableList& world) const
{
    // Base case for ray bounce recursion - if we've exceeded the ray bounce limit, no more light is gathered
    if (depth == 0)
    {
        return raymath::color(0, 0, 0);
    }

    std::optional<Nyra::HitRecord> hitRecord = world.Hit(ray, Interval(0.001, std::numeric_limits<double>::infinity()));
    if (hitRecord.has_value())
    {
        const Nyra::HitRecord& record = hitRecord.value();

        // Reflect ray in random direction from hit point so we can send it out later to see what it hits next (i.e. bounce ray around the scene).
        auto [attenuation, reflectedRay] = record.material->Scatter(ray, record);

        if (!reflectedRay.has_value())
        {
            // Ray was absorbed
            return raymath::color(0, 0, 0);
        }

        return attenuation * CalculateRayColor(reflectedRay.value(), depth - 1, world);
    }

    // Handle ray didnt hit anything - render background gradient
    raymath::vec3 unitDir = raymath::unitize(ray.GetDirection());
    double t = 0.5 * (unitDir.y + 1.0);
    return ((1.0 - t) * raymath::color(1.0, 1.0, 1.0)) + (t * raymath::color(0.5, 0.7, 1.0));
}

void Camera::CreatePPMFromBuffer(const std::vector<uint8_t>& buffer, const std::string& filename) const
{   
    std::ofstream file(filename, std::ios::binary);
    file << "P6\n" 
        << m_imageWidth << " " << m_imageHeight << "\n" 
        << "255\n";

    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

raymath::color Camera::LinearToGamma(const raymath::color& linearColor) const
{
    return raymath::color(std::sqrt(linearColor.r), std::sqrt(linearColor.g), std::sqrt(linearColor.b));
}
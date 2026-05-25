#include <BVHNode.h>
#include <Camera.h>
#include <vec3.h>
#include <Sphere.h>
#include <HittableList.h>
#include <Lambertian.h>
#include <Metal.h>
#include <Dielectric.h>
#include <Random.h>

using namespace Nyra;

int main(int argc, char *argv[])
{
    HittableList world;
    
    // Ground
    std::shared_ptr<Lambertian> groundMaterial = std::make_shared<Lambertian>(raymath::color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(raymath::point3(0, -1000, 0), 1000, groundMaterial));

    // Random spheres
    for (int i = 0; i < 150; i++)
    {
        raymath::point3 centerAtStart = raymath::point3(Random::GenerateDouble(-10, 10), 0.2, Random::GenerateDouble(-10, 10));
        if ((centerAtStart - raymath::point3(4, 0.2, 0)).length() > 0.9)
        {
            std::shared_ptr<Material> material;
            double materialChoice = Random::GenerateDouble(0, 1);
            if (materialChoice < 0.8)
            {
                // Diffuse
                material = std::make_shared<Lambertian>(Random::GenerateVector3(0, 1));
            }
            else if (materialChoice < 0.95)
            {
                // Metal
                material = std::make_shared<Metal>(Random::GenerateVector3(0.5, 1), Random::GenerateDouble(0, 0.5));
            }
            else
            {
                // Glass
                material = std::make_shared<Dielectric>(1.5);
            }

            raymath::point3 centerAtEnd = centerAtStart + raymath::vec3(0, Random::GenerateDouble(0, 0.5), 0);
            world.Add(std::make_shared<Sphere>(centerAtStart, centerAtEnd, 0.2, material));
        }
    }

    std::shared_ptr<Dielectric> glassMaterial = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(raymath::point3(0, 1, 0), 1.0, glassMaterial));

    std::shared_ptr<Lambertian> diffuseMaterial = std::make_shared<Lambertian>(raymath::color(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(raymath::point3(-4, 1, 0), 1.0, diffuseMaterial));

    std::shared_ptr<Metal> metalMaterial = std::make_shared<Metal>(raymath::color(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(raymath::point3(4, 1, 0), 1.0, metalMaterial));

    // Build BVH for world
    world = HittableList(std::make_shared<BVHNode>(world));

    // Render
    Camera cam;
    cam.render(world);
}
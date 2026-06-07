#include <NyraPCH.h>

#include <Box.h>
#include <BVHNode.h>
#include <Camera.h>
#include <Sphere.h>
#include <HittableList.h>
#include <Lambertian.h>
#include <Metal.h>
#include <Dielectric.h>
#include <Random.h>
#include <CheckerTexture.h>
#include <SolidColor.h>
#include <ImageTexture.h>
#include <NoiseTexture.h>
#include <Quad.h>
#include <DiffuseLight.h>
#include <Translate.h>
#include <RotateY.h>
#include <ConstantMedium.h>

using namespace Nyra;

void RenderSpheresScene()
{
    HittableList world;
    
    // Ground
    glm::vec3 green(0.0f, 1.0f, 0.0f);
    glm::vec3 blue(0.0f, 0.0f, 1.0f);
    std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32f, std::make_shared<SolidColor>(green), std::make_shared<SolidColor>(blue));
    std::shared_ptr<Lambertian> groundMaterial = std::make_shared<Lambertian>(checkerTexture);
    world.Add(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, groundMaterial));

    // Random spheres
    for (int i = 0; i < 100; i++)
    {
        glm::vec3 centerAtStart = glm::vec3(Random::GenerateFloat(-10, 10), 0.2, Random::GenerateFloat(-10, 10));
        if ((centerAtStart - glm::vec3(4, 0.2, 0)).length() > 0.9)
        {
            std::shared_ptr<Material> material;
            float materialChoice = Random::GenerateFloat(0, 1);
            if (materialChoice < 0.8)
            {
                // Diffuse
                material = std::make_shared<Lambertian>(Random::GenerateVec3(0, 1));
            }
            else if (materialChoice < 0.95)
            {
                // Metal
                material = std::make_shared<Metal>(Random::GenerateVec3(0.5, 1), Random::GenerateFloat(0, 0.5));
            }
            else
            {
                // Glass
                material = std::make_shared<Dielectric>(1.5);
            }

            glm::vec3 centerAtEnd = centerAtStart + glm::vec3(0, Random::GenerateFloat(0, 0.5), 0);
            world.Add(std::make_shared<Sphere>(centerAtStart, centerAtEnd, 0.2, material));
        }
    }

    std::shared_ptr<Dielectric> glassMaterial = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, glassMaterial));

    std::shared_ptr<ImageTexture> earthTexture = std::make_shared<ImageTexture>("assets/textures/earth.jpg");
    std::shared_ptr<Lambertian> earthMaterial = std::make_shared<Lambertian>(earthTexture);
    //std::shared_ptr<Lambertian> diffuseMaterial = std::make_shared<Lambertian>(glm::vec3(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, earthMaterial));

    std::shared_ptr<Metal> metalMaterial = std::make_shared<Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, metalMaterial));

    // Build BVH for world
    world = HittableList(std::make_shared<BVHNode>(world));

    // Render
    Camera cam;
    cam.render(world);
}

void RenderEarthScene()
{
    HittableList world;
    
    // Earth
    std::shared_ptr<ImageTexture> earthTexture = std::make_shared<ImageTexture>("assets/textures/earth.jpg");
    std::shared_ptr<Lambertian> earthMaterial = std::make_shared<Lambertian>(earthTexture);
    world.Add(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1.5f, earthMaterial));

    // Build BVH for world
    world = HittableList(std::make_shared<BVHNode>(world));

    // Render
    Camera cam;
    cam.render(world);
}

void RenderPerlinScene()
{
    HittableList world;
    
    // Ground
    std::shared_ptr<NoiseTexture> noiseTexture = std::make_shared<NoiseTexture>(4.0f);
    std::shared_ptr<Lambertian> noiseMaterial = std::make_shared<Lambertian>(noiseTexture);
    world.Add(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, noiseMaterial));

    // Light
    std::shared_ptr<SolidColor> lightColor = std::make_shared<SolidColor>(glm::vec3(4, 4, 4));
    std::shared_ptr<DiffuseLight> lightMaterial = std::make_shared<DiffuseLight>(lightColor);
    world.Add(std::make_shared<Quad>(glm::vec3(3, 1, -2), glm::vec3(2, 0, 0), glm::vec3(0, 2, 0), lightMaterial));

    // Sphere
    world.Add(std::make_shared<Sphere>(glm::vec3(0, 2, 0), 2.0, noiseMaterial));

    // Build BVH for world
    world = HittableList(std::make_shared<BVHNode>(world));

    // Render
    Camera cam;
    cam.SetBackgroundColor(glm::vec3(0, 0, 0)); // Override default background color to pure black since we have a light in the scene and want to see the contrast
    cam.render(world);
}

void RenderQuadsScene()
{
    HittableList world;

    std::shared_ptr<Lambertian> redMaterial = std::make_shared<Lambertian>(glm::vec3(1, 0, 0));
    std::shared_ptr<Lambertian> greenMaterial = std::make_shared<Lambertian>(glm::vec3(0, 1, 0));
    std::shared_ptr<Lambertian> blueMaterial = std::make_shared<Lambertian>(glm::vec3(0, 0, 1));
    std::shared_ptr<Lambertian> orangeMaterial = std::make_shared<Lambertian>(glm::vec3(1, 0.5, 0));
    std::shared_ptr<Lambertian> tealMaterial = std::make_shared<Lambertian>(glm::vec3(0, 1, 1));

    world.Add(std::make_shared<Quad>(glm::vec3(-3, -2, 5), glm::vec3(0, 0, -4), glm::vec3(0, 4, 0), redMaterial));
    world.Add(std::make_shared<Quad>(glm::vec3(-2, -2, 0), glm::vec3(4, 0, 0), glm::vec3(0, 4, 0), greenMaterial));
    world.Add(std::make_shared<Quad>(glm::vec3(3, -2, 1), glm::vec3(0, 0, 4), glm::vec3(0, 4, 0), blueMaterial));
    world.Add(std::make_shared<Quad>(glm::vec3(-2, 3, 1), glm::vec3(4, 0, 0), glm::vec3(0, 0, 4), orangeMaterial));
    world.Add(std::make_shared<Quad>(glm::vec3(-2, -3, 5), glm::vec3(4, 0, 0), glm::vec3(0, 0, -4), tealMaterial));

    // Build BVH for world
    world = HittableList(std::make_shared<BVHNode>(world));

    // Render
    Camera cam;
    cam.render(world);
}

void RenderCornellBoxScene()
{
    std::shared_ptr<Lambertian> redMaterial = std::make_shared<Lambertian>(glm::vec3(0.65f, 0.05f, 0.05f));
    std::shared_ptr<Lambertian> whiteMaterial = std::make_shared<Lambertian>(glm::vec3(0.73f, 0.73f, 0.73f));
    std::shared_ptr<Lambertian> greenMaterial = std::make_shared<Lambertian>(glm::vec3(0.12f, 0.45f, 0.15f));

    // Light
    std::shared_ptr<SolidColor> lightColor = std::make_shared<SolidColor>(glm::vec3(15, 15, 15));
    std::shared_ptr<DiffuseLight> lightMaterial = std::make_shared<DiffuseLight>(lightColor);

    HittableList world;

    world.Add(std::make_shared<Quad>(glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 555), greenMaterial)); // Left wall
    world.Add(std::make_shared<Quad>(glm::vec3(0, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 555), redMaterial)); // Right wall
    world.Add(std::make_shared<Quad>(glm::vec3(0, 0, 555), glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), whiteMaterial)); // Back wall
    world.Add(std::make_shared<Quad>(glm::vec3(0, 0, 0), glm::vec3(555, 0, 0), glm::vec3(0, 0, 555), whiteMaterial)); // Floor
    world.Add(std::make_shared<Quad>(glm::vec3(555, 555, 555), glm::vec3(-555, 0, 0), glm::vec3(0, 0, -555), whiteMaterial)); // Ceiling
    world.Add(std::make_shared<Quad>(glm::vec3(113, 554, 127), glm::vec3(330, 0, 0), glm::vec3(0, 0, 305), lightMaterial)); // Light

    // Texture colors for fog
    std::shared_ptr<SolidColor> black = std::make_shared<SolidColor>(glm::vec3(0.0f, 0.0f, 0.0f));
    std::shared_ptr<SolidColor> white = std::make_shared<SolidColor>(glm::vec3(1.0f, 1.0f, 1.0f));

    // Boxes
    std::shared_ptr<Hittable> leftBox = std::make_shared<Box>(glm::vec3(0, 0, 0), glm::vec3(165, 330, 165), whiteMaterial);
    leftBox = std::make_shared<RotateY>(leftBox, 15.0f);
    leftBox = std::make_shared<Translate>(leftBox, glm::vec3(265, 0, 295));
    //leftBox = std::make_shared<ConstantMedium>(leftBox, 0.01f, black);

    std::shared_ptr<Hittable> rightBox = std::make_shared<Box>(glm::vec3(0, 0, 0), glm::vec3(165, 165, 165), whiteMaterial);
    rightBox = std::make_shared<RotateY>(rightBox, -18.0f);
    rightBox = std::make_shared<Translate>(rightBox, glm::vec3(130, 0, 65));
    //rightBox = std::make_shared<ConstantMedium>(rightBox, 0.01f, white);

    world.Add(leftBox);
    world.Add(rightBox);

    // Build BVH for world
    world = HittableList(std::make_shared<BVHNode>(world));

    // Render
    Camera cam;
    cam.SetBackgroundColor(glm::vec3(0, 0, 0)); // Override default background color to pure black since we have a light in the scene and want to see the contrast
    cam.render(world);
}

int main(int argc, char *argv[])
{
    switch(5)
    {
        case 1:
            RenderSpheresScene();
            break;
        case 2:
            RenderEarthScene();
            break;
        case 3:
            RenderPerlinScene();
            break;
        case 4:
            RenderQuadsScene();
            break;
        case 5:
            RenderCornellBoxScene();
            break;
        default:
            break;
    }
}
#include <vec3.h>
#include <Sphere.h>
#include <HittableList.h>
#include <Camera.h>

int main(int argc, char *argv[])
{
    Nyra::HittableList world;
    world.PushBack(std::make_shared<Nyra::Sphere>(raymath::point3(0, 0, -1), 0.5));
    world.PushBack(std::make_shared<Nyra::Sphere>(raymath::point3(0, -100.5, -1), 100));

    Camera cam;
    cam.render(world);
}
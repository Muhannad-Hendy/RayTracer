#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Sphere.h"
#include "Light.h"


class World
{
public:
    World();

    bool isEmpty() const;

    bool isDark() const;

    int getNumberOfLights() const;

    Light getLight(int i) const;

    int getNumberOfSpheres() const;

    Sphere getSphere(int i) const;

private:
    std::vector<Sphere> spheres{};
    std::vector<Light> lights{};
};

#endif // WORLD_H

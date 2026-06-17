#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Shape.h"
#include "Light.h"
#include "IntersectionTracker.h"


class World
{
public:
    World();

    World(std::unique_ptr<Shape> shape, Light light);

    bool isEmpty() const;

    bool isDark() const;

    int getNumberOfLights() const;

    Light getLight(int i) const;

    void addLight(Light light);

    int getNumberOfShapes() const;

    Shape& getShape(int i);

    void addShape(std::unique_ptr<Shape> shape);

    Color shadeHit(Intersection& intersection);

    Ray generateShadowRay(const Tuple& objectPoint) const;

    bool isShadowed(Ray& ray);

    void intersect(Ray& ray, IntersectionTracker& tracker);

    Color colorAt(Ray& ray);

private:
    std::vector<std::unique_ptr<Shape>> shapes;
    std::vector<Light> lights{};
};

#endif // WORLD_H

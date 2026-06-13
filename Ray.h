#ifndef RAY_H
#define RAY_H
#include <cmath>
#include <vector>
#include "IntersectionTracker.h"
#include "Tuple.h"
#include "World.h"

class Sphere;

class Ray
{
public:
    Ray();

    Ray(Tuple& origin, Tuple& direction);

    Ray(World& world, Tuple& point);

    Tuple getOrigin() const;

    Tuple getDirection() const;

    void initialize(Tuple& origin, Tuple& direction);

    Ray& operator= (const Ray& original);

    Tuple locate(double time);

    int getNumberOfIntersections() const;

    double getIntersectionTime(int index);

    Sphere& getIntersectedObject(int index);

    std::vector<double> calculateIntersectionParameters(Sphere& sphere);

    void intersect(Sphere& sphere);

    void intersect(World& world);

    bool hitFound();

    IntersectionTracker getIntersectionTracker() const;

    void prepComputations();

    Color colorAt(World& world);

    bool isShadowed(World& world);

private:
    Tuple origin{};
    Tuple direction{};
    IntersectionTracker intersections{};
    double distance{0};
};
#endif // RAY_H

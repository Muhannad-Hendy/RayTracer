#ifndef RAY_H
#define RAY_H
#include <cmath>
#include <vector>
#include "IntersectionTracker.h"
#include "Tuple.h"

class Sphere;

class Ray
{
public:
    Ray();

    Ray(Tuple& origin, Tuple& direction);

    Tuple getOrigin() const;

    Tuple getDirection() const;

    void initialize(Tuple& origin, Tuple& direction);

    Ray& operator= (const Ray& original);

    Tuple locate(double time);

    int getNumberOfIntersections() const;

    double getIntersectionTime(int index) const;

    Sphere& getIntersectedObject(int index) const;

    std::vector<double> calculateIntersectionParameters(Sphere& sphere);

    void intersect(Sphere& sphere);

    bool hitFound();

private:
    Tuple origin{};
    Tuple direction{};
    IntersectionTracker intersections{};
};
#endif // RAY_H

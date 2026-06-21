#ifndef RAY_H
#define RAY_H
#include <cmath>
#include <vector>
#include "Tuple.h"

class Ray
{
public:
    Ray();

    Ray(const Tuple& origin, const Tuple& direction);

    Tuple getOrigin() const;

    Tuple getDirection() const;

    void initialize(Tuple& origin, Tuple& direction);

    Ray& operator= (const Ray& original);

    Tuple locate(double time) const;

    void setDistance(double distance);

    double getDistance() const;

private:
    Tuple origin{};
    Tuple direction{};
    double distance{0};
};
#endif // RAY_H

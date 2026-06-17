#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "Shape.h"

class Sphere : public Shape
{
public:
    Sphere();

    Tuple getCenter() const;

protected:
    Tuple localNormalAt(const Tuple &localPoint) const override;
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;

private:
    static int spheresCounter;
    int ID{};
    double radius{};
    Tuple center{};
    std::vector<double> calculateIntersectionParameters(const Ray &ray) const;
};

#endif // SPHERE_H

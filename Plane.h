#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public:
    Plane();

protected:
    Tuple localNormalAt(const Tuple &localPoint, Intersection *intersection=nullptr) const override;
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
};

#endif // PLANE_H

#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape
{
public:
    using Shape::Shape;

protected:
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
    Tuple localNormalAt(const Tuple &localPoint) const override;

private:
    std::vector<double> checkAxis(double originComponent, double directionComponent);
};

#endif // CUBE_H

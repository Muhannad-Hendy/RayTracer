#ifndef TESTSHAPE_H
#define TESTSHAPE_H

#include "Shape.h"

class TestShape : public Shape
{
public:
    TestShape();

protected:
    Tuple localNormalAt(const Tuple &localPoint, Intersection *intersection=nullptr) const override;
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
};

#endif // TESTSHAPE_H

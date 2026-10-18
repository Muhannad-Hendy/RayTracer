#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(const Tuple& point1, const Tuple& point2, const Tuple point3);

    Tuple getVertex(const int index) const;

    Tuple getEdge(const int index) const;

    void setNormal();

    Tuple getNormal() const;

protected:
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
    Tuple localNormalAt(const Tuple &localPoint, Intersection *intersection=nullptr) const override;
    std::vector<Tuple> edges{};
    std::vector<Tuple> vertices{};

private:
    Tuple normal{};
};

#endif // TRIANGLE_H

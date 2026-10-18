#ifndef SMOOTHTRIANGLE_H
#define SMOOTHTRIANGLE_H

#include <triangle.h>

class SmoothTriangle : public Triangle
{
public:
    SmoothTriangle(const Tuple& point1, const Tuple& point2, const Tuple point3,
                   const Tuple &vnormal1, const Tuple &vnormal2, const Tuple &vnormal3);

    Tuple getVertexNormal(const int index) const;

protected:
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
    Tuple localNormalAt(const Tuple &localPoint, Intersection *intersection = nullptr) const override;

private:
    std::vector<Tuple> vertexNormals{};
};

#endif // SMOOTHTRIANGLE_H

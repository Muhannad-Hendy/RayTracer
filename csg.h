#ifndef CSG_H
#define CSG_H
#include "Shape.h"

enum class Operation{
    Union,
    Intersection,
    Difference
};


class CSG : public Shape
{
public:
    CSG(Operation operation, std::unique_ptr<Shape> left, std::unique_ptr<Shape> right);

    Operation getOperation() const;

    Shape* getLeftShape() const;

    Shape* getRightShape() const;

    bool intersectionAllowed(bool leftHit, bool insideLeft, bool insideRight) const;

    void filterIntersections(IntersectionTracker &tracker);

    bool includes(const Shape &shape) const override;

protected:
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
    Tuple localNormalAt(const Tuple &localPoint, Intersection *intersection = nullptr) const override;

private:
    Operation operation;
    std::unique_ptr<Shape> leftShape;
    std::unique_ptr<Shape> rightShape;
};

#endif // CSG_H

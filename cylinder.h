#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"
#include <limits>

class Cylinder : public Shape
{
public:
    using Shape::Shape;

    double getMinimum() const;

    double getMaximum() const;

    void setMinimum(double min);

    void setMaximum(double max);

    void setClosed(bool status);

    bool isClosed() const;

protected:
    void localIntersect(const Ray &localRay, IntersectionTracker &tracker) override;
    Tuple localNormalAt(const Tuple &localPoint) const override;

private:
    double minimum{-std::numeric_limits<double>::infinity()};
    double maximum{std::numeric_limits<double>::infinity()};
    bool closed_ = false;
    bool checkCap(const Ray &ray, const double time);
    void intersectCaps(const Ray& localRay, IntersectionTracker &tracker);
};

#endif // CYLINDER_H

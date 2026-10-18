#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include <limits>

class Cone : public Shape
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
    Tuple localNormalAt(const Tuple &localPoint, Intersection *intersection=nullptr) const override;

private:
    double minimum{-std::numeric_limits<double>::infinity()};
    double maximum{std::numeric_limits<double>::infinity()};
    bool closed_ = false;
    bool checkCap(const Ray &ray, const double time, const double endCapLocation);
    void intersectCaps(const Ray& localRay, IntersectionTracker &tracker);
};

#endif // CONE_H

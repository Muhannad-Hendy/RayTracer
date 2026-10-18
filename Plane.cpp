#include "Plane.h"
#include "Utilities.h"

Plane::Plane() {}

Tuple Plane::localNormalAt(const Tuple &localPoint, Intersection *intersection) const {
    Tuple normal{0,1,0,TupleType::vector};
    return normal;
}

void Plane::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    if (std::abs(localRay.getDirection().getYValue()) > util::EPSILON) {
        double intersectionTime = -localRay.getOrigin().getYValue() / localRay.getDirection().getYValue();
        tracker.addIntersection(intersectionTime, *this);
    }
}

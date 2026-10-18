#include "cylinder.h"
#include <cmath>
#include "Utilities.h"
#include <utility>

void Cylinder::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    double aTerm = std::pow(localRay.getDirection().getXValue(),2) + std::pow(localRay.getDirection().getZValue(),2);
    if (util::equals(aTerm,0)) {
        intersectCaps(localRay, tracker);
        return;
    }
    else {
        double bTerm = 2*localRay.getOrigin().getXValue()*localRay.getDirection().getXValue() +
                        2*localRay.getOrigin().getZValue()*localRay.getDirection().getZValue();
        double cTerm = std::pow(localRay.getOrigin().getXValue(),2) + std::pow(localRay.getOrigin().getZValue(),2) - 1;
        double discriminant = std::pow(bTerm,2) - 4*aTerm*cTerm;
        if (discriminant < 0) return;

        double time0 = (-bTerm - std::sqrt(discriminant)) / (2*aTerm);
        double time1 = (-bTerm + std::sqrt(discriminant)) / (2*aTerm);
        if (time0>time1) std::swap(time0,time1);

        double y0 = localRay.getOrigin().getYValue() + time0 * localRay.getDirection().getYValue();
        if (minimum<y0 && y0<maximum) {
            tracker.addIntersection(time0, *this);
        }

        double y1 = localRay.getOrigin().getYValue() + time1 * localRay.getDirection().getYValue();
        if (minimum<y1 && y1<maximum) {
            tracker.addIntersection(time1, *this);
        }

        intersectCaps(localRay,tracker);
    }
}

Tuple Cylinder::localNormalAt(const Tuple &localPoint, Intersection *intersection) const {
    double distance = std::pow(localPoint.getXValue(),2) + std::pow(localPoint.getZValue(),2);
    if (distance<1 && localPoint.getYValue()>=(maximum-util::EPSILON)) return Tuple{0,1,0,TupleType::vector};
    else if (distance<1 && localPoint.getYValue()<=(minimum+util::EPSILON)) return Tuple{0,-1,0,TupleType::vector};
    else return Tuple{localPoint.getXValue(),0,localPoint.getZValue(),TupleType::vector};
}

double Cylinder::getMinimum() const {
    return minimum;
}

double Cylinder::getMaximum() const {
    return maximum;
}


void Cylinder::setMinimum(double min) {
    minimum = min;
}

void Cylinder::setMaximum(double max) {
    maximum = max;
}

void Cylinder::setClosed(bool status) {
    closed_ = status;
}

bool Cylinder::isClosed() const {
    return closed_;
}

bool Cylinder::checkCap(const Ray &ray, const double time) {
    double xDistance = ray.getOrigin().getXValue() + time * ray.getDirection().getXValue();
    double zDistance = ray.getOrigin().getZValue() + time * ray.getDirection().getZValue();
    bool isInside = (std::pow(xDistance,2) + std::pow(zDistance,2)) <= 1;
    return isInside;
}

void Cylinder::intersectCaps(const Ray &localRay, IntersectionTracker &tracker) {
    if (closed_==false || util::equals(localRay.getDirection().getYValue(),0)) return;

    double time = (minimum - localRay.getOrigin().getYValue()) / localRay.getDirection().getYValue();
    if (checkCap(localRay,time)) tracker.addIntersection(time,*this);

    time = (maximum - localRay.getOrigin().getYValue()) / localRay.getDirection().getYValue();
    if (checkCap(localRay,time)) tracker.addIntersection(time,*this);
}

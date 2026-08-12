#include "cone.h"

void Cone::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    Tuple rayOrigin = localRay.getOrigin();
    Tuple rayDirection = localRay.getDirection();
    double aTerm = std::pow(rayDirection.getXValue(),2) - std::pow(rayDirection.getYValue(),2) + std::pow(rayDirection.getZValue(),2);
    double bTerm = 2*rayOrigin.getXValue()*rayDirection.getXValue() - 2*rayOrigin.getYValue()*rayDirection.getYValue() + 2*rayOrigin.getZValue()*rayDirection.getZValue();
    double cTerm = std::pow(rayOrigin.getXValue(),2) - std::pow(rayOrigin.getYValue(),2) + std::pow(rayOrigin.getZValue(),2);

    if (util::equals(aTerm,0) && !util::equals(bTerm,0)) {
        double time = -cTerm/(2*bTerm);
        tracker.addIntersection(time,*this);
        intersectCaps(localRay,tracker);
        return;
    }
    else if (!util::equals(aTerm,0)) {
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

Tuple Cone::localNormalAt(const Tuple &localPoint) const {
    double distance = std::pow(localPoint.getXValue(),2) + std::pow(localPoint.getZValue(),2);
    double y = std::sqrt(distance);
    if (distance<std::pow(maximum,2) && localPoint.getYValue()>=(maximum-util::EPSILON)) return Tuple{0,1,0,TupleType::vector};
    else if (distance<std::pow(minimum,2) && localPoint.getYValue()<=(minimum+util::EPSILON)) return Tuple{0,-1,0,TupleType::vector};

    if (localPoint.getYValue()>0) y = -y;
    return Tuple{localPoint.getXValue(),y,localPoint.getZValue(),TupleType::vector};

}


double Cone::getMinimum() const {
    return minimum;
}

double Cone::getMaximum() const {
    return maximum;
}


void Cone::setMinimum(double min) {
    minimum = min;
}

void Cone::setMaximum(double max) {
    maximum = max;
}

void Cone::setClosed(bool status) {
    closed_ = status;
}

bool Cone::isClosed() const {
    return closed_;
}

bool Cone::checkCap(const Ray &ray, const double time, const double endCapLocation) {
    double xDistance = ray.getOrigin().getXValue() + time * ray.getDirection().getXValue();
    double zDistance = ray.getOrigin().getZValue() + time * ray.getDirection().getZValue();
    bool isInside = std::sqrt(std::pow(xDistance,2) + std::pow(zDistance,2)) <= std::abs(endCapLocation);
    return isInside;
}

void Cone::intersectCaps(const Ray &localRay, IntersectionTracker &tracker) {
    if (closed_==false || util::equals(localRay.getDirection().getYValue(),0)) return;

    double time = (minimum - localRay.getOrigin().getYValue()) / localRay.getDirection().getYValue();
    if (checkCap(localRay,time,minimum)) tracker.addIntersection(time,*this);

    time = (maximum - localRay.getOrigin().getYValue()) / localRay.getDirection().getYValue();
    if (checkCap(localRay,time,maximum)) tracker.addIntersection(time,*this);
}

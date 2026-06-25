#include "cube.h"
#include <cmath>
#include <algorithm>

void Cube::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    std::vector<double> xValues = checkAxis(localRay.getOrigin().getXValue(),localRay.getDirection().getXValue());
    std::vector<double> yValues = checkAxis(localRay.getOrigin().getYValue(),localRay.getDirection().getYValue());
    std::vector<double> zValues = checkAxis(localRay.getOrigin().getZValue(),localRay.getDirection().getZValue());
    double tMin = std::max({xValues[0],yValues[0],zValues[0]});
    double tMax = std::min({xValues[1],yValues[1],zValues[1]});
    if (tMin>tMax) return;
    tracker.addIntersection(tMin, *this);
    tracker.addIntersection(tMax, *this);
}

std::vector<double> Cube::checkAxis(double originComponent, double directionComponent) {
    double tMinNumerator = -1 - originComponent;
    double tMaxNumerator = 1 - originComponent;
    double tMin{};
    double tMax{};
    if (std::abs(directionComponent) >= util::EPSILON) {
        tMin = tMinNumerator / directionComponent;
        tMax = tMaxNumerator / directionComponent;
    }
    else {
        tMin = tMinNumerator * std::numeric_limits<double>::infinity();
        tMax = tMaxNumerator * std::numeric_limits<double>::infinity();
    }
    if (tMin>tMax) {
        double temp = tMin;
        tMin = tMax;
        tMax = temp;
    }
    return std::vector<double>{tMin,tMax};
}

Tuple Cube::localNormalAt(const Tuple &localPoint) const {
    double xComponent = localPoint.getXValue();
    double yComponent = localPoint.getYValue();
    double zComponent = localPoint.getZValue();
    auto maxComponent = std::max({std::abs(xComponent),std::abs(yComponent),std::abs(zComponent)});
    if (maxComponent==std::abs(xComponent)) return Tuple{xComponent,0,0,TupleType::vector};
    else if (maxComponent==std::abs(yComponent)) return Tuple{0,yComponent,0,TupleType::vector};
    else return Tuple{0,0,zComponent,TupleType::vector};
}

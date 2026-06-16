#include "Intersection.h"
#include "Sphere.h"

Intersection::Intersection(){};

Intersection::Intersection(double time, Shape &shape) : intersectionTime{time}, intersectedShape{&shape}{};

double Intersection::getIntersectionTime() const{
    return intersectionTime;
}

Shape* Intersection::getIntersectedShape(){
    return intersectedShape;
}

bool operator== (const Intersection& intersection1, const Intersection& intersection2){
    if ((intersection1.intersectionTime == intersection2.intersectionTime)
            && (*intersection1.intersectedShape == *intersection2.intersectedShape)) return true;
    else return false;
}

Tuple* Intersection::getIntersectionPoint() {
    return &intersectionPoint;
}

void Intersection::setIntersectionPoint(Tuple point) {
    intersectionPoint= point;
}

Tuple& Intersection::getEyeVector() {
    return eyeVector;
}

void Intersection::setEyeVector(Tuple point) {
    eyeVector = point;
}

Tuple& Intersection::getNormalVector() {
    return normalVector;
}

void Intersection::setNormalVector() {
    normalVector = intersectedShape->normalAt(intersectionPoint);
}

bool Intersection::isInside() const {
    return m_isInside;
}

void Intersection::setInside(bool status) {
    m_isInside = status;
}

void Intersection::invertNormal() {
    normalVector = -normalVector;
}

void Intersection::setOverIntersectionPoint(Tuple point) {
    overIntersectionPoint = point;
}

Tuple& Intersection::getOverIntersectionPoint() {
    return overIntersectionPoint;
}

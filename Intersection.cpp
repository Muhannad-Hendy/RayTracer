#include "Intersection.h"
#include "Sphere.h"

Intersection::Intersection(){};

Intersection::Intersection(double time, Sphere& sphere) : intersectionTime{time}, intersectedSphere{&sphere}{};

double Intersection::getIntersectionTime() const{
    return intersectionTime;
}

Sphere* Intersection::getIntersectedSphere(){
    return intersectedSphere;
}

bool operator== (const Intersection& intersection1, const Intersection& intersection2){
    if ((intersection1.intersectionTime == intersection2.intersectionTime)
            && (*intersection1.intersectedSphere == *intersection2.intersectedSphere)) return true;
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
    normalVector = intersectedSphere->normal(intersectionPoint);
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

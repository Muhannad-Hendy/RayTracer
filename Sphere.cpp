#include "Sphere.h"

int Sphere::spheresCounter=0;

Sphere::Sphere() {
    ID = spheresCounter;
    spheresCounter++;
    radius = 1.0;
    center.initialize(0,0,0,TupleType::point);
}

Tuple Sphere::getCenter() const{
    return center;
}

int Sphere::getSphereID() const{
    return ID;
}

Tuple Sphere::localNormalAt(const Tuple &localPoint) const {
    Tuple localNormal = localPoint;
    localNormal.setWValue(0);
    return localNormal;
}


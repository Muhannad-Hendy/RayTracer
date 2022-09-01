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

bool operator== (Sphere& sphere1, Sphere& sphere2){
    if (sphere1.ID == sphere2.ID) return true;
    else return false;
}

Transformer Sphere::getTransformation() const{
    return transformation;
}

void Sphere::setTransformation(const Transformer& transformation){
    this->transformation = transformation;
}

Tuple Sphere::normal(Tuple& pointOnSphere) const{
    Tuple origin{0,0,0,TupleType::point};
    Tuple normalVector = (pointOnSphere - origin).normalize();
    return normalVector;
}

#include "Ray.h"
#include "Transformer.h"

Ray::Ray(){};

Ray::Ray(Tuple& origin, Tuple& direction) : origin{origin}, direction{direction}{}

Tuple Ray::getOrigin() const{
    return origin;
}

Tuple Ray::getDirection() const{
    return direction;
}

void Ray::initialize(Tuple& origin, Tuple& direction){
    Ray temporary{origin,direction};
    *this = temporary;
}

Ray& Ray::operator= (const Ray& original){
    if (this == &original) return *this;
    origin = original.origin;
    direction = original.direction;
    return *this;
}

Tuple Ray::locate(double time) const{
    Tuple deltaDistance = direction * time;
    Tuple distance = origin + deltaDistance;
    return distance;
}

void Ray::setDistance(double distance) {
    this->distance = distance;
}

double Ray::getDistance() const {
    return distance;
}

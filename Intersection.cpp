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

#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Sphere.h"

class Intersection
{
public:
    Intersection(){};

    Intersection(double time, Sphere& sphere) : intersectionTime{time}, intersectedSphere{&sphere}{};

    double getIntersectionTime() const{
        return intersectionTime;
    }

    Sphere* getIntersectedSphere(){
        return intersectedSphere;
    }

    friend bool operator< (const Intersection& intersection1, const Intersection& intersection2){
        if (intersection1.intersectionTime < intersection2.intersectionTime) return true;
        else return false;
    }

    friend bool operator== (const Intersection& intersection1, const Intersection& intersection2){
        if ((intersection1.intersectionTime == intersection2.intersectionTime)
                && (*intersection1.intersectedSphere == *intersection2.intersectedSphere)) return true;
        else return false;
    }

private:
    double intersectionTime{};
    Sphere* intersectedSphere{};
};

#endif // INTERSECTION_H

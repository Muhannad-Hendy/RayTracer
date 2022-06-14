#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Sphere.h"

class Intersection
{
public:
    Intersection(){};

    Intersection(double time, Sphere& sphere) : intersectionTime{time}, intersectedSphere{&sphere}{};

    double getIntersectionTime(){
        return intersectionTime;
    }

    Sphere* getIntersectedSphere(){
        return intersectedSphere;
    }

private:
    double intersectionTime{};
    Sphere* intersectedSphere{};
};

#endif // INTERSECTION_H

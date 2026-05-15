#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Tuple.h"

class Sphere;

class Intersection
{
public:
    Intersection();

    Intersection(double time, Sphere& sphere);

    double getIntersectionTime() const;

    Sphere* getIntersectedSphere();

    friend bool operator< (const Intersection& intersection1, const Intersection& intersection2){
        if (intersection1.intersectionTime < intersection2.intersectionTime) return true;
        else return false;
    }

    friend bool operator== (const Intersection& intersection1, const Intersection& intersection2);

    Tuple* getIntersectionPoint();

    void setIntersectionPoint(Tuple point);

    Tuple& getEyeVector();

    void setEyeVector(Tuple point);

    Tuple& getNormalVector();

    void setNormalVector();

private:
    double intersectionTime{};
    Sphere* intersectedSphere{};
    Tuple intersectionPoint{};
    Tuple eyeVector{};
    Tuple normalVector{};
};

#endif // INTERSECTION_H

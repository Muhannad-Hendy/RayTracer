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

    bool isInside() const;

    void setInside(bool status);

    void invertNormal();

private:
    double intersectionTime{};
    Sphere* intersectedSphere{};
    Tuple intersectionPoint{};
    Tuple eyeVector{};
    Tuple normalVector{};
    bool m_isInside{};
};

#endif // INTERSECTION_H

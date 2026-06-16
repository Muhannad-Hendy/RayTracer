#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Tuple.h"

class Shape;

class Intersection
{
public:
    Intersection();

    Intersection(double time, Shape &shape);

    double getIntersectionTime() const;

    Shape* getIntersectedShape();

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

    void setOverIntersectionPoint(Tuple point);

    Tuple& getOverIntersectionPoint();

private:
    double intersectionTime{};
    Shape* intersectedShape{};
    Tuple intersectionPoint{};
    Tuple eyeVector{};
    Tuple normalVector{};
    bool m_isInside{};
    Tuple overIntersectionPoint{};
};

#endif // INTERSECTION_H

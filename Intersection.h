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

    void setReflectionVector(const Tuple& reflectionVector);

    const Tuple& getReflectionVector() const;

    void setN1(const double n1);

    double getN1() const;

    void setN2(const double n2);

    double getN2() const;

private:
    double intersectionTime{};
    Shape* intersectedShape{};
    Tuple intersectionPoint{};
    Tuple eyeVector{};
    Tuple normalVector{};
    bool m_isInside{};
    Tuple overIntersectionPoint{};
    Tuple reflectionVector{};
    double n1{};
    double n2{};
};

#endif // INTERSECTION_H

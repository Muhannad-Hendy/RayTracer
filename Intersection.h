#ifndef INTERSECTION_H
#define INTERSECTION_H

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

private:
    double intersectionTime{};
    Sphere* intersectedSphere{};
};

#endif // INTERSECTION_H

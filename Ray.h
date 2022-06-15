#ifndef RAY_H
#define RAY_H
#include "Tuple.h"
#include "Sphere.h"
#include <cmath>
#include <vector>
#include "IntersectionTracker.h"

class Ray
{
public:
    Ray(){}

    Ray(Tuple& origin, Tuple& direction) : origin{origin}, direction{direction}{}

    Tuple getOrigin(){
        return origin;
    }

    Tuple getDirection(){
        return direction;
    }

    void initialize(Tuple& origin, Tuple& direction){
        Ray temporary{origin,direction};
        *this = temporary;
    }

    Ray& operator= (const Ray& original){
        if (this == &original) return *this;
        origin = original.origin;
        direction = original.direction;
        return *this;
    }

    Tuple locate(double time) {
        Tuple deltaDistance = direction * time;
        Tuple distance = origin + deltaDistance;
        return distance;
    }

    int getNumberOfIntersections(){
        return intersections.count();
    }

    double getIntersectionTime(int index){
        Intersection intersection =  intersections.getIntersection(index);
        return intersection.getIntersectionTime();
    }

    Sphere& getIntersectedObject(int index){
        Intersection intersection = intersections.getIntersection(index);
        return *intersection.getIntersectedSphere();
    }

    std::vector<double> calculateIntersectionParameters(Sphere& sphere){
        Tuple sphereCenter = sphere.getCenter();
        Tuple sphereToRay = this->origin - sphereCenter;
        double a = this->direction.dot(this->direction);
        double b = 2 * this->direction.dot(sphereToRay);
        double c = sphereToRay.dot(sphereToRay) - 1;
        double discriminant = b * b - 4 * a * c;
        return {a, b, c, discriminant};
    }

    void intersect(Sphere& sphere){
        std::vector<double> intersectionParameters = calculateIntersectionParameters(sphere);
        double a = intersectionParameters[0];
        double b = intersectionParameters[1];
        double discriminant = intersectionParameters[3];

        if (discriminant >= 0) {
            double intersectionTime1 = (-b - sqrt(discriminant)) / (2 * a);
            double intersectionTime2 = (-b + sqrt(discriminant)) / (2 * a);
            intersections.addIntersection(intersectionTime1, sphere);
            intersections.addIntersection(intersectionTime2, sphere);
        }
    }

private:
    Tuple origin{};
    Tuple direction{};
    IntersectionTracker intersections{};
};
#endif // RAY_H

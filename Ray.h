#ifndef RAY_H
#define RAY_H
#include "Tuple.h"
#include <iostream>
#include "Sphere.h"
#include <cmath>
//class Sphere;

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
        return numberOfIntersections;
    }

    double getIntersectionDistance(int index){
        return intersectionDistance[index];
    }

    void intersect(Sphere& sphere){
        Tuple sphereCenter = sphere.getCenter();
        Tuple sphereToRay = this->origin - sphereCenter;
        std::cout << sphereToRay.getYValue() << sphereToRay.getZValue() << std::endl;
        double a = this->direction.dot(this->direction);
        std::cout << "a: " << a << std::endl;
        double b = 2 * this->direction.dot(sphereToRay);
        std::cout << "b: " << b << std::endl;
        double c = sphereToRay.dot(sphereToRay) - 1;
        std::cout << "c: " << c << std::endl;

        double discriminant = b * b - 4 * a * c;
        std::cout << "discriminant: " << discriminant << std::endl;

        if (discriminant < 0) {
            numberOfIntersections = 0;
        }
        else {
            numberOfIntersections = 2;
            intersectionDistance = new double[numberOfIntersections];
            intersectionDistance[0] = (-b - sqrt(discriminant)) / (2 * a);
            intersectionDistance[1] = (-b + sqrt(discriminant)) / (2 * a);
        }
    }
private:
    Tuple origin{};
    Tuple direction{};
    int numberOfIntersections{};
    double* intersectionDistance;
};
#endif // RAY_H

#include "Ray.h"
#include "Sphere.h"
#include "Transformer.h"

Ray::Ray(){};

Ray::Ray(Tuple& origin, Tuple& direction) : origin{origin}, direction{direction}{}

Tuple Ray::getOrigin() const{
    return origin;
}

Tuple Ray::getDirection() const{
    return direction;
}

void Ray::initialize(Tuple& origin, Tuple& direction){
    Ray temporary{origin,direction};
    *this = temporary;
}

Ray& Ray::operator= (const Ray& original){
    if (this == &original) return *this;
    origin = original.origin;
    direction = original.direction;
    return *this;
}

Tuple Ray::locate(double time) {
    Tuple deltaDistance = direction * time;
    Tuple distance = origin + deltaDistance;
    return distance;
}

int Ray::getNumberOfIntersections() const{
    return intersections.count();
}

double Ray::getIntersectionTime(int index) {
    Intersection intersection =  intersections.getIntersection(index);
    return intersection.getIntersectionTime();
}

Sphere& Ray::getIntersectedObject(int index) {
    Intersection intersection = intersections.getIntersection(index);
    return *intersection.getIntersectedSphere();
}

std::vector<double> Ray::calculateIntersectionParameters(Sphere& sphere){
    Transformer rayTransformation = sphere.getTransformation().invert();
    Ray rayTransformed = rayTransformation.transform(*this);
    Tuple sphereCenter = sphere.getCenter();
    Tuple rayOrigin = rayTransformed.getOrigin();
    Tuple rayDirection = rayTransformed.getDirection();
    Tuple sphereToRay = rayOrigin - sphereCenter;

    double a = rayDirection.dot(rayDirection);
    double b = 2 * rayDirection.dot(sphereToRay);
    double c = sphereToRay.dot(sphereToRay) - 1;
    double discriminant = b * b - 4 * a * c;
    return {a, b, c, discriminant};
}

void Ray::intersect(Sphere& sphere) {
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

void Ray::intersect(World& world) {
    int numberOfSpheres = world.getNumberOfSpheres();
    for (int i = 0; i < numberOfSpheres; i++) {
        Sphere sphere = world.getSphere(i);
        intersect(sphere);
    }
}

bool Ray::hitFound() {
    if (this->intersections.hit() != nullptr) return true;
    else return false;
}

IntersectionTracker Ray::getIntersectionTracker() const {
    return intersections;
}

void Ray::prepComputations() {
    for (Intersection& intersection : intersections) {
        Tuple intersectionPoint = locate(intersection.getIntersectionTime());
        intersection.setIntersectionPoint(intersectionPoint);
        intersection.setEyeVector(-direction);
        intersection.setNormalVector();
        double dotProduct = intersection.getEyeVector().dot(intersection.getNormalVector());
        if (dotProduct < 0){
            intersection.setInside(true);
            intersection.invertNormal();
        }
        else {
            intersection.setInside(false);
        }
    }
}

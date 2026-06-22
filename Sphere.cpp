#include "Sphere.h"
#include "Material.h"

int Sphere::spheresCounter=0;

Sphere::Sphere() {
    ID = spheresCounter;
    spheresCounter++;
    radius = 1.0;
    center.initialize(0,0,0,TupleType::point);
}

Sphere::Sphere(SphereType type) {
    switch (type) {
    case SphereType::glass: {
        ID = spheresCounter;
        spheresCounter++;
        radius = 1.0;
        center.initialize(0,0,0,TupleType::point);
        Material glass{};
        glass.setTransparency(1);
        glass.setRefractiveIndex(1.5);
        setMaterial(glass);
    }

    }
}

Tuple Sphere::getCenter() const{
    return center;
}

Tuple Sphere::localNormalAt(const Tuple &localPoint) const {
    Tuple localNormal = localPoint;
    localNormal.setWValue(0);
    return localNormal;
}

void Sphere::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    std::vector<double> intersectionParameters = calculateIntersectionParameters(localRay);
    double a = intersectionParameters[0];
    double b = intersectionParameters[1];
    double discriminant = intersectionParameters[3];

    if (discriminant >= 0) {
        double intersectionTime1 = (-b - sqrt(discriminant)) / (2 * a);
        double intersectionTime2 = (-b + sqrt(discriminant)) / (2 * a);
        tracker.addIntersection(intersectionTime1, *this);
        tracker.addIntersection(intersectionTime2, *this);
    }
}

std::vector<double> Sphere::calculateIntersectionParameters(const Ray &ray) const {
    Tuple rayOrigin = ray.getOrigin();
    Tuple rayDirection = ray.getDirection();
    Tuple objectOrigin{0,0,0,TupleType::point};
    Tuple sphereToRay = rayOrigin - objectOrigin;

    double a = rayDirection.dot(rayDirection);
    double b = 2 * rayDirection.dot(sphereToRay);
    double c = sphereToRay.dot(sphereToRay) - 1;
    double discriminant = b * b - 4 * a * c;
    return {a, b, c, discriminant};
}


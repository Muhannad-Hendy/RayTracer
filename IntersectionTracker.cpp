#include "IntersectionTracker.h"

IntersectionTracker::IntersectionTracker(){};

IntersectionTracker::IntersectionTracker(std::vector<Intersection> intersectionsVector){
    for (auto intersection : intersectionsVector){
        addIntersection(intersection);
        sortIntersections();
    }
}

void IntersectionTracker::addIntersection(const Intersection& intersection){
    intersections.push_back(intersection);
    sortIntersections();
}

void IntersectionTracker::addIntersection(double time,Shape &shape){
    intersections.emplace_back(time, shape);
    sortIntersections();
}

Intersection& IntersectionTracker::getIntersection(int position) {
    auto listStart = intersections.begin();
    std::advance(listStart, position);
    return *listStart;
}

int IntersectionTracker::count() const{
    return intersections.size();
}

void IntersectionTracker::sortIntersections(){
    intersections.sort([](const Intersection& intersection1, const Intersection intersection2)
                        { return intersection1 < intersection2; });
}

Intersection* IntersectionTracker::hit(){
    for (auto& element : intersections){
        if (element.getIntersectionTime() >= 0) return &element;
    }
    return nullptr;
}

int IntersectionTracker::getNumberOfIntersections() const {
    return intersections.size();
}

double IntersectionTracker::getIntersectionTime(const int index) {
    Intersection intersection =  this->getIntersection(index);
    return intersection.getIntersectionTime();
}

Shape& IntersectionTracker::getIntersectedObject(const int index) {
    Intersection intersection = this->getIntersection(index);
    return *intersection.getIntersectedShape();
}

void IntersectionTracker::prepComputations(const Ray &ray) {
    for (Intersection& intersection : intersections) {
        Tuple intersectionPoint = ray.locate(intersection.getIntersectionTime());
        intersection.setIntersectionPoint(intersectionPoint);
        intersection.setEyeVector(-ray.getDirection());
        intersection.setNormalVector();
        Tuple offsetVector = intersection.getNormalVector() * util::EPSILON;
        Tuple overIntersection = intersectionPoint + offsetVector;
        intersection.setOverIntersectionPoint(overIntersection);
        Tuple rayReflectionVector = ray.getDirection().reflectAround(intersection.getNormalVector());
        intersection.setReflectionVector(rayReflectionVector);
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

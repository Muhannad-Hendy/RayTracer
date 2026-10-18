#include "IntersectionTracker.h"
#include "Shape.h"
#include <algorithm>
#include <vector>

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

void IntersectionTracker::addIntersection(double time,Shape &shape, double u, double v){
    intersections.emplace_back(time, shape, u, v);
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
    setRefractionIndices();
    for (Intersection& intersection : intersections) {
        Tuple intersectionPoint = ray.locate(intersection.getIntersectionTime());
        intersection.setIntersectionPoint(intersectionPoint);
        intersection.setEyeVector(-ray.getDirection());
        intersection.setNormalVector();

        double dotProduct = intersection.getEyeVector().dot(intersection.getNormalVector());
        if (dotProduct < 0){
            intersection.setInside(true);
            intersection.invertNormal();
        }
        else {
            intersection.setInside(false);
        }

        Tuple offsetVector = intersection.getNormalVector() * util::EPSILON;
        Tuple overIntersection = intersectionPoint + offsetVector;
        intersection.setOverIntersectionPoint(overIntersection);
        Tuple underIntersection = intersectionPoint - offsetVector;
        intersection.setUnderIntersectionPoint(underIntersection);
        Tuple rayReflectionVector = ray.getDirection().reflectAround(intersection.getNormalVector());
        intersection.setReflectionVector(rayReflectionVector);
    }
}

void IntersectionTracker::setRefractionIndices() {
    std::vector<Shape*> encounteredShapes;
    encounteredShapes.reserve(10);
    for (auto& intersection : intersections) {
        auto* intersectedShape = intersection.getIntersectedShape();
        if (intersection.getIntersectionTime() >= 0) {
            if (encounteredShapes.empty()) {
                intersection.setN1(1);
            }
            else {
                auto& lastInList = encounteredShapes.back();
                double refractiveIndex = lastInList->getMaterial().getRefractiveIndex();
                intersection.setN1(refractiveIndex);
            }
        }
        auto intersectionInList = std::find(encounteredShapes.begin(), encounteredShapes.end(), intersectedShape);
        if (intersectionInList != encounteredShapes.end()) {
            encounteredShapes.erase(intersectionInList);
        }
        else {
            encounteredShapes.push_back(intersectedShape);
        }
        if (intersection.getIntersectionTime() >= 0) {
            if (encounteredShapes.empty()) {
                intersection.setN2(1);
            }
            else {
                auto& lastInList = encounteredShapes.back();
                double refractiveIndex = lastInList->getMaterial().getRefractiveIndex();
                intersection.setN2(refractiveIndex);
            }
        }
    }
}

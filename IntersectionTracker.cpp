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

void IntersectionTracker::addIntersection(double time, Sphere& sphere){
    intersections.emplace_back(time, sphere);
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

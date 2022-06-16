#ifndef INTERSECTIONTRACKER_H
#define INTERSECTIONTRACKER_H

#include <list>
#include <vector>
#include "Intersection.h"

class IntersectionTracker
{
public:
    IntersectionTracker(){};

    IntersectionTracker(std::vector<Intersection> intersectionsVector){
        for (auto intersection : intersectionsVector){
            addIntersection(intersection);
            sortIntersections();
        }
    }

    void addIntersection(const Intersection& intersection){
        intersections.push_back(intersection);
        sortIntersections();
    }

    void addIntersection(double time, Sphere& sphere){
        intersections.emplace_back(time, sphere);
        sortIntersections();
    }

    Intersection getIntersection(int position) const{
        auto listStart = intersections.begin();
        std::advance(listStart, position);
        return *listStart;
    }

    int count() const{
        return intersections.size();
    }

    void sortIntersections(){
        intersections.sort([](const Intersection& intersection1, const Intersection intersection2)
                            { return intersection1 < intersection2; });
    }

    Intersection* hit(){
        for (auto& element : intersections){
            if (element.getIntersectionTime() >= 0) return &element;
        }
        return nullptr;
    }

private:
    std::list<Intersection> intersections{};
};

#endif // INTERSECTIONTRACKER_H

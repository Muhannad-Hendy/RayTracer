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
        }
    }

    void addIntersection(const Intersection& intersection){
        intersections.push_back(intersection);
    }

    void addIntersection(double time, Sphere& sphere){
        intersections.emplace_back(time, sphere);
    }

    Intersection getIntersection(int position) const{
        auto listStart = intersections.begin();
        std::advance(listStart, position);
        return *listStart;
    }

    int count() const{
        return intersections.size();
    }

private:
    std::list<Intersection> intersections{};
};

#endif // INTERSECTIONTRACKER_H

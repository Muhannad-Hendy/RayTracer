#ifndef INTERSECTIONTRACKER_H
#define INTERSECTIONTRACKER_H

#include <list>
#include <vector>
#include "Intersection.h"

class IntersectionTracker
{
public:
    IntersectionTracker();

    IntersectionTracker(std::vector<Intersection> intersectionsVector);

    void addIntersection(const Intersection& intersection);

    void addIntersection(double time, Shape &shape);

    Intersection& getIntersection(int position);

    int count() const;

    void sortIntersections();

    Intersection* hit();

    auto begin() {
        return intersections.begin();
    }

    auto end() {
        return intersections.end();
    }

private:
    std::list<Intersection> intersections{};
};

#endif // INTERSECTIONTRACKER_H

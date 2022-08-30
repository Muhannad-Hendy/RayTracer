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

    void addIntersection(double time, Sphere& sphere);

    Intersection getIntersection(int position) const;

    int count() const;

    void sortIntersections();

    Intersection* hit();

private:
    std::list<Intersection> intersections{};
};

#endif // INTERSECTIONTRACKER_H

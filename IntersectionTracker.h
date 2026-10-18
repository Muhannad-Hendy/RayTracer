#ifndef INTERSECTIONTRACKER_H
#define INTERSECTIONTRACKER_H

#include <list>
#include <vector>
#include "Intersection.h"
#include "Ray.h"

class IntersectionTracker
{
public:
    IntersectionTracker();

    IntersectionTracker(std::vector<Intersection> intersectionsVector);

    void addIntersection(const Intersection& intersection);

    void addIntersection(double time, Shape &shape);

    void addIntersection(double time, Shape &shape, double u, double v);

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

    int getNumberOfIntersections() const;

    double getIntersectionTime(const int index);

    Shape& getIntersectedObject(const int index);

    void prepComputations(const Ray &ray);

    void setRefractionIndices();


private:
    std::list<Intersection> intersections{};
};

#endif // INTERSECTIONTRACKER_H

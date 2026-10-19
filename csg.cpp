#include "csg.h"
#include <typeinfo>
#include "group.h"

CSG::CSG(Operation operation, std::unique_ptr<Shape> left, std::unique_ptr<Shape> right) :
    operation{operation}, leftShape{std::move(left)}, rightShape{std::move(right)}
{
  leftShape->setParent(this);
  rightShape->setParent(this);
}

void CSG::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    leftShape->intersect(localRay,tracker);
    rightShape->intersect(localRay,tracker);
    filterIntersections(tracker);
}

Tuple CSG::localNormalAt(const Tuple &localPoint, Intersection *intersection) const {

}

Operation CSG::getOperation() const {
    return operation;
}

Shape* CSG::getLeftShape() const {
    return leftShape.get();
}

Shape* CSG::getRightShape() const {
    return rightShape.get();
}

bool CSG::intersectionAllowed(bool leftHit, bool insideLeft, bool insideRight) const {
    if (operation==Operation::Union) {
        return (leftHit && !insideRight) || (!leftHit && !insideLeft);
    }
    else if (operation==Operation::Intersection) {
        return (leftHit && insideRight) || (!leftHit && insideLeft);
    }
    else if (operation==Operation::Difference) {
        return (leftHit && !insideRight) || (!leftHit && insideLeft);
    }

    return false;
}

void CSG::filterIntersections(IntersectionTracker &tracker) {
    bool insideLeft = false;
    bool insideRight = false;
    IntersectionTracker updatedTracker{};

    std::size_t numberOfIntersections = tracker.getNumberOfIntersections();
    for (std::size_t i=0; i < numberOfIntersections; i++) {
        Intersection intersection = tracker.getIntersection(i);
        bool leftHit = leftShape->includes(*intersection.getIntersectedShape());

        if (intersectionAllowed(leftHit,insideLeft,insideRight)) {
            updatedTracker.addIntersection(intersection);
        }

        if (leftHit) {
            insideLeft = !insideLeft;
        }
        else {
            insideRight = !insideRight;
        }
    }
    tracker = std::move(updatedTracker);
}

bool CSG::includes(const Shape &shape) const {
    return (leftShape->includes(shape)) || (rightShape->includes(shape));
}

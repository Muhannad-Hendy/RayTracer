#include "group.h"
#include <algorithm>

Group::Group()
{

}

Tuple Group::localNormalAt(const Tuple &localPoint, Intersection *intersection) const {

}

void Group::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    for (const auto& shape:children) shape->intersect(localRay,tracker);
}

int Group::getChildrenCount() {
    return children.size();
}

bool Group::isEmpty() {
    return children.empty();
}

Shape* Group::getChild(std::size_t childNumber) const {
    return children.at(childNumber).get();
}

bool Group::includes(const Shape &shape) const {
    return std::any_of(children.begin(), children.end(),
                [&] (const auto& child) {return child->includes(shape);});
}

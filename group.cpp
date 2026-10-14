#include "group.h"

Group::Group()
{

}

Tuple Group::localNormalAt(const Tuple &localPoint) const {

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

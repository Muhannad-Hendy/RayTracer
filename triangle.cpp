#include "triangle.h"

Triangle::Triangle(const Tuple& point1, const Tuple& point2, const Tuple point3) : vertices{point1,point2,point3} {
    edges.push_back(point2-point1);
    edges.push_back(point3-point1);
    setNormal();
}

void Triangle::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
    auto rayCrossEdge2 = localRay.getDirection().cross(edges[1]);
    auto determinant = rayCrossEdge2.dot(edges[0]);
    if (std::abs(determinant) < util::EPSILON) return;

    auto f = 1/determinant;
    auto p1ToOrigin = localRay.getOrigin() - vertices[0];
    auto u = f * p1ToOrigin.dot(rayCrossEdge2);
    if (u<0  || u>1) return;

    auto originCrossEdge1 = p1ToOrigin.cross(edges[0]);
    auto v = f * localRay.getDirection().dot(originCrossEdge1);
    if (v<0 || (u+v)>1) return;

    auto t = f * edges[1].dot(originCrossEdge1);
    tracker.addIntersection(t,*this);
}

Tuple Triangle::localNormalAt(const Tuple &localPoint) const {
    return normal;
}

Tuple Triangle::getVertex(const int index) const {
    return vertices[index];
}

Tuple Triangle::getEdge(const int index) const {
    return edges[index];
}

void Triangle::setNormal() {
    normal = edges[1].cross(edges[0]).normalize();
}

Tuple Triangle::getNormal() const {
    return normal;
}


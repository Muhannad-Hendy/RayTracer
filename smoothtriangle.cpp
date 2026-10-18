#include "smoothtriangle.h"

SmoothTriangle::SmoothTriangle(const Tuple& point1, const Tuple& point2, const Tuple point3,
                               const Tuple &vnormal1, const Tuple &vnormal2, const Tuple &vnormal3)
    : Triangle(point1,point2,point3), vertexNormals{vnormal1,vnormal2,vnormal3}
{

}

Tuple SmoothTriangle::getVertexNormal(const int index) const {
    return vertexNormals[index];
}

void SmoothTriangle::localIntersect(const Ray &localRay, IntersectionTracker &tracker) {
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
    tracker.addIntersection(t,*this, u, v);
}

Tuple SmoothTriangle::localNormalAt(const Tuple &localPoint, Intersection *intersection) const {
    double u = intersection->getU();
    double v = intersection->getV();
    auto normal = vertexNormals[1] * u + vertexNormals[2] * v + vertexNormals[0] * (1-u-v);
    return normal;
}

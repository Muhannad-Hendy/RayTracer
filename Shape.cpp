#include "Shape.h"
#include "Matrix.h"
#include "IntersectionTracker.h"
#include "group.h"

int Shape::shapesCounter = 0;

Shape::Shape() : shapeID{shapesCounter++} {}

const Transformer& Shape::getTransformation() const {
    return transformation;
}

void Shape::setTransformation(const Transformer &transformation) {
    this->transformation = transformation;
}

Material& Shape::getMaterial() {
    return material;
}

void Shape::setMaterial(const Material &newMaterial) {
    this->material = newMaterial;
}

Tuple Shape::normalAt(const Tuple &worldPoint, Intersection *intersection) const {
    Tuple localPoint = worldToObject(worldPoint);
    Tuple localNormal = localNormalAt(localPoint, intersection);
    return normalToWorld(localNormal);
}

bool operator== (const Shape &shape1, const Shape &shape2) {
    if (shape1.shapeID == shape2.shapeID) return true;
    else return false;
}

int Shape::getShapeID() const {
    return shapeID;
}

void Shape::intersect(const Ray &ray, IntersectionTracker &tracker) {
    Ray localRay = transformation.invert().transform(ray);
    localIntersect(localRay, tracker);
}

Group* Shape::getParent() const{
    return parent;
}

void Shape::setParent(Group* group) {
    parent = group;
}

Tuple Shape::worldToObject(const Tuple &point) const {
    Tuple localPoint = point;
    if (parent!=nullptr) {
        localPoint = parent->worldToObject(point);
    }
    return transformation.invert().transform(localPoint);
}

Tuple Shape::normalToWorld(const Tuple &normal) const {
    Tuple worldNormal = transformation.invert().getTransformationMatrix().transpose() * normal;
    worldNormal.setWValue(0);
    worldNormal = worldNormal.normalize();

    if (parent!=nullptr) {
        worldNormal = parent->normalToWorld(worldNormal);
    }
    return worldNormal;
}

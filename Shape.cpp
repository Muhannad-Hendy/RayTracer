#include "Shape.h"
#include "Matrix.h"

int Shape::shapesCounter = 0;

Shape::Shape() : shapeID{shapesCounter++} {}

const Transformer& Shape::getTransformation() const {
    return transformation;
}

void Shape::setTransformation(const Transformer &transformation) {
    this->transformation = transformation;
}

const Material& Shape::getMaterial() const {
    return material;
}

void Shape::setMaterial(const Material &newMaterial) {
    this->material = newMaterial;
}

Tuple Shape::normalAt(const Tuple &worldPoint) const {
    Tuple localPoint = transformation.invert().transform(worldPoint);
    Tuple localNormal = localNormalAt(localPoint);
    Matrix objectToWorldTransformation = transformation.invert().getTransformationMatrix().transpose();
    Tuple worldNormal = objectToWorldTransformation * localNormal;
    worldNormal.setWValue(0);
    return worldNormal.normalize();
}

bool operator== (const Shape &shape1, const Shape &shape2) {
    if (shape1.shapeID == shape2.shapeID) return true;
    else return false;
}

int Shape::getShapeID() const {
    return shapeID;
}

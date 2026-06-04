#include <cmath>
#include "Transformer.h"
#include "Matrix.h"
#include "Tuple.h"
#include "Ray.h"

Transformer::Transformer(){}

Transformer::Transformer(Transformation type, double x, double y, double z) {
    switch (type) {
    case Transformation::translation: {
        transformationMatrix.set(0,3,x);
        transformationMatrix.set(1,3,y);
        transformationMatrix.set(2,3,z);
    } break;
    case Transformation::scaling: {
        transformationMatrix.set(0,0,x);
        transformationMatrix.set(1,1,y);
        transformationMatrix.set(2,2,z);
    } break;

    }

}

Transformer::Transformer(Transformation type, double radians){
    switch (type) {
    case Transformation::xRotation: {
        transformationMatrix.set(1,1,cos(radians));
        transformationMatrix.set(1,2,-sin(radians));
        transformationMatrix.set(2,1,sin(radians));
        transformationMatrix.set(2,2,cos(radians));
    } break;
    case Transformation::yRotation: {
        transformationMatrix.set(0,0,cos(radians));
        transformationMatrix.set(0,2,sin(radians));
        transformationMatrix.set(2,0,-sin(radians));
        transformationMatrix.set(2,2,cos(radians));
    } break;
    case Transformation::zRotation: {
        transformationMatrix.set(0,0,cos(radians));
        transformationMatrix.set(0,1,-sin(radians));
        transformationMatrix.set(1,0,sin(radians));
        transformationMatrix.set(1,1,cos(radians));
    } break;

    }
}

Transformer::Transformer(double xRelativeY, double xRelativeZ, double yRelativeX, double yRelativeZ, double zRelativeX, double zRelativeY){
    transformationMatrix.set(0,1,xRelativeY);
    transformationMatrix.set(0,2,xRelativeZ);
    transformationMatrix.set(1,0,yRelativeX);
    transformationMatrix.set(1,2,yRelativeZ);
    transformationMatrix.set(2,0,zRelativeX);
    transformationMatrix.set(2,1,zRelativeY);
}

Transformer::Transformer(Tuple from, Tuple to, Tuple upDirection){
    Tuple forwardVector = (to - from).normalize();
    Tuple normalizedUp = upDirection.normalize();
    Tuple leftDirection = forwardVector.cross(normalizedUp);
    Tuple trueUp = leftDirection.cross(forwardVector);
    transformationMatrix.set(0,0, leftDirection.getXValue());
    transformationMatrix.set(0,1, leftDirection.getYValue());
    transformationMatrix.set(0,2, leftDirection.getZValue());
    transformationMatrix.set(1,0, trueUp.getXValue());
    transformationMatrix.set(1,1, trueUp.getYValue());
    transformationMatrix.set(1,2, trueUp.getZValue());
    transformationMatrix.set(2,0, -forwardVector.getXValue());
    transformationMatrix.set(2,1, -forwardVector.getYValue());
    transformationMatrix.set(2,2, -forwardVector.getZValue());
    Transformer translation{Transformation::translation, -from.getXValue(), -from.getYValue(), -from.getZValue()};
    Matrix viewTransformation = transformationMatrix * translation.getTransformationMatrix();
    transformationMatrix = viewTransformation;
}

Tuple Transformer::transform(const Tuple& original) const{
    Tuple transformed = this->transformationMatrix * original;
    return transformed;
}

Ray Transformer::transform(const Ray& original) const{
    Tuple originTransformed = this->transformationMatrix * original.getOrigin();
    Tuple directionTransformed = this->transformationMatrix * original.getDirection();
    Ray transformed{originTransformed, directionTransformed};
    return transformed;
}

Transformer Transformer::invert() const{
    Transformer transformation{};
    transformation.transformationMatrix = this->transformationMatrix.invert();
    return transformation;
}

Transformer operator> (const Transformer& transformation1, const Transformer& transformation2){
    Transformer chain{};
    chain.transformationMatrix = transformation2.transformationMatrix * transformation1.transformationMatrix;
    return chain;
}

Matrix Transformer::getTransformationMatrix() const{
    return transformationMatrix;
}

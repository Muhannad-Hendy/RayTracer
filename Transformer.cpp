#include <cmath>
#include "Transformer.h"
#include "Matrix.h"
#include "Tuple.h"

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

Tuple Transformer::transform(const Tuple& original) const{
    Tuple transformed = this->transformationMatrix * original;
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

#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "Matrix.h"
class Tuple;
class Ray;

enum class Transformation{
    translation,
    scaling,
    xRotation,
    yRotation,
    zRotation,
    shearing,
    view
};

class Transformer
{
public:
    Transformer();

    Transformer(Transformation type, double x, double y, double z);

    Transformer(Transformation type, double radians);

    Transformer(double xRelativeY, double xRelativeZ, double yRelativeX, double yRelativeZ, double zRelativeX, double zRelativeY);

    Transformer(const Transformer& original) {
        transformationMatrix = original.transformationMatrix;
    }

    Transformer(Tuple from, Tuple to, Tuple upDirection);

    Tuple transform(const Tuple& original) const;

    Ray transform(const Ray& original) const;

    Transformer invert() const;

    friend Transformer operator> (const Transformer& transformation1, const Transformer& transformation2);

    Matrix getTransformationMatrix() const;

private:
    Matrix transformationMatrix{4, MatrixType::identity};
};

#endif // TRANSFORMER_H

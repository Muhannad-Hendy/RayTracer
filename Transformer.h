#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "Matrix.h"
class Tuple;

enum class Transformation{
    translation,
    scaling,
    xRotation,
    yRotation,
    zRotation,
    shearing
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

    Tuple transform(const Tuple& original) const;

    Transformer invert() const;

    friend Transformer operator> (const Transformer& transformation1, const Transformer& transformation2);

private:
    Matrix transformationMatrix{4, MatrixType::identity};
};

#endif // TRANSFORMER_H

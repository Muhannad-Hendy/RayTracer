#ifndef SHAPE_H
#define SHAPE_H

#include "Tuple.h"
#include "Transformer.h"
#include "Material.h"

class Shape
{
public:
    Shape();

    virtual ~Shape() = default;

    const Transformer& getTransformation() const;

    void setTransformation(const Transformer &transformation);

    const Material& getMaterial() const;

    void setMaterial(const Material &newMaterial);

    Tuple normalAt(const Tuple &worldPoint) const;

    friend bool operator== (const Shape &shape1, const Shape &shape2);

    int getShapeID() const;

protected:
    virtual Tuple localNormalAt(const Tuple& localPoint) const = 0;

private:
    Transformer transformation{};
    Material material{};
    static int shapesCounter;
    int shapeID{};
};

#endif // SHAPE_H

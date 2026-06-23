#ifndef SHAPE_H
#define SHAPE_H

#include "Tuple.h"
#include "Transformer.h"
#include "Material.h"
#include "IntersectionTracker.h"
#include "Ray.h"

class Shape
{
public:
    Shape();

    virtual ~Shape() = default;

    const Transformer& getTransformation() const;

    void setTransformation(const Transformer &transformation);

    Material& getMaterial();

    void setMaterial(const Material &newMaterial);

    Tuple normalAt(const Tuple &worldPoint) const;

    friend bool operator== (const Shape &shape1, const Shape &shape2);

    int getShapeID() const;

    void intersect(const Ray &ray, IntersectionTracker &tracker);

protected:
    virtual Tuple localNormalAt(const Tuple& localPoint) const = 0;
    virtual void localIntersect(const Ray &localRay, IntersectionTracker &tracker) = 0;

private:
    Transformer transformation{};
    Material material{};
    static int shapesCounter;
    int shapeID{};
};

#endif // SHAPE_H

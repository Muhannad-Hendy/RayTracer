#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"
#include "Transformer.h"
#include "Material.h"

class Sphere
{
public:
    Sphere();

    Tuple getCenter() const;

    int getSphereID() const;

    friend bool operator== (Sphere& sphere1, Sphere& sphere2);

    Transformer getTransformation() const;

    void setTransformation(const Transformer& transformation);

    Tuple normal(Tuple& pointOnSphere) const;

    Material getMaterial() const;

    void setMaterial(const Material& newMaterial);

private:
    static int spheresCounter;
    int ID{};
    double radius{};
    Tuple center{};
    Transformer transformation{};
    Material material{};
};

#endif // SPHERE_H

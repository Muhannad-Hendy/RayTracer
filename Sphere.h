#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"
#include "Transformer.h"

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

private:
    static int spheresCounter;
    int ID{};
    double radius{};
    Tuple center{};
    Transformer transformation{};
};

#endif // SPHERE_H

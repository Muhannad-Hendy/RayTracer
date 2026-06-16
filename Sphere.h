#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape
{
public:
    Sphere();

    Tuple getCenter() const;

protected:
    Tuple localNormalAt(const Tuple &localPoint) const override;

private:
    static int spheresCounter;
    int ID{};
    double radius{};
    Tuple center{};
};

#endif // SPHERE_H

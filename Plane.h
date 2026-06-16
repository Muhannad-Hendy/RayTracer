#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public:
    Plane();

protected:
    Tuple localNormalAt(const Tuple &localPoint) const override;
};

#endif // PLANE_H

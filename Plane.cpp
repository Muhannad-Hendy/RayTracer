#include "Plane.h"

Plane::Plane() {}

Tuple Plane::localNormalAt(const Tuple &localPoint) const {
    Tuple normal{0,1,0,TupleType::vector};
    return normal;
}

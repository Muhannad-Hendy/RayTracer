#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Tuple.h"

class Light
{
public:
    Light(const Tuple& position, const Color& intensity);

    Tuple getPosition() const;

    Color getIntensity() const;

private:
    Tuple position;
    Color intensity;
};

#endif // LIGHT_H

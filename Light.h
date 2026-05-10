#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Tuple.h"
#include "Material.h"

class Light
{
public:
    Light(const Tuple& position, const Color& intensity);

    Tuple getPosition() const;

    Color getIntensity() const;

    Color light(Material& material, Tuple& target, Tuple& eyeVector, Tuple& normalVector);

    friend bool operator== (Light& light1, Light& light2);

private:
    Tuple position;
    Color intensity;
    Color black{0,0,0};
};

#endif // LIGHT_H

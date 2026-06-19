#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Tuple.h"

class Shape;
class Material;

class Light
{
public:
    Light(const Tuple& position, const Color& intensity);

    Tuple getPosition() const;

    Color getIntensity() const;

    Color light(const Material& material, const Shape& shape, const Tuple& point, const Tuple& eyeVector, const Tuple& normalVector, const bool inShadow=false) const;

    Color light(const Material& material, const Tuple& point, const Tuple& eyeVector, const Tuple& normalVector, const bool inShadow=false) const;

    friend bool operator== (Light& light1, Light& light2);

private:
    Tuple position;
    Color intensity;
    Color black{0,0,0};
};

#endif // LIGHT_H

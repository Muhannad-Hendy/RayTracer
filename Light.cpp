#include "Light.h"

Light::Light(const Tuple& position, const Color& intensity) : position{position}, intensity{intensity} {}

Tuple Light::getPosition() const{
    return position;
}

Color Light::getIntensity() const{
    return intensity;
}

#include "Light.h"

Light::Light(const Tuple& position, const Color& intensity) : position{position}, intensity{intensity} {}

Tuple Light::getPosition() const{
    return position;
}

Color Light::getIntensity() const{
    return intensity;
}

Color Light::light(Material &material, Tuple &target, Tuple &eyeVector, Tuple &normalVector) {
    Color effectiveColor = material.getColor() * this->intensity;
    Tuple lightVector = this->position - target;
    lightVector = lightVector.normalize();
    Color ambientComponent = effectiveColor * material.getAmbient();
    double lightDotNormal = lightVector.dot(normalVector);
    Color diffuseComponent;
    Color specularComponent;
    if (lightDotNormal < 0) {
        diffuseComponent = this->black;
        specularComponent = this->black;
    }
    else {
        diffuseComponent = effectiveColor * material.getDiffuse() * lightDotNormal;
        Tuple reflectedVector = -lightVector.reflectAround(normalVector);
        double reflectedVectorDotEyeVector = reflectedVector.dot(eyeVector);
        if (reflectedVectorDotEyeVector <= 0) {
            specularComponent = this->black;
        }
        else {
            double factor = pow(reflectedVectorDotEyeVector,material.getShininess());
            specularComponent = this->intensity * material.getSpecular() * factor;
        }
    }
    return ambientComponent + diffuseComponent + specularComponent;
}

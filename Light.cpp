#include "Light.h"

Light::Light(const Tuple& position, const Color& intensity) : position{position}, intensity{intensity} {}

Tuple Light::getPosition() const{
    return position;
}

Color Light::getIntensity() const{
    return intensity;
}

Color Light::light(Material &material, Tuple &target, Tuple &eyeVector, Tuple &normalVector, bool inShadow) {
    Color effectiveColor = material.getColor() * this->intensity;
    Tuple lightVector = this->position - target;
    lightVector = lightVector.normalize();
    Color ambientComponent = effectiveColor * material.getAmbient();
    if (inShadow) return ambientComponent;
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

bool operator== (Light& light1, Light& light2){
    if ((light1.position==light2.position) && (light1.intensity==light2.intensity))
            return true;
    else return false;
}

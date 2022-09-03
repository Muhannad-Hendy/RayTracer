#include "Material.h"

Material::Material() {
    Color defaultColor{1,1,1};
    color = defaultColor;
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200;
}

Color Material::getColor() const{
    return color;
}

void Material::setColor(const Color& newColor){
    color = newColor;
}

double Material::getAmbient() const{
    return ambient;
}

void Material::setAmbient(const double newAmbient){
    ambient = newAmbient;
}

double Material::getDiffuse() const{
    return diffuse;
}

void Material::setDiffuse(const double newDiffuse){
    diffuse = newDiffuse;
}

double Material::getSpecular() const{
    return specular;
}

void Material::setSpecular(const double newSpecular){
    specular = newSpecular;
}

double Material::getShininess() const{
    return shininess;
}

void Material::setShininess(const double newShininess){
    shininess = newShininess;
}

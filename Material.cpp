#include "Material.h"

Material::Material() {
    Color defaultColor{1,1,1};
    color = defaultColor;
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200;
    reflectivity = 0;
    transparency = 0;
    refractiveIndex = 1.0;
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

bool operator== (Material& material1, Material& material2){
    using namespace util;
    if ((material1.color == material2.color) &&
        equals(material1.ambient, material2.ambient) &&
        equals(material1.diffuse, material2.diffuse) &&
        equals(material1.specular, material2.specular) &&
        equals(material1.shininess, material2.shininess)) return true;
    else return false;
}

Material& Material::operator=(const Material& original){
    if (this == &original) return *this;
    color = original.color;
    ambient = original.ambient;
    diffuse = original.diffuse;
    specular = original.specular;
    shininess = original.shininess;
    pattern = original.pattern;
    reflectivity = original.reflectivity;
    transparency = original.transparency;
    refractiveIndex = original.refractiveIndex;
    return *this;
}

std::shared_ptr<Pattern> Material::getPattern() const {
    return pattern;
}

void Material::setPattern(std::shared_ptr<Pattern> pattern) {
    this->pattern = pattern;
}

void Material::setReflectivity(const double reflectivity) {
    this->reflectivity = reflectivity;
}

double Material::getReflectivity() const {
    return reflectivity;
}

void Material::setTransparency(const double transparency) {
    this->transparency = transparency;
}

double Material::getTransparency() const {
    return transparency;
}

void Material::setRefractiveIndex(const double index) {
    this->refractiveIndex = index;
}

double Material::getRefractiveIndex() const {
    return refractiveIndex;
}

#include "World.h"

World::World(){
    Tuple lightPosition{-10,10,-10,TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    lights.push_back(light);
    Sphere unitSphere{};
    Sphere halfSphere{};
    Material material{};
    Color sphereColor{0.8, 1, 0.6};
    material.setColor(sphereColor);
    material.setDiffuse(0.7);
    material.setSpecular(0.2);
    unitSphere.setMaterial(material);
    spheres.push_back(unitSphere);
    Transformer scaler{Transformation::scaling, 0.5,0.5,0.5};
    halfSphere.setTransformation(scaler);
    spheres.push_back(halfSphere);
}

bool World::isEmpty() const{
    return spheres.empty();
}

bool World::isDark() const{
    return lights.empty();
}

int World::getNumberOfLights() const{
    return lights.size();
}

Light World::getLight(int i) const{
    return lights.at(i);
}

int World::getNumberOfSpheres() const{
    return spheres.size();
}

Sphere World::getSphere(int i) const{
    return spheres.at(i);
}

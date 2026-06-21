#include "World.h"
#include "Ray.h"
#include "Sphere.h"

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
    shapes.push_back(std::make_unique<Sphere>(unitSphere));
    Transformer scaler{Transformation::scaling, 0.5,0.5,0.5};
    halfSphere.setTransformation(scaler);
    shapes.push_back(std::make_unique<Sphere>(halfSphere));
}

World::World(std::unique_ptr<Shape> shape, Light light) {
    addShape(std::move(shape));
    addLight(light);
}

bool World::isEmpty() const{
    return shapes.empty();
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

void World::addLight(Light light) {
    lights.push_back(std::move(light));
}

int World::getNumberOfShapes() const{
    return shapes.size();
}

Shape& World::getShape(int i) {
    return *shapes.at(i);
}

void World::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

Ray World::generateShadowRay(const Tuple& objectPoint) const {
    Tuple lightPosition = getLight(0).getPosition();
    Tuple vector = lightPosition - objectPoint;
    double distance = vector.magnitude();
    Tuple direction = vector.normalize();
    Tuple origin = objectPoint;
    Ray ray{origin,direction};
    ray.setDistance(distance);
    return ray;
}

Color World::shadeHit(Intersection &intersection, int remainingRecursions) {
    Material material = intersection.getIntersectedShape()->getMaterial();
    const auto& shape = intersection.getIntersectedShape();
    Light light = this->getLight(0);
    Tuple eyeVector = intersection.getEyeVector();
    Tuple normalVector = intersection.getNormalVector();
    Tuple& overIntersectionPoint = intersection.getOverIntersectionPoint();
    Ray shadowRay = generateShadowRay(overIntersectionPoint);
    bool inShadow = isShadowed(shadowRay);
    Color surface = light.light(material,*shape,overIntersectionPoint,eyeVector,normalVector,inShadow);
    Color reflected = this->reflectedColor(intersection, remainingRecursions);
    return surface+reflected;
}

void World::intersect(Ray &ray, IntersectionTracker &tracker) {
    for (const auto& shape : shapes) {
        shape->intersect(ray,tracker);
    }
}

bool World::isShadowed(Ray &ray) {
    IntersectionTracker tracker{};
    intersect(ray, tracker);
    Intersection* hit = tracker.hit();
    if(hit && (hit->getIntersectionTime() < ray.getDistance())) return true;
    else return false;
}

Color World::colorAt(Ray &ray, int remainingRecursions) {
    IntersectionTracker tracker{};
    intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection* hit = tracker.hit();
    if (hit) {
            return shadeHit(*hit, remainingRecursions);
        }
        else {
            Color black{0,0,0};
            return black;
        }
}

Color World::reflectedColor(Intersection &intersection, int remainingRecursions) {
    double objectReflectivy = intersection.getIntersectedShape()->getMaterial().getReflectivity();
    if ((objectReflectivy==0) || (remainingRecursions<1)) {
        return Color{0,0,0};
    }
    else {
        Ray reflectedRay{intersection.getOverIntersectionPoint(),intersection.getReflectionVector()};
        Color color = colorAt(reflectedRay, --remainingRecursions);
        return color*intersection.getIntersectedShape()->getMaterial().getReflectivity();
    }
}

#include "gmock/gmock.h"
#include <cmath>
#include "World.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#define PI 3.14159265
using namespace testing;

class WorldFeature : public Test {

};

//TEST_F(WorldFeature, DISABLED_WorldInitializedEmpty) {
//    World emptyWorld{};

//    ASSERT_THAT(emptyWorld.isEmpty(), true);
//    ASSERT_THAT(emptyWorld.isDark(), true);
//}

TEST_F(WorldFeature, DefaultWorldHasDefaultLight) {
    World world{};
    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightIntensity{1,1,1};
    Light light{lightPosition, lightIntensity};

    ASSERT_THAT(world.getNumberOfLights()== 1, true);
    Light worldLight = world.getLight(0);
    ASSERT_THAT(worldLight == light, true);
}

TEST_F(WorldFeature, DefaultWorldHasDefaultSpheres) {
    World world{};

    Material material{};
    Color sphereColor{0.8, 1, 0.6};
    material.setColor(sphereColor);
    material.setDiffuse(0.7);
    material.setSpecular(0.2);

    Transformer scaler{Transformation::scaling, 0.5,0.5,0.5};

    Material sphereMaterial = world.getShape(0).getMaterial();
    Transformer sphereScaler = world.getShape(1).getTransformation();

    ASSERT_THAT(world.getNumberOfShapes() == 2, true);
    ASSERT_THAT(sphereMaterial == material, true);
}

TEST_F(WorldFeature, IntersectWorldWithRay) {
    World world{};
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);

    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(4));
    ASSERT_THAT(tracker.getIntersectionTime(0), Eq(4));
    ASSERT_THAT(tracker.getIntersectionTime(1), Eq(4.5));
    ASSERT_THAT(tracker.getIntersectionTime(2), Eq(5.5));
    ASSERT_THAT(tracker.getIntersectionTime(3), Eq(6));
}

TEST_F(WorldFeature, ShadingAnIntersection){
    World world{};
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin, rayDirection};
    auto& sphere = world.getShape(0);
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection* hit = tracker.hit();
    Color color = world.shadeHit(*hit);
    Color correctColor{0.38066,0.47583,0.2855};
    ASSERT_THAT(color == correctColor, true);
}

TEST_F(WorldFeature, ColorWhenRayMisses){
    World world{};
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,1,0,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    Color color = world.colorAt(ray);
    Color correctColor{0,0,0};
    ASSERT_THAT(color == correctColor, true);
}

TEST_F(WorldFeature, ColorWhenRayHits) {
    World world{};
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    Color color = world.colorAt(ray);
    Color correctColor{0.38066,0.47583,0.2855};
    ASSERT_THAT(color == correctColor, true);
}

TEST_F(WorldFeature, ColorWithIntersectionBehindRay) {
    World world{};
    auto& outerSphere = world.getShape(0);
    auto& innerSphere = world.getShape(1);
    Material material = outerSphere.getMaterial();
    material.setAmbient(1);
    outerSphere.setMaterial(material);
    material = innerSphere.getMaterial();
    material.setAmbient(1);
    innerSphere.setMaterial(material);
    Tuple rayOrigin{0,0,0.75,TupleType::point};
    Tuple rayDirection{0,0,-1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    Color color = world.colorAt(ray);
    Color correctColor = material.getColor();
    ASSERT_THAT(color == correctColor, true);
}

TEST_F(WorldFeature, NoShadowWhenNothingIsCollinearWithPointAndLight) {
    World world{};
    Tuple point{0,10,0,TupleType::point};
    Ray shadowRay = world.generateShadowRay(point);
    bool isShadowed = world.isShadowed(shadowRay);
    bool correctIsShadowed = false;
    ASSERT_EQ(isShadowed,correctIsShadowed);
}

TEST_F(WorldFeature, ShadowWhenObjectIsBetweenPointAndLight) {
    World world{};
    Tuple point{10,-10,10,TupleType::point};
    Ray shadowRay = world.generateShadowRay(point);
    bool isShadowed = world.isShadowed(shadowRay);
    bool correctIsShadowed = true;
    ASSERT_EQ(isShadowed,correctIsShadowed);
}

TEST_F(WorldFeature, NoShadowWhenObjectIsBehindLight) {
    World world{};
    Tuple point{-20,20,-20,TupleType::point};
    Ray shadowRay = world.generateShadowRay(point);
    bool isShadowed = world.isShadowed(shadowRay);
    bool correctIsShadowed = false;
    ASSERT_EQ(isShadowed,correctIsShadowed);
}

TEST_F(WorldFeature, NoShadowWhenObjectIsBehindPoint) {
    World world{};
    Tuple point{-2,2,-2,TupleType::point};
    Ray shadowRay = world.generateShadowRay(point);
    bool isShadowed = world.isShadowed(shadowRay);
    bool correctIsShadowed = false;
    ASSERT_EQ(isShadowed,correctIsShadowed);
}

TEST_F(WorldFeature, ShadeHitInShadow) {
    Tuple point{0,0,-10,TupleType::point};
    Color lightColor{1,1,1};
    Light light{point, lightColor};
    Sphere sphere1{};
    World world{std::make_unique<Sphere>(sphere1), light};
    Sphere sphere2{};
    Transformer translation{Transformation::translation,0,0,10};
    sphere2.setTransformation(translation);
    world.addShape(std::make_unique<Sphere>(sphere2));
    Tuple rayOrigin{0,0,5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    sphere2.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection intersection = tracker.getIntersection(0);
    Color color = world.shadeHit(intersection);
    Color correctColor{0.1,0.1,0.1};
    ASSERT_THAT(color==correctColor, true);
}

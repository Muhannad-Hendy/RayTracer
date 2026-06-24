#include "gmock/gmock.h"
#include <cmath>
#include "World.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Stripe.h"
#include "testpattern.h"
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


TEST_F(WorldFeature, ReflectedColorForNonreflectiveMaterial) {
    World world{};
    Tuple rayOrigin{0,0,0,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    auto& shape = world.getShape(1);
    Material material{};
    material.setAmbient(1);
    shape.setMaterial(material);
    IntersectionTracker tracker{};
    shape.intersect(ray,tracker);
    Color reflectedColor = world.reflectedColor(*tracker.hit());
    Color correctReflected{0,0,0};
    ASSERT_THAT(reflectedColor==correctReflected,true);
}

TEST_F(WorldFeature, ReflectedColorForReflectiveMaterial) {
    World world{};
    Plane plane{};
    Material planeMaterial{};
    planeMaterial.setReflectivity(0.5);
    plane.setMaterial(planeMaterial);
    Transformer planeTranslation{Transformation::translation,0,-1,0};
    plane.setTransformation(planeTranslation);
    world.addShape(std::make_unique<Plane>(plane));
    Ray ray{Tuple{0,0,-3,TupleType::point},Tuple{0,-std::sqrt(2)/2, std::sqrt(2)/2,TupleType::vector}};
    IntersectionTracker tracker{};
    plane.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Color reflectedColor = world.reflectedColor(*tracker.hit());
    Color correctReflection{0.19033,0.23791,0.14274};
    ASSERT_THAT(reflectedColor==correctReflection,true);
}

TEST_F(WorldFeature, ReflectedColorForReflectiveMaterialShadeHit) {
    World world{};
    Plane plane{};
    Material planeMaterial{};
    planeMaterial.setReflectivity(0.5);
    plane.setMaterial(planeMaterial);
    Transformer planeTranslation{Transformation::translation,0,-1,0};
    plane.setTransformation(planeTranslation);
    world.addShape(std::make_unique<Plane>(plane));
    Ray ray{Tuple{0,0,-3,TupleType::point},Tuple{0,-std::sqrt(2)/2, std::sqrt(2)/2,TupleType::vector}};
    IntersectionTracker tracker{};
    plane.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Color reflectedColor = world.shadeHit(*tracker.hit());
    Color correctReflection{0.87676,0.92434,0.82917};
    ASSERT_THAT(reflectedColor==correctReflection,true);
}


TEST_F(WorldFeature, ColorAtWithMutuallyReflectiveSurfaces) {
    Light light{Tuple{0,0,0,TupleType::point},Color{1,1,1}};
    Plane lower{};
    Material lowerMaterial{};
    lowerMaterial.setReflectivity(1);
    Transformer lowerTranslation{Transformation::translation,0,-1,0};
    lower.setMaterial(lowerMaterial);
    lower.setTransformation(lowerTranslation);
    World world{std::make_unique<Plane>(lower),light};
    Plane upper{};
    Transformer upperTranslation{Transformation::translation,0,1,0};
    upper.setMaterial(lowerMaterial);
    upper.setTransformation(upperTranslation);
    world.addShape(std::make_unique<Plane>(upper));
    Ray ray{Tuple{0,0,0,TupleType::point},Tuple{0,1,0,TupleType::vector}};
    Color color = world.colorAt(ray);
}

TEST_F(WorldFeature, ReflectedColorAtMaximumRecursiveDepth) {
    World world{};
    Plane plane{};
    Material planeMaterial{};
    planeMaterial.setReflectivity(0.5);
    plane.setMaterial(planeMaterial);
    Transformer planeTranslation{Transformation::translation,0,-1,0};
    plane.setTransformation(planeTranslation);
    world.addShape(std::make_unique<Plane>(plane));
    Ray ray{Tuple{0,0,-3,TupleType::point},Tuple{0,-std::sqrt(2)/2, std::sqrt(2)/2,TupleType::vector}};
    IntersectionTracker tracker{};
    plane.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Color reflectedColor = world.reflectedColor(*tracker.hit(),0);
    Color black{0,0,0};
    ASSERT_THAT(reflectedColor==black,true);
}

TEST_F(WorldFeature, RefractedColorWithOpaqueSurface) {
    World world{};
    Ray ray{Tuple{0,0,-5,TupleType::point}, Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);
    Intersection& intersection = tracker.getIntersection(0);
    Color refracted = world.refractedColor(intersection);
    Color black{0,0,0};
    ASSERT_THAT(refracted==black,true);
}

TEST_F(WorldFeature, RefractedColorAtMaximumRecursiveDepth) {
    World world{};
    auto& sphere1 = world.getShape(0);
    auto& material1 = sphere1.getMaterial();
    material1.setTransparency(1);
    material1.setRefractiveIndex(1.5);
    Ray ray{Tuple{0,0,-5,TupleType::point}, Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);
    Intersection& intersection = tracker.getIntersection(0);
    Color refracted = world.refractedColor(intersection,0);
    Color black{0,0,0};
    ASSERT_THAT(refracted==black,true);
}

TEST_F(WorldFeature, RefractedColorUnderTotalInternalReflection) {
    World world{};
    auto& sphere1 = world.getShape(0);
    auto& material1 = sphere1.getMaterial();
    material1.setTransparency(1);
    material1.setRefractiveIndex(1.5);
    Ray ray{Tuple{0,0,std::sqrt(2)/2,TupleType::point}, Tuple{0,1,0,TupleType::vector}};
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection& intersection = tracker.getIntersection(1);
    Color refracted = world.refractedColor(intersection);
    Color black{0,0,0};
    ASSERT_THAT(refracted==black,true);
}

TEST_F(WorldFeature, RefractedColorWithRefractedRay) {
    World world{};
    auto& sphere1 = world.getShape(0);
    auto& material1 = sphere1.getMaterial();
    material1.setAmbient(1);
    TestPattern test{};
    material1.setPattern(std::make_shared<TestPattern>(test));
    auto& sphere2 = world.getShape(1);
    auto& material2 = sphere2.getMaterial();
    material2.setTransparency(1);
    material2.setRefractiveIndex(1.5);
    Ray ray{Tuple{0,0,0.1,TupleType::point}, Tuple{0,1,0,TupleType::vector}};
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection& intersection = tracker.getIntersection(2);
    Color refracted = world.refractedColor(intersection);
    Color correctColor{0,0.99887,0.04721};
    ASSERT_THAT(refracted==correctColor,true);
}

TEST_F(WorldFeature, shadeHitWithTransparentMaterial) {
    World world{};
    Plane floor{};
    Transformer translator{Transformation::translation,0,-1,0};
    floor.setTransformation(translator);
    auto& floorMaterial = floor.getMaterial();
    floorMaterial.setTransparency(0.5);
    floorMaterial.setRefractiveIndex(1.5);
    world.addShape(std::make_unique<Plane>(floor));
    Sphere ball{};
    Transformer ballTransformer{Transformation::translation,0,-3.5,-0.5};
    ball.setTransformation(ballTransformer);
    auto& ballMaterial = ball.getMaterial();
    ballMaterial.setColor(Color{1,0,0});
    ballMaterial.setAmbient(0.5);
    world.addShape(std::make_unique<Sphere>(ball));
    Ray ray{Tuple{0,0,-3,TupleType::point}, Tuple{0,-std::sqrt(2)/2, std::sqrt(2)/2,TupleType::vector}};
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);
    tracker.prepComputations(ray);
    auto& intersection = tracker.getIntersection(0);
    Color color = world.shadeHit(intersection);
    Color correctColor{0.93642,0.68642,0.68642};
    ASSERT_THAT(color==correctColor,true);
}

TEST_F(WorldFeature, shadeHitWithReflectiveTransparentMaterial) {
    World world{};
    Ray ray{Tuple{0,0,-3,TupleType::point}, Tuple{0,-std::sqrt(2)/2,std::sqrt(2)/2,TupleType::vector}};
    Plane floor{};
    Transformer floorTransform{Transformation::translation,0,-1,0};
    floor.setTransformation(floorTransform);
    auto& floorMaterial = floor.getMaterial();
    floorMaterial.setReflectivity(0.5);
    floorMaterial.setTransparency(0.5);
    floorMaterial.setRefractiveIndex(1.5);
    world.addShape(std::make_unique<Plane>(floor));
    Sphere ball{};
    Transformer ballTransform{Transformation::translation,0,-3.5,-0.5};
    ball.setTransformation(ballTransform);
    auto& ballMaterial = ball.getMaterial();
    ballMaterial.setColor(Color{1,0,0});
    ballMaterial.setAmbient(0.5);
    world.addShape(std::make_unique<Sphere>(ball));
    IntersectionTracker tracker{};
    world.intersect(ray,tracker);
    tracker.prepComputations(ray);
    auto& intersection = tracker.getIntersection(0);
    Color color = world.shadeHit(intersection);
    Color correctColor{0.93391,0.69643,0.69243};
    ASSERT_THAT(color==correctColor,true);
}

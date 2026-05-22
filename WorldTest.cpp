#include "gmock/gmock.h"
#include <cmath>
#include "World.h"
#include "Light.h"
#include "Ray.h"
#define PI 3.14159265
using namespace testing;

class WorldFeature : public Test {

};

TEST_F(WorldFeature, DISABLED_WorldInitializedEmpty) {
    World emptyWorld{};

    ASSERT_THAT(emptyWorld.isEmpty(), true);
    ASSERT_THAT(emptyWorld.isDark(), true);
}

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

    Material sphereMaterial = world.getSphere(0).getMaterial();
    Transformer sphereScaler = world.getSphere(1).getTransformation();

    ASSERT_THAT(world.getNumberOfSpheres() == 2, true);
    ASSERT_THAT(sphereMaterial == material, true);
}

TEST_F(WorldFeature, IntersectWorldWithRay) {
    World world{};
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    ray.intersect(world);

    ASSERT_THAT(ray.getNumberOfIntersections(), Eq(4));
    ASSERT_THAT(ray.getIntersectionTime(0), Eq(4));
    ASSERT_THAT(ray.getIntersectionTime(1), Eq(4.5));
    ASSERT_THAT(ray.getIntersectionTime(2), Eq(5.5));
    ASSERT_THAT(ray.getIntersectionTime(3), Eq(6));
}

TEST_F(WorldFeature, ShadingAnIntersection){
    World world{};
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin, rayDirection};
    Sphere sphere = world.getSphere(0);
    ray.intersect(sphere);
    ray.prepComputations();
    Intersection* hit = ray.getIntersectionTracker().hit();
    Color color = world.shadeHit(*hit);
    Color correctColor{0.38066,0.47583,0.2855};
    ASSERT_THAT(color == correctColor, true);
}

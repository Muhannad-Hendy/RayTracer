#include "gmock/gmock.h"
#include "Ray.h"
#include "Sphere.h"

using namespace testing;

class RaySphereIntersectionFeature : public Test {

};

TEST_F(RaySphereIntersectionFeature, CreatingAndQueryingRay){
    Tuple origin{1,2,3,TupleType::point};
    Tuple direction{4,5,6,TupleType::vector};

    Ray ray{origin, direction};
    Tuple trueOrigin = ray.getOrigin();
    Tuple trueDirection = ray.getDirection();

    ASSERT_THAT(trueOrigin == origin, true);
    ASSERT_THAT(trueDirection== direction, true);
}

TEST_F(RaySphereIntersectionFeature, ComputingPointFromDistance){
    Tuple origin{2,3,4,TupleType::point};
    Tuple direction{1,0,0,TupleType::vector};
    Ray ray{origin,direction};
    Tuple position1 = ray.locate(0);
    Tuple truePosition1{2,3,4,TupleType::point};
    Tuple position2 = ray.locate(1);
    Tuple truePosition2{3,3,4,TupleType::point};
    Tuple position3 = ray.locate(-1);
    Tuple truePosition3{1,3,4,TupleType::point};
    Tuple position4 = ray.locate(2.5);
    Tuple truePosition4{4.5,3,4,TupleType::point};

    ASSERT_THAT(position1 == truePosition1, true);
    ASSERT_THAT(position2 == truePosition2, true);
    ASSERT_THAT(position3 == truePosition3, true);
    ASSERT_THAT(position4 == truePosition4, true);
}

TEST_F(RaySphereIntersectionFeature, RayIntersectsSphereAtTwoPoints){
    Tuple origin{0,0,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    ray.intersect(sphere);
    ASSERT_THAT(ray.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(ray.getIntersectionDistance(0), Eq(4));
    ASSERT_THAT(ray.getIntersectionDistance(1), Eq(6));
}

TEST_F(RaySphereIntersectionFeature, RayIntersectsSphereAtTangent){
    Tuple origin{0,1,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    ray.intersect(sphere);
    ASSERT_THAT(ray.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(ray.getIntersectionDistance(0), Eq(5));
    ASSERT_THAT(ray.getIntersectionDistance(1), Eq(5));
}

TEST_F(RaySphereIntersectionFeature, RayMissesSphere){
    Tuple origin{0,2,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    ray.intersect(sphere);
    ASSERT_THAT(ray.getNumberOfIntersections(), Eq(0));
}

TEST_F(RaySphereIntersectionFeature, RayOriginatesInsideSphere){
    Tuple origin{0,0,0,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    ray.intersect(sphere);
    ASSERT_THAT(ray.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(ray.getIntersectionDistance(0), Eq(-1));
    ASSERT_THAT(ray.getIntersectionDistance(1), Eq(1));
}

TEST_F(RaySphereIntersectionFeature, SphereIsBehindRay){
    Tuple origin{0,0,5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    ray.intersect(sphere);
    ASSERT_THAT(ray.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(ray.getIntersectionDistance(0), Eq(-6));
    ASSERT_THAT(ray.getIntersectionDistance(1), Eq(-4));
}

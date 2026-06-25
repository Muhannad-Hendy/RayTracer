#include "gmock/gmock.h"
#include "cube.h"

using namespace testing;

class CubesFeature : public Test {

};

TEST_F(CubesFeature, RayIntersectsCube) {
    //Ran all tests on page 169.
    Cube cube{};
    Tuple rayOrigin{0, 0.5, 0,TupleType::point};
    Tuple rayDirection{0, 0, 1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cube.intersect(ray,tracker);
    ASSERT_EQ(tracker.getNumberOfIntersections(),2);
    ASSERT_DOUBLE_EQ(tracker.getIntersectionTime(0),-1);
    ASSERT_DOUBLE_EQ(tracker.getIntersectionTime(1),1);
}

TEST_F(CubesFeature, RayMissesCube) {
    //Ran all tests on page 172.
    Cube cube{};
    Tuple rayOrigin{2, 2, 0,TupleType::point};
    Tuple rayDirection{-1, 0, 0,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cube.intersect(ray,tracker);
    ASSERT_EQ(tracker.getNumberOfIntersections(),0);
}

TEST_F(CubesFeature, NormalOnSurfaceOfCube) {
    //Ran all tests on page 174.
    Cube cube{};
    Tuple point{-1, -1, -1,TupleType::point};
    Tuple normal = cube.normalAt(point);
    Tuple correctNormal{-1, 0, 0, TupleType::vector};
    ASSERT_THAT(normal==correctNormal,true);
}

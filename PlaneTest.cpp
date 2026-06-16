#include "gmock/gmock.h"
#include "Plane.h"

using namespace testing;

class PlanesFeature : public Test {

};

TEST_F(PlanesFeature, NormalOfPlaneIsConstantEverywhere) {
    Plane plane{};
    Tuple point1{0,0,0,TupleType::point};
    Tuple point2{10,0,-10,TupleType::point};
    Tuple point3{-5,0,150,TupleType::point};
    Tuple normal1 = plane.normalAt(point1);
    Tuple normal2 = plane.normalAt(point2);
    Tuple normal3 = plane.normalAt(point3);
    Tuple correctNormal{0,1,0,TupleType::vector};
    ASSERT_THAT(normal1==correctNormal, true);
    ASSERT_THAT(normal2==correctNormal, true);
    ASSERT_THAT(normal3==correctNormal, true);
}

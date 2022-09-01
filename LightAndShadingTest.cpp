#include "gmock/gmock.h"
#include "Sphere.h"
#include "Tuple.h"

using namespace testing;

class LightAndShadingFeature : public Test {
public:
    double coordinateValue{sqrt(3) / 3};
};

TEST_F(LightAndShadingFeature, NormalOnSphereAtPointOnXAxis){
    Sphere sphere{};
    Tuple point{1,0,0,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{1,0,0,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalOnSphereAtPointOnYAxis){
    Sphere sphere{};
    Tuple point{0,1,0,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{0,1,0,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalOnSphereAtPointOnZAxis){
    Sphere sphere{};
    Tuple point{0,0,1,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{0,0,1,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalOnSphereAtNonAxialPoint){
    Sphere sphere{};
    Tuple point{coordinateValue,coordinateValue,coordinateValue,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{coordinateValue,coordinateValue,coordinateValue,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalVectorIsNormalized){
    Sphere sphere{};
    Tuple point{coordinateValue,coordinateValue,coordinateValue,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple normalizedVector = normalVector.normalize();

    ASSERT_THAT(normalVector == normalizedVector, true);
}

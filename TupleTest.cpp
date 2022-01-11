#include "gmock/gmock.h"
#include "Tuple.h"
#include "Utilities.h"

using namespace testing;

class TupleFeature : public Test {
public:

    Tuple pointTuple{4.3, -4.2, 3.1, TupleType::point};
    Tuple vectorTuple{4.3, -4.2, 3.1, TupleType::vector};
};

TEST_F(TupleFeature, TupleStoresXYZCoordinatesAndIsPoint) {
    ASSERT_THAT(pointTuple.getXValue(), Eq(4.3));
    ASSERT_THAT(pointTuple.getYValue(), Eq(-4.2));
    ASSERT_THAT(pointTuple.getZValue(), Eq(3.1));
    ASSERT_THAT(pointTuple.getWValue(), Eq(1.0));
}

TEST_F(TupleFeature, TupleStoresXYZCoordinatesAndIsVector){
    ASSERT_THAT(vectorTuple.getXValue(), Eq(4.3));
    ASSERT_THAT(vectorTuple.getYValue(), Eq(-4.2));
    ASSERT_THAT(vectorTuple.getZValue(), Eq(3.1));
    ASSERT_THAT(vectorTuple.getWValue(), Eq(0.0));
}

TEST_F(TupleFeature, PointHasWValuesEqualsOne){
    Tuple point{4, -4, 3, TupleType::point};
    ASSERT_THAT(point.getWValue(), Eq(1.0));
}

TEST_F(TupleFeature, VectorHasWValuesEqualsZero){
    Tuple point{4.3, -4.2, 3.1, TupleType::vector};
    ASSERT_THAT(point.getWValue(), Eq(0.0));
}

TEST_F(TupleFeature, CheckTuplesForEquality){
    Tuple point1{10, 15, -7, TupleType::point};
    Tuple point2{10, 15, -7, TupleType::point};
    Tuple point3{10, 5, -7, TupleType::point};
    Tuple vector{10, 15, -7, TupleType::vector};
    ASSERT_THAT(point1 == point2, true);
    ASSERT_THAT(point1 == point3, false);
    ASSERT_THAT(point1 == vector, false);
}

TEST_F(TupleFeature, AdditionOfTwoTuples){
    Tuple point{3, -2, 5, TupleType::point};
    Tuple vector{-2, 3, 1, TupleType::vector};
    Tuple correctSum{1, 1, 6, TupleType::point};
    Tuple sum = point + vector;
    ASSERT_THAT(correctSum == sum, true);
}

TEST_F(TupleFeature, SubtractionOfTwoPoints){
    Tuple pointA{3, 2, 1, TupleType::point};
    Tuple pointB{5, 6, 7, 1};
    Tuple correctSum{-2, -4, -6, TupleType::vector};
    Tuple sum = pointA - pointB;
    ASSERT_THAT(correctSum == sum, true);
}

TEST_F(TupleFeature, SubtractionOfVectorFromPoint){
    Tuple point{3, 2, 1, TupleType::point};
    Tuple vector{5, 6, 7, TupleType::vector};
    Tuple correctSum{-2, -4, -6, TupleType::point};
    Tuple sum = point - vector;
    ASSERT_THAT(correctSum == sum, true);
}

TEST_F(TupleFeature, SubtractionOfVectorFromVector){
    Tuple vectorA{3, 2, 1, TupleType::vector};
    Tuple vectorB{5, 6, 7, TupleType::vector};
    Tuple correctSum{-2, -4, -6, TupleType::vector};
    Tuple sum = vectorA - vectorB;
    ASSERT_THAT(correctSum == sum, true);
}

TEST_F(TupleFeature, SubtractionOfVectorFromZeroVector){
    Tuple zeroVector{0, 0, 0, 0};
    Tuple vector{1, -2, 3, 0};
    Tuple correctSum{-1, 2, -3, 0};
    Tuple sum = zeroVector - vector;
    ASSERT_THAT(correctSum == sum, true);
}

TEST_F(TupleFeature, NegatingTuple){
    Tuple tuple{1, -2, 3, -4};
    Tuple correctValue{-1, 2, -3, 4};
    Tuple tupleNegated = (-tuple);
    ASSERT_THAT(correctValue == tupleNegated, true);
}

TEST_F(TupleFeature, MultiplyingTupleByScalar){
    Tuple tuple{1, -2, 3, -4};
    double factor{3.5};
    Tuple correctValue{3.5, -7, 10.5, -14};
    Tuple scaledTuple = tuple * factor;
    ASSERT_THAT(correctValue == scaledTuple, true);
}

TEST_F(TupleFeature, DividingTupleByScalar){
    Tuple tuple{1, -2, 3, -4};
    double factor{2.0};
    Tuple correctValue{0.5, -1, 1.5, -2};
    Tuple scaledTuple = tuple / factor;
    ASSERT_THAT(correctValue == scaledTuple, true);
}

TEST_F(TupleFeature, ComputingMagnitudeOfVector){
    Tuple vector1{1, 0, 0, TupleType::vector};
    Tuple vector2{0, 1, 0, TupleType::vector};
    Tuple vector3{0, 0, 1, TupleType::vector};
    Tuple vector4{1, 2, 3, TupleType::vector};
    Tuple vector5{-1, -2, -3, TupleType::vector};

    ASSERT_THAT(vector1.magnitude(), Eq(1.0));
    ASSERT_THAT(vector2.magnitude(), Eq(1.0));
    ASSERT_THAT(vector3.magnitude(), Eq(1.0));
    ASSERT_THAT(util::equals(vector4.magnitude(), 3.74165738677), true);
    ASSERT_THAT(util::equals(vector5.magnitude(), 3.74165738677), true);

}

TEST_F(TupleFeature, ComputingNormalVector){
    Tuple vector1{4, 0, 0, TupleType::vector};
    Tuple correctNormal1{1, 0, 0, 0};
    Tuple vector1Normalized = vector1.normalize();
    Tuple vector2{1, 2, 3, TupleType::vector};
    Tuple correctNormal2{0.26726, 0.53452, 0.80178, 0};
    Tuple vector2Normalized = vector2.normalize();

    ASSERT_THAT(correctNormal1 == vector1Normalized, true);
    ASSERT_THAT(correctNormal2 == vector2Normalized, true);
}

TEST_F(TupleFeature, DotProductOfTwoTuples){
    Tuple a{1, 2, 3, 0};
    Tuple b{2, 3, 4, 0};
    double correctValue{20.0};
    double aDotB = a.dot(b);
    ASSERT_THAT(correctValue == aDotB, true);
}

TEST_F(TupleFeature, CrossProductOfTwoVectors){
    Tuple a{1, 2, 3, 0};
    Tuple b{2, 3, 4, 0};
    Tuple correctACrossB{-1, 2, -1, 0};
    Tuple correctBCrossA{1, -2, 1, 0};
    Tuple ACrossB = a.cross(b);
    Tuple BCrossA = b.cross(a);

    ASSERT_THAT(correctACrossB == ACrossB, true);
    ASSERT_THAT(correctBCrossA == BCrossA, true);
}

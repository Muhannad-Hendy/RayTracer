#include "gmock/gmock.h"
#include "Tuple.h"

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

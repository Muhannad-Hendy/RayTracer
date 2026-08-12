#include "gmock/gmock.h"
#include "cone.h"

using namespace testing;

class ConeIntersection : public::testing::TestWithParam<std::tuple<Tuple,Tuple,int,double,double>> {

};

TEST_P(ConeIntersection, IntersectingConeWithRay) {
    auto [rayOrigin, rayDirection, numberOfIntersections, time0, time1] = GetParam();
    Cone cone{};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cone.intersect(ray,tracker);
    EXPECT_EQ(tracker.getNumberOfIntersections(),numberOfIntersections);
    EXPECT_TRUE(util::equals(tracker.getIntersectionTime(0), time0));
    EXPECT_TRUE(util::equals(tracker.getIntersectionTime(1), time1));

}

INSTANTIATE_TEST_SUITE_P(
    IntersectionScenarios,
    ConeIntersection,
    ::testing::Values(
        std::make_tuple(Tuple{0, 0, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 2,5,5),
        std::make_tuple(Tuple{0, 0, -5,TupleType::point}, Tuple{1, 1, 1,TupleType::vector}.normalize(), 2,8.66025,8.66025),
        std::make_tuple(Tuple{1, 1, -5,TupleType::point}, Tuple{-0.5, -1, 1,TupleType::vector}.normalize(), 2,4.55006,49.44994)
    )
);

class ConeIntersectionParallelRay : public::Test {

};

TEST_F(ConeIntersectionParallelRay, IntersectingConeWithRayParallelToOneOfItsHalves) {
    Cone cone{};
    Tuple rayDirection = Tuple{0,1,1,TupleType::vector}.normalize();
    Ray ray{Tuple{0,0,-1,TupleType::point},rayDirection};
    IntersectionTracker tracker{};
    cone.intersect(ray,tracker);
    ASSERT_EQ(tracker.getNumberOfIntersections(),1);
    EXPECT_TRUE(util::equals(tracker.getIntersectionTime(0), 0.35355));}

class ConeWithCaps : public::testing::TestWithParam<std::tuple<Tuple,Tuple,int>> {

};

TEST_P(ConeWithCaps, IntersectingConeEndCaps) {
    auto[rayOrigin,rayDirection,numberOfIntersections] = GetParam();
    Cone cone{};
    cone.setMinimum(-0.5);
    cone.setMaximum(0.5);
    cone.setClosed(true);
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cone.intersect(ray,tracker);
    ASSERT_EQ(tracker.getNumberOfIntersections(),numberOfIntersections);
}

INSTANTIATE_TEST_SUITE_P(
        VariousCapIntersections,
        ConeWithCaps,
        ::testing::Values(
            std::make_tuple(Tuple{0, 0, -5,TupleType::point}, Tuple{0, 1, 0,TupleType::vector}.normalize(), 0),
            std::make_tuple(Tuple{0, 0, -0.25,TupleType::point}, Tuple{0, 1, 1,TupleType::vector}.normalize(), 2),
            std::make_tuple(Tuple{0, 0, -0.25,TupleType::point}, Tuple{0, 1, 0,TupleType::vector}.normalize(), 4)
            ));

class ConeNormal : public::testing::TestWithParam<std::tuple<Tuple,Tuple>> {

};

TEST_P(ConeNormal, ComputingNormalVectorOnCone) {
    auto [point,trueNormal] = GetParam();
    Cone cone{};
    Tuple normal = cone.normalAt(point);
    EXPECT_TRUE(normal==trueNormal);
}

INSTANTIATE_TEST_SUITE_P(
        NormalsOnVariousPoints,
        ConeNormal,
        ::testing::Values(
            std::make_tuple(Tuple{0, 0, 0,TupleType::point}, Tuple{0, 0, 0,TupleType::vector}.normalize()),
            std::make_tuple(Tuple{1, 1, 1,TupleType::point}, Tuple{1, -std::sqrt(2), 1,TupleType::vector}.normalize()),
            std::make_tuple(Tuple{-1, -1, 0,TupleType::point}, Tuple{-1, 1, 0,TupleType::vector}.normalize())
            ));

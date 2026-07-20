#include "gmock/gmock.h"
#include "cylinder.h"

using namespace testing;

class CylinderFeature : public ::testing::TestWithParam<std::tuple<Tuple, Tuple, int, double, double>> {

};

TEST_P(CylinderFeature, RayMissesCylinder) {
    auto [rayOrigin, rayDirection, numberOfIntersections, time0, time1] = GetParam();
    Cylinder cylinder{};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cylinder.intersect(ray,tracker);
    EXPECT_EQ(tracker.getNumberOfIntersections(),numberOfIntersections);

}

INSTANTIATE_TEST_SUITE_P(
    VariousMissingRays,
    CylinderFeature,
    ::testing::Values(
            std::make_tuple(Tuple{1,0,0,TupleType::point}, Tuple{0,1,0,TupleType::vector}.normalize(), 0,0,0),
        std::make_tuple(Tuple{0,0,0,TupleType::point}, Tuple{0,1,0,TupleType::vector}.normalize(), 0,0,0),
        std::make_tuple(Tuple{0,0,-5,TupleType::point}, Tuple{1,1,1,TupleType::vector}.normalize(), 0,0,0)
    )
);

TEST_P(CylinderFeature, RayIntersectsCylinder) {
    auto [rayOrigin, rayDirection, numberOfIntersections, time0, time1] = GetParam();
    Cylinder cylinder{};
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cylinder.intersect(ray,tracker);
    EXPECT_EQ(tracker.getNumberOfIntersections(),numberOfIntersections);
    EXPECT_TRUE(util::equals(tracker.getIntersectionTime(0), time0));
    EXPECT_TRUE(util::equals(tracker.getIntersectionTime(1), time1));
}

INSTANTIATE_TEST_SUITE_P(
    VariousIntersectingRays,
    CylinderFeature,
    ::testing::Values(
            std::make_tuple(Tuple{1, 0, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 2,5,5),
        std::make_tuple(Tuple{0, 0, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 2,4,6),
        std::make_tuple(Tuple{0.5, 0, -5,TupleType::point}, Tuple{0.1, 1, 1,TupleType::vector}.normalize(), 2,6.80798,7.08872)
    )
);

class CylinderNormalTest : public::testing::TestWithParam<std::tuple<Tuple,Tuple>> {

};

TEST_P(CylinderNormalTest, NormalVectorOnCylinder) {
    auto [point, expectedNormal] = GetParam();
    Cylinder cylinder{};
    Tuple normal = cylinder.normalAt(point);
    EXPECT_TRUE(normal==expectedNormal);
}

INSTANTIATE_TEST_SUITE_P(
        NormalAtDifferentPoints,
        CylinderNormalTest,
        ::testing::Values(
            std::make_tuple(Tuple{1, 0, 0,TupleType::point}, Tuple{1, 0, 0,TupleType::vector}),
            std::make_tuple(Tuple{0, 5, -1,TupleType::point}, Tuple{0, 0, -1,TupleType::vector}),
            std::make_tuple(Tuple{0, -2, 1,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}),
            std::make_tuple(Tuple{-1, 1, 0,TupleType::point}, Tuple{-1, 0, 0,TupleType::vector})
            ));

class CylinderLimits : public Test {

};

TEST_F(CylinderLimits, DefaultMinimumAndMaximumForCylinder) {
    Cylinder cylinder{};
    EXPECT_DOUBLE_EQ(cylinder.getMinimum(), -std::numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(cylinder.getMaximum(), std::numeric_limits<double>::infinity());
}

TEST_F(CylinderLimits, DefaultClosedValueForCylinder) {
    Cylinder cylinder{};
    bool closed = cylinder.isClosed();
    ASSERT_EQ(closed,false);
}

class TruncatedCylinderIntersection : public::testing::TestWithParam<std::tuple<Tuple, Tuple, int>> {

};

TEST_P(TruncatedCylinderIntersection, IntersectingConstrainedCylinder) {
    auto [rayOrigin,rayDirection, exptectedIntersections] = GetParam();
    Cylinder cylinder{};
    cylinder.setMaximum(2);
    cylinder.setMinimum(1);
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cylinder.intersect(ray,tracker);
    EXPECT_EQ(tracker.getNumberOfIntersections(), exptectedIntersections);
}

INSTANTIATE_TEST_SUITE_P(
        VariousTruncatedIntersections,
        TruncatedCylinderIntersection,
        ::testing::Values(
            std::make_tuple(Tuple{0, 1.5, 0,TupleType::point}, Tuple{0.1, 1, 0,TupleType::vector}.normalize(), 0),
            std::make_tuple(Tuple{0, 3, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 0),
            std::make_tuple(Tuple{0, 0, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 0),
            std::make_tuple(Tuple{0, 2, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 0),
            std::make_tuple(Tuple{0, 1, -5,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 0),
            std::make_tuple(Tuple{0, 1.5, -2,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}.normalize(), 2)
            ));

class CylinderWithCapsIntersection : public::testing::TestWithParam<std::tuple<Tuple, Tuple, int>> {

};

TEST_P(CylinderWithCapsIntersection, IntersectingCapsOfClosedCylinder) {
    auto [rayOrigin,rayDirection,expectedIntersections] = GetParam();
    Cylinder cylinder{};
    cylinder.setMaximum(2);
    cylinder.setMinimum(1);
    cylinder.setClosed(true);
    Ray ray{rayOrigin,rayDirection};
    IntersectionTracker tracker{};
    cylinder.intersect(ray,tracker);
    EXPECT_EQ(tracker.getNumberOfIntersections(), expectedIntersections);
}

INSTANTIATE_TEST_SUITE_P(
        VariousCylinderWithCapsIntersections,
        CylinderWithCapsIntersection,
        ::testing::Values(
            std::make_tuple(Tuple{0, 3, 0,TupleType::point}, Tuple{0, -1, 0,TupleType::vector}.normalize(), 2),
            std::make_tuple(Tuple{0, 3, -2,TupleType::point}, Tuple{0, -1, 2,TupleType::vector}.normalize(), 2),
            std::make_tuple(Tuple{0, 4, -2,TupleType::point}, Tuple{0, -1, 1,TupleType::vector}.normalize(), 2),
            std::make_tuple(Tuple{0, 0, -2,TupleType::point}, Tuple{0, 1, 2,TupleType::vector}.normalize(), 2),
            std::make_tuple(Tuple{0, -1, -2,TupleType::point}, Tuple{0, 1, 1,TupleType::vector}.normalize(), 2)
            ));

class CappedCylinderNormals : public::testing::TestWithParam<std::tuple<Tuple, Tuple>> {

};

TEST_P(CappedCylinderNormals, NormalVectorOnCylinderEndCaps) {
    auto [point, correctNormal] = GetParam();
    Cylinder cylinder{};
    cylinder.setMinimum(1);
    cylinder.setMaximum(2);
    cylinder.setClosed(true);
    Tuple normal = cylinder.normalAt(point);
    EXPECT_TRUE(normal==correctNormal);
}

INSTANTIATE_TEST_SUITE_P(
        NormalAtDifferentPointsOnCylinder,
        CappedCylinderNormals,
        ::testing::Values(
            std::make_tuple(Tuple{0, 1, 0,TupleType::point}, Tuple{0, -1, 0,TupleType::vector}),
            std::make_tuple(Tuple{0.5, 1, 0,TupleType::point}, Tuple{0, -1, 0,TupleType::vector}),
            std::make_tuple(Tuple{0, 1, 0.5,TupleType::point}, Tuple{0, -1, 0,TupleType::vector}),
            std::make_tuple(Tuple{0, 2, 0,TupleType::point}, Tuple{0, 1, 0,TupleType::vector}),
            std::make_tuple(Tuple{0.5, 2, 0,TupleType::point}, Tuple{0, 1, 0,TupleType::vector}),
            std::make_tuple(Tuple{0, 2, 0.5,TupleType::point}, Tuple{0, 1, 0,TupleType::vector})
            ));

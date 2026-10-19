#include "gmock/gmock.h"
#include "csg.h"
#include "Sphere.h"
#include "cube.h"

using namespace testing;

class CSGExposer : public CSG {
public:
    using CSG::CSG;
    using CSG::localIntersect;
};

class CSGFeature : public Test {

};

TEST_F(CSGFeature, CSGCreatedWithOperationAndTwoShapes) {
    auto spherePointer = std::make_unique<Sphere>();
    Shape* sphereRaw = spherePointer.get();
    auto cubePointer = std::make_unique<Cube>();
    Shape* cubeRaw = cubePointer.get();
    CSG construction{Operation::Union,std::move(spherePointer),std::move(cubePointer)};

    auto operation = construction.getOperation();
    auto left = construction.getLeftShape();
    auto right = construction.getRightShape();
    auto leftParent = left->getParent();
    auto rightParent = right->getParent();

    ASSERT_EQ(operation,Operation::Union);
    ASSERT_THAT(left==sphereRaw,true);
    ASSERT_THAT(right==cubeRaw,true);
    ASSERT_THAT(*leftParent==construction,true);
    ASSERT_THAT(*rightParent==construction,true);
}

TEST_F(CSGFeature, RayMissesCSGObject) {
    CSGExposer csg{Operation::Union,std::make_unique<Sphere>(Sphere{}),std::make_unique<Cube>(Cube{})};
    Ray ray{Tuple{0, 2, -5,TupleType::point},Tuple{0, 0, 1,TupleType::vector}};
    IntersectionTracker tracker{};
    csg.localIntersect(ray,tracker);
    ASSERT_EQ(tracker.getNumberOfIntersections(),0);
}

TEST_F(CSGFeature, RayHitsCSGObject) {
    auto sphere1 = std::make_unique<Sphere>(Sphere{});
    auto s1Pointer = sphere1.get();
    auto sphere2 = std::make_unique<Sphere>(Sphere{});
    auto s2Pointer = sphere2.get();
    Transformer translator{Transformation::translation,0,0,0.5};
    sphere2->setTransformation(translator);
    CSGExposer csg{Operation::Union,std::move(sphere1),std::move(sphere2)};
    Ray ray{Tuple{0, 0, -5,TupleType::point},Tuple{0, 0, 1,TupleType::vector}};
    IntersectionTracker tracker{};
    csg.localIntersect(ray,tracker);
    ASSERT_EQ(tracker.getNumberOfIntersections(),2);
    ASSERT_EQ(tracker.getIntersectionTime(0),4);
    ASSERT_THAT(&tracker.getIntersectedObject(0)==s1Pointer,true);
    ASSERT_EQ(tracker.getIntersectionTime(1),6.5);
    ASSERT_THAT(&tracker.getIntersectedObject(1)==s2Pointer,true);
}

class CSGUnion : public::testing::TestWithParam<std::tuple<bool,bool,bool,bool>> {

};

TEST_P(CSGUnion, EvaluatingRuleForCSGUnionOperation) {
    auto [leftHit, insideLeft, insideRight, correctResult] = GetParam();
    auto spherePointer = std::make_unique<Sphere>();
    auto cubePointer = std::make_unique<Cube>();
    CSG construction{Operation::Union,std::move(spherePointer),std::move(cubePointer)};
    bool result = construction.intersectionAllowed(leftHit,insideLeft,insideRight);
    EXPECT_EQ(result,correctResult);
}

INSTANTIATE_TEST_SUITE_P(
        IntersectionScenarios,
        CSGUnion,
        ::testing::Values(
            std::make_tuple(true,true,true,false),
            std::make_tuple(true,true,false,true),
            std::make_tuple(true,false,true,false),
            std::make_tuple(true,false,false,true),
            std::make_tuple(false,true,true,false),
            std::make_tuple(false,true,false,false),
            std::make_tuple(false,false,true,true),
            std::make_tuple(false,false,false,true)
            )

        );

class CSGIntersection : public::testing::TestWithParam<std::tuple<bool,bool,bool,bool>> {

};

TEST_P(CSGIntersection, EvaluatingRuleForCSGIntersectionOperation) {
    auto [leftHit, insideLeft, insideRight, correctResult] = GetParam();
    auto spherePointer = std::make_unique<Sphere>();
    auto cubePointer = std::make_unique<Cube>();
    CSG construction{Operation::Intersection,std::move(spherePointer),std::move(cubePointer)};
    bool result = construction.intersectionAllowed(leftHit,insideLeft,insideRight);
    EXPECT_EQ(result,correctResult);
}

INSTANTIATE_TEST_SUITE_P(
        IntersectionScenarios,
        CSGIntersection,
        ::testing::Values(
            std::make_tuple(true,true,true,true),
            std::make_tuple(true,true,false,false),
            std::make_tuple(true,false,true,true),
            std::make_tuple(true,false,false,false),
            std::make_tuple(false,true,true,true),
            std::make_tuple(false,true,false,true),
            std::make_tuple(false,false,true,false),
            std::make_tuple(false,false,false,false)
            )

        );

class CSGDifference : public::testing::TestWithParam<std::tuple<bool,bool,bool,bool>> {

};

TEST_P(CSGDifference, EvaluatingRuleForCSGDifferenceOperation) {
    auto [leftHit, insideLeft, insideRight, correctResult] = GetParam();
    auto spherePointer = std::make_unique<Sphere>();
    auto cubePointer = std::make_unique<Cube>();
    CSG construction{Operation::Difference,std::move(spherePointer),std::move(cubePointer)};
    bool result = construction.intersectionAllowed(leftHit,insideLeft,insideRight);
    EXPECT_EQ(result,correctResult);
}

INSTANTIATE_TEST_SUITE_P(
        IntersectionScenarios,
        CSGDifference,
        ::testing::Values(
            std::make_tuple(true,true,true,false),
            std::make_tuple(true,true,false,true),
            std::make_tuple(true,false,true,false),
            std::make_tuple(true,false,false,true),
            std::make_tuple(false,true,true,true),
            std::make_tuple(false,true,false,true),
            std::make_tuple(false,false,true,false),
            std::make_tuple(false,false,false,false)
            )

        );

class CSGFiltering : public::testing::TestWithParam<std::tuple<Operation,std::vector<double>>> {

};

TEST_P(CSGFiltering, FilteringListOfIntersections) {
    auto [operation, trueResults] = GetParam();
    auto spherePointer = std::make_unique<Sphere>();
    auto sphereRaw = spherePointer.get();
    auto cubePointer = std::make_unique<Cube>();
    auto cubeRaw = cubePointer.get();
    CSG construction{operation,std::move(spherePointer),std::move(cubePointer)};
    IntersectionTracker tracker{};
    tracker.addIntersection(1,*sphereRaw);
    tracker.addIntersection(2,*cubeRaw);
    tracker.addIntersection(3,*sphereRaw);
    tracker.addIntersection(4,*cubeRaw);
    IntersectionTracker original{tracker};
    construction.filterIntersections(tracker);
    EXPECT_EQ(tracker.getNumberOfIntersections(),2);
    EXPECT_THAT(tracker.getIntersection(0)==original.getIntersection(trueResults[0]), true);
    EXPECT_THAT(tracker.getIntersection(1)==original.getIntersection(trueResults[1]), true);
}

INSTANTIATE_TEST_SUITE_P(
        IntersectionScenarios,
        CSGFiltering,
        ::testing::Values(
            std::make_tuple(Operation::Union,std::vector<double>{0,3}),
            std::make_tuple(Operation::Intersection,std::vector<double>{1,2}),
            std::make_tuple(Operation::Difference,std::vector<double>{0,1})
            )

        );

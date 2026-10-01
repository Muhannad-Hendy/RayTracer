#include "gmock/gmock.h"
#include "group.h"
#include "testshape.h"
#include "Sphere.h"
#define PI 3.14159265

using namespace testing;

class GroupFeature : public Test {

};

TEST_F(GroupFeature, CreatingNewGroup) {
    Group group{};
    Matrix identity(4, MatrixType::identity);
    auto& groupTransformation = group.getTransformation();
    ASSERT_THAT(groupTransformation.getTransformationMatrix()==identity,true);
    ASSERT_EQ(group.getChildrenCount(),0);
}

TEST_F(GroupFeature, ShapeHasChildAttribute) {
    TestShape shape{};
    auto* shapeParent = shape.getParent();
    ASSERT_EQ(shapeParent,nullptr);
}

TEST_F(GroupFeature, AddingChildToGroup) {
    Group group{};
    TestShape shape{};
    group.addChild(std::make_unique<TestShape>(shape));
    ASSERT_EQ(group.isEmpty(), false);
    ASSERT_EQ(group.getChild(0)->getShapeID(),shape.getShapeID());
    ASSERT_NE(group.getChild(0)->getParent(),nullptr);
    ASSERT_THAT(group.getChild(0)->getParent()==&group,true);
}

TEST_F(GroupFeature, IntersectingRayWithEmptyGroup) {
    Group group{};
    Tuple origin{0,0,0,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    IntersectionTracker tracker{};
    group.intersect(ray,tracker);
    ASSERT_EQ(tracker.count(),0);
}

TEST_F(GroupFeature, IntersectingRayWithNonEmptyGroup) {
    Group group{};
    Sphere sphere1{};
    Sphere sphere2{};
    Transformer translator2{Transformation::translation,0,0,-3};
    sphere2.setTransformation(translator2);
    Sphere sphere3{};
    Transformer translator3{Transformation::translation,5,0,0};
    sphere3.setTransformation(translator3);
    group.addChild(std::make_unique<Sphere>(sphere1));
    group.addChild(std::make_unique<Sphere>(sphere2));
    group.addChild(std::make_unique<Sphere>(sphere3));
    Tuple origin{0,0,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    IntersectionTracker tracker{};
    group.intersect(ray,tracker);
    ASSERT_EQ(tracker.count(),4);
    ASSERT_EQ(tracker.getIntersectedObject(0).getShapeID(),sphere2.getShapeID());
    ASSERT_EQ(tracker.getIntersectedObject(1).getShapeID(),sphere2.getShapeID());
    ASSERT_EQ(tracker.getIntersectedObject(2).getShapeID(),sphere1.getShapeID());
    ASSERT_EQ(tracker.getIntersectedObject(3).getShapeID(),sphere1.getShapeID());
}

TEST_F(GroupFeature,IntersectingTransformedGroup) {
    Group group{};
    Transformer scalar{Transformation::scaling,2,2,2};
    group.setTransformation(scalar);
    Sphere sphere{};
    Transformer translator{Transformation::translation,5,0,0};
    sphere.setTransformation(translator);
    group.addChild(std::make_unique<Sphere>(sphere));
    Tuple origin{10,0,-10,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    IntersectionTracker tracker{};
    group.intersect(ray,tracker);
    ASSERT_EQ(tracker.count(),2);
}

TEST_F(GroupFeature,ConvertingPointFromWorldToObjectSpace) {
    Group group1{};
    Transformer rotator1{Transformation::yRotation,PI/2};
    group1.setTransformation(rotator1);
    Group group2{};
    Transformer scalar{Transformation::scaling,2,2,2};
    group2.setTransformation(scalar);
    auto* group2Pointer = group1.addChild(std::make_unique<Group>(std::move(group2)));
    Sphere sphere{};
    Transformer translator{Transformation::translation,5,0,0};
    sphere.setTransformation(translator);
    auto* spherePointer = group2Pointer->addChild(std::make_unique<Sphere>(sphere));
    auto point = spherePointer->worldToObject(Tuple{-2,0,-10,TupleType::point});
    Tuple correctPoint{0,0,-1,TupleType::point};
    ASSERT_THAT(point==correctPoint,true);
}

TEST_F(GroupFeature, ConvertingNormalFromObjectToWorldSpace) {
    Group group1{};
    Transformer rotator1{Transformation::yRotation,PI/2};
    group1.setTransformation(rotator1);
    Group group2{};
    Transformer scalar{Transformation::scaling,1,2,3};
    group2.setTransformation(scalar);
    auto* group2Pointer = group1.addChild(std::make_unique<Group>(std::move(group2)));
    Sphere sphere{};
    Transformer translator{Transformation::translation,5,0,0};
    sphere.setTransformation(translator);
    auto* spherePointer = group2Pointer->addChild(std::make_unique<Sphere>(sphere));
    auto point = spherePointer->normalToWorld(Tuple{std::sqrt(3)/3,std::sqrt(3)/3,std::sqrt(3)/3,TupleType::vector});
    Tuple correctPoint{0.28571,0.42857,-0.85714,TupleType::vector};
    ASSERT_THAT(point==correctPoint,true);
}

TEST_F(GroupFeature, FindingNormalOnChildObject) {
    Group group1{};
    Transformer rotator1{Transformation::yRotation,PI/2};
    group1.setTransformation(rotator1);
    Group group2{};
    Transformer scalar{Transformation::scaling,1,2,3};
    group2.setTransformation(scalar);
    auto* group2Pointer = group1.addChild(std::make_unique<Group>(std::move(group2)));
    Sphere sphere{};
    Transformer translator{Transformation::translation,5,0,0};
    sphere.setTransformation(translator);
    auto* spherePointer = group2Pointer->addChild(std::make_unique<Sphere>(sphere));
    auto normal = spherePointer->normalAt(Tuple{1.7321,1.1547,-5.5774,TupleType::point});
    Tuple correctNormal{0.28570,0.42854,-0.85716,TupleType::vector};
    ASSERT_THAT(normal==correctNormal,true);
}

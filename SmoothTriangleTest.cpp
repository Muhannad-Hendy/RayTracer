#include "gmock/gmock.h"
#include "Tuple.h"
#include "smoothtriangle.h"

using namespace testing;

class SmoothTriangleExposer : public SmoothTriangle {
public:
    using SmoothTriangle::SmoothTriangle;

    using SmoothTriangle::localNormalAt;
    using SmoothTriangle::localIntersect;
};

class SmoothTriangleFeature : public Test {
public:
    Tuple point1{0, 1, 0, TupleType::point};
    Tuple point2{-1, 0, 0, TupleType::point};
    Tuple point3{1, 0, 0, TupleType::point};
    Tuple normal1{0, 1, 0, TupleType::vector};
    Tuple normal2{-1, 0, 0, TupleType::vector};
    Tuple normal3{1, 0, 0, TupleType::vector};

    SmoothTriangleExposer tri{point1,point2,point3,normal1,normal2,normal3};

};

TEST_F(SmoothTriangleFeature, ConstructingSmoothTriangle) {
    ASSERT_THAT(tri.getVertex(0)==point1,true);
    ASSERT_THAT(tri.getVertex(1)==point2,true);
    ASSERT_THAT(tri.getVertex(2)==point3,true);

    ASSERT_THAT(tri.getVertexNormal(0)==normal1,true);
    ASSERT_THAT(tri.getVertexNormal(1)==normal2,true);
    ASSERT_THAT(tri.getVertexNormal(2)==normal3,true);
}

TEST_F(SmoothTriangleFeature, IntersectionWithSmoothTriangleStoresUV) {
    Ray ray{Tuple{-0.2, 0.3, -2,TupleType::point},Tuple{0, 0, 1,TupleType::vector}};
    IntersectionTracker tracker{};
    tri.localIntersect(ray,tracker);
    auto intersection = tracker.getIntersection(0);
    ASSERT_DOUBLE_EQ(intersection.getU(),0.45);
    ASSERT_DOUBLE_EQ(intersection.getV(),0.25);
}

TEST_F(SmoothTriangleFeature, NormalInterpolationWithUV) {
    IntersectionTracker tracker{};
    tracker.addIntersection(1,tri,0.45,0.25);
    Intersection &intersection = tracker.getIntersection(0);
    auto normal = tri.normalAt(Tuple{0,0,0,TupleType::point},&intersection);
    Tuple correctNormal{-0.5547, 0.83205, 0,TupleType::vector};
    ASSERT_THAT(normal==correctNormal,true);
}

TEST_F(SmoothTriangleFeature, PreparingNormalOnSmoothTriangle) {
    IntersectionTracker tracker{};
    tracker.addIntersection(1,tri,0.45,0.25);
    Ray ray{Tuple{-0.2, 0.3, -2,TupleType::point}, Tuple{0, 0, 1,TupleType::vector}};
    tracker.prepComputations(ray);
    auto normal = tracker.hit()->getNormalVector();
    Tuple correctNormal{-0.5547, 0.83205, 0,TupleType::vector};
    ASSERT_THAT(normal==correctNormal,true);
}

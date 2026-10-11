#include "gmock/gmock.h"
#include "Tuple.h"
#include "triangle.h"

using namespace testing;

class TrianglesFeature : public Test {

};

class TriangleExposer : public Triangle {
public:
    using Triangle::Triangle;

    using Triangle::localNormalAt;
    using Triangle::localIntersect;
};

TEST_F(TrianglesFeature, ConstructingTriangle) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    Triangle triangle{point1,point2,point3};

    ASSERT_THAT(triangle.getVertex(0)==point1,true);
    ASSERT_THAT(triangle.getVertex(1)==point2,true);
    ASSERT_THAT(triangle.getVertex(2)==point3,true);

    Tuple edge1{-1,-1,0,TupleType::vector};
    Tuple edge2{1,-1,0,TupleType::vector};
    Tuple normal{0,0,-1,TupleType::vector};
    ASSERT_THAT(triangle.getEdge(0)==edge1,true);
    ASSERT_THAT(triangle.getEdge(1)==edge2,true);
    ASSERT_THAT(triangle.getNormal()==normal,true);
}

TEST_F(TrianglesFeature, FindingNormalOnTriangle) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    TriangleExposer triangle{point1,point2,point3};

    auto normal1 = triangle.localNormalAt(Tuple{0, 0.5, 0,TupleType::point});
    auto normal2 = triangle.localNormalAt(Tuple{-0.5,0.75,0,TupleType::point});
    auto normal3 = triangle.localNormalAt(Tuple{0.5, 0.25, 0,TupleType::point});

    ASSERT_THAT(normal1==triangle.getNormal(),true);
    ASSERT_THAT(normal2==triangle.getNormal(),true);
    ASSERT_THAT(normal3==triangle.getNormal(),true);
}

TEST_F(TrianglesFeature, IntersectingRayParallelToTriangle) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    TriangleExposer triangle{point1,point2,point3};

    Ray ray{Tuple{0,-1,-2,TupleType::point},Tuple{0,1,0,TupleType::vector}};
    IntersectionTracker tracker{};
    triangle.localIntersect(ray,tracker);
    EXPECT_EQ(tracker.count(),0);
}


TEST_F(TrianglesFeature, RayMissesP1P3Edge) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    TriangleExposer triangle{point1,point2,point3};

    Ray ray{Tuple{1, 1, -2,TupleType::point},Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    triangle.localIntersect(ray,tracker);
    EXPECT_EQ(tracker.count(),0);
}

TEST_F(TrianglesFeature, RayMissesP1P2Edge) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    TriangleExposer triangle{point1,point2,point3};

    Ray ray{Tuple{-1, 1, -2,TupleType::point},Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    triangle.localIntersect(ray,tracker);
    EXPECT_EQ(tracker.count(),0);
}

TEST_F(TrianglesFeature, RayMissesP2P3Edge) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    TriangleExposer triangle{point1,point2,point3};

    Ray ray{Tuple{0, -1, -2,TupleType::point},Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    triangle.localIntersect(ray,tracker);
    EXPECT_EQ(tracker.count(),0);
}

TEST_F(TrianglesFeature, RayStrikesTriangle) {
    Tuple point1{0,1,0,TupleType::point};
    Tuple point2{-1,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    TriangleExposer triangle{point1,point2,point3};

    Ray ray{Tuple{0, 0.5, -2,TupleType::point},Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    triangle.localIntersect(ray,tracker);
    EXPECT_EQ(tracker.count(),1);
    ASSERT_EQ(tracker.getIntersectionTime(0),2);
}

#include "gmock/gmock.h"
#include "meshreader.h"
#include "triangle.h"
#include "Tuple.h"

using namespace testing;

class MeshReaderFeature : public Test {

};

TEST_F(MeshReaderFeature, IgnoringUnrecognizedLines) {
    std::string file{"../TestFiles/gibberish.obj"};

    MeshReader reader{file};
    reader.parseObjFile();
    auto ignoredLines = reader.getIgnoredLineCount();
    ASSERT_EQ(ignoredLines,5);
}

TEST_F(MeshReaderFeature, VertexRecords) {
    std::string file{"../TestFiles/vertexRecord.obj"};

    MeshReader reader{file};
    reader.parseObjFile();
    auto ignoredLines = reader.getIgnoredLineCount();
    EXPECT_EQ(ignoredLines,0);

    Tuple vertex1{-1, 1, 0,TupleType::point};
    Tuple vertex2{-1, 0.5, 0,TupleType::point};
    Tuple vertex3{1, 0, 0,TupleType::point};
    Tuple vertex4{1, 1, 0,TupleType::point};
    ASSERT_THAT(reader.getVertex(0)==vertex1,true);
    ASSERT_THAT(reader.getVertex(1)==vertex2,true);
    ASSERT_THAT(reader.getVertex(2)==vertex3,true);
    ASSERT_THAT(reader.getVertex(3)==vertex4,true);
}

TEST_F(MeshReaderFeature, ParsingTriangleFaces) {
    std::string file{"../TestFiles/triangleFaces.obj"};

    MeshReader reader{file};
    reader.parseObjFile();

    Tuple vertex1{-1, 1, 0,TupleType::point};
    Tuple vertex2{-1, 0, 0,TupleType::point};
    Tuple vertex3{1, 0, 0,TupleType::point};
    Tuple vertex4{1, 1, 0,TupleType::point};

    auto group = reader.getParserGroup();
    auto triangle1 = dynamic_cast<Triangle*>(group->getChild(0));
    auto triangle2 = dynamic_cast<Triangle*>(group->getChild(1));
    ASSERT_THAT(triangle1->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle1->getVertex(1)==vertex2,true);
    ASSERT_THAT(triangle1->getVertex(2)==vertex3,true);
    ASSERT_THAT(triangle2->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle2->getVertex(1)==vertex3,true);
    ASSERT_THAT(triangle2->getVertex(2)==vertex4,true);
}

TEST_F(MeshReaderFeature, TriangulatingPolygons) {
    std::string file{"../TestFiles/polygonTriangulation.obj"};

    MeshReader reader{file};
    reader.parseObjFile();

    Tuple vertex1{-1, 1, 0,TupleType::point};
    Tuple vertex2{-1, 0, 0,TupleType::point};
    Tuple vertex3{1, 0, 0,TupleType::point};
    Tuple vertex4{1, 1, 0,TupleType::point};
    Tuple vertex5{0,2, 0,TupleType::point};

    auto group = reader.getParserGroup();
    auto triangle1 = dynamic_cast<Triangle*>(group->getChild(0));
    auto triangle2 = dynamic_cast<Triangle*>(group->getChild(1));
    auto triangle3 = dynamic_cast<Triangle*>(group->getChild(2));
    ASSERT_THAT(triangle1->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle1->getVertex(1)==vertex2,true);
    ASSERT_THAT(triangle1->getVertex(2)==vertex3,true);
    ASSERT_THAT(triangle2->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle2->getVertex(1)==vertex3,true);
    ASSERT_THAT(triangle2->getVertex(2)==vertex4,true);
    ASSERT_THAT(triangle3->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle3->getVertex(1)==vertex4,true);
    ASSERT_THAT(triangle3->getVertex(2)==vertex5,true);
}

TEST_F(MeshReaderFeature, TrianglesInGroups) {
    std::string file{"../TestFiles/triangleGroups.obj"};

    MeshReader reader{file};
    reader.parseObjFile();

    Tuple vertex1{-1, 1, 0,TupleType::point};
    Tuple vertex2{-1, 0, 0,TupleType::point};
    Tuple vertex3{1, 0, 0,TupleType::point};
    Tuple vertex4{1, 1, 0,TupleType::point};

    auto group = reader.getParserGroup();
    auto group1 = dynamic_cast<Group*>(group->getChild(0));
    auto group2 = dynamic_cast<Group*>(group->getChild(1));
    auto triangle1 = dynamic_cast<Triangle*>(group1->getChild(0));
    auto triangle2 = dynamic_cast<Triangle*>(group2->getChild(0));
    ASSERT_THAT(triangle1->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle1->getVertex(1)==vertex2,true);
    ASSERT_THAT(triangle1->getVertex(2)==vertex3,true);
    ASSERT_THAT(triangle2->getVertex(0)==vertex1,true);
    ASSERT_THAT(triangle2->getVertex(1)==vertex3,true);
    ASSERT_THAT(triangle2->getVertex(2)==vertex4,true);
}

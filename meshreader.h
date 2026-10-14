#ifndef MESHREADER_H
#define MESHREADER_H

#include <string>
#include <vector>
#include "Tuple.h"
#include "group.h"

class MeshReader
{
public:
    MeshReader(const std::string& inputFile);

    void parseObjFile();

    int getIgnoredLineCount() const;

    Tuple getVertex(const int index) const;

    Group* getParserGroup();

    std::unique_ptr<Group> takeParserGroup();

private:
    std::string inputFile{};
    int ignoredLineCount{};
    int totalLineCount{};
    int readLineCount{};
    std::vector<Tuple> vertices{};
    std::unique_ptr<Group> parserGroup = std::make_unique<Group>();
    void fanTriangulation(std::istringstream &stream);
    Group* activeGroup = parserGroup.get();
};

#endif // MESHREADER_H

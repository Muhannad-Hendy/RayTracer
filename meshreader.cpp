#include "meshreader.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "triangle.h"

MeshReader::MeshReader(const std::string &inputFile) : inputFile{inputFile} {}


void MeshReader::parseObjFile() {
    std::ifstream file(inputFile);

    if (!file.is_open()) {
        std::cerr << "Could not open " << inputFile << " for reading.\n";
    }

    std::string line;
    char lineIdentifier{};
    double x,y,z;
    while (std::getline(file,line)) {
        std::istringstream inputStringStream(line);
        inputStringStream >> lineIdentifier;
        switch (lineIdentifier) {
        case 'v':
            inputStringStream >> x >> y >> z;
            vertices.push_back(Tuple{x,y,z,TupleType::point});
            readLineCount++;
            break;
        case 'f': {
            fanTriangulation(inputStringStream);
            readLineCount++;
            break;
        }
        case 'g':{
            Group group{};
            activeGroup = parserGroup->addChild(std::make_unique<Group>(std::move(group)));
            break;
        }
        default:
            ignoredLineCount++;
            break;
        }
        totalLineCount++;
    }
    std::cout<<"Total lines: " << totalLineCount << std::endl;
    std::cout<<"Lines read: " << readLineCount << std::endl;
    std::cout<<"Lines ignored: " << ignoredLineCount << std::endl;
}

int MeshReader::getIgnoredLineCount() const {
    return ignoredLineCount;
}

Tuple MeshReader::getVertex(const int index) const {
    return vertices[index];
}

Group* MeshReader::getParserGroup() {
    return parserGroup.get();
}

void MeshReader::fanTriangulation(std::istringstream &stream) {
    std::vector<int> vertexIndices;
    int token;
    while (stream >> token) {
        vertexIndices.push_back(--token);
    }

    if (vertexIndices.size() == 3) {
        Triangle triangle{vertices[vertexIndices[0]],vertices[vertexIndices[1]],vertices[vertexIndices[2]]};
        activeGroup->addChild(std::make_unique<Triangle>(triangle));
    }
    else if (vertexIndices.size() > 3) {
        for (size_t i=1; i<vertexIndices.size(); i++) {
            Triangle triangle{vertices[vertexIndices[0]],vertices[vertexIndices[i]],vertices[vertexIndices[i+1]]};
            activeGroup->addChild(std::make_unique<Triangle>(triangle));
        }
    }
}

std::unique_ptr<Group> MeshReader::takeParserGroup() {
    return std::move(parserGroup);
}

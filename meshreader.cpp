#include "meshreader.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "triangle.h"
#include "smoothtriangle.h"

MeshReader::MeshReader(const std::string &inputFile) : inputFile{inputFile} {}


void MeshReader::parseObjFile() {
    std::ifstream file(inputFile);

    if (!file.is_open()) {
        std::cerr << "Could not open " << inputFile << " for reading.\n";
    }

    std::string line;
    while (std::getline(file,line)) {
        std::string lineIdentifier{};
        double x,y,z;
        std::istringstream inputStringStream(line);
        inputStringStream >> lineIdentifier;
        if (lineIdentifier == "v") {
            inputStringStream >> x >> y >> z;
            vertices.push_back(Tuple{x,y,z,TupleType::point});
            readLineCount++;
        }
        else if (lineIdentifier == "f") {
            fanTriangulation(inputStringStream);
            readLineCount++;
        }
        else if (lineIdentifier == "g") {
            Group group{};
            activeGroup = parserGroup->addChild(std::make_unique<Group>(std::move(group)));
        }
        else if (lineIdentifier == "vn") {
            hasVertexNormals = true;
            inputStringStream >> x >> y >> z;
            vertexNormals.push_back(Tuple{x,y,z,TupleType::vector});
            readLineCount++;
        }
        else {
            ignoredLineCount++;
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
    std::vector<int> textureVertexIndices;
    std::vector<int> vertexNormalIndices;
    int oneBased{};
    std::string token;
    std::vector<std::string> tokens;
    if (!hasVertexNormals) {
        while (stream >> oneBased) {
            vertexIndices.push_back(--oneBased);
        }
    }
    else {
        while (stream >> token) {
            tokens.push_back(token);
        }
        for (size_t i=0; i<tokens.size(); i++) {
            std::vector<int> temp;
            std::istringstream perVertexTokens(tokens[i]);
            while (std::getline(perVertexTokens, token, '/')) {
                if(!token.empty()) {
                    oneBased = std::stoi(token);
                    temp.push_back(--oneBased);
                }
                else temp.push_back(0);
            }
            vertexIndices.push_back(temp[0]);
            vertexNormalIndices.push_back(temp[2]);
        }
    }

    if (vertexIndices.size() == 3) {
        if (!hasVertexNormals) {
            Triangle triangle{vertices[vertexIndices[0]],vertices[vertexIndices[1]],vertices[vertexIndices[2]]};
            activeGroup->addChild(std::make_unique<Triangle>(triangle));
        }
        else {
            SmoothTriangle triangle{vertices[vertexIndices[0]],vertices[vertexIndices[1]],vertices[vertexIndices[2]],
                                   vertexNormals[vertexNormalIndices[0]], vertexNormals[vertexNormalIndices[1]], vertexNormals[vertexNormalIndices[2]]};
            activeGroup->addChild(std::make_unique<SmoothTriangle>(triangle));
        }

    }
    else if (vertexIndices.size() > 3) {
        for (size_t i=1; i<vertexIndices.size(); i++) {
            if (!hasVertexNormals) {
                Triangle triangle{vertices[vertexIndices[0]],vertices[vertexIndices[i]],vertices[vertexIndices[i+1]]};
                activeGroup->addChild(std::make_unique<Triangle>(triangle));
            }
            else {
                SmoothTriangle triangle{vertices[vertexIndices[0]],vertices[vertexIndices[i]],vertices[vertexIndices[i+1]],
                                       vertexNormals[vertexNormalIndices[0]], vertexNormals[vertexNormalIndices[i]], vertexNormals[vertexNormalIndices[i+1]]};
                activeGroup->addChild(std::make_unique<SmoothTriangle>(triangle));
            }
        }
    }
}

std::unique_ptr<Group> MeshReader::takeParserGroup() {
    return std::move(parserGroup);
}

Tuple MeshReader::getVertexNormal(const int index) const {
    return vertexNormals[index];
}

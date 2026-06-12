#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include "Color.h"

class Canvas
{
public:
    Canvas (int width, int height);

    ~Canvas ();

    int getWidth ();

    int getHeight ();

    Color* getPixelColor (int columnNumber, int rowNumber) const;

    void setPixelColor (int columnNumber, int rowNumber, Color color);

    void saveToPPM(const std::string& filePath) const;

    std::vector<int> scaleThenClampColor(const Color& pixelColor, double scalar) const;

    std::string readFromPPM(const std::string& filePath);

private:
    int width{};
    int height{};
    Color** pixelArray;
    std::string PPM_FORMAT_IDENTIFIER = "P3\n";
    int MIN_COLOR_VALUE = 0;
    int MAX_COLOR_VALUE = 255;
    int MAX_PPM_LINE_CHAR_WIDTH = 70;
};

#endif // CANVAS_H

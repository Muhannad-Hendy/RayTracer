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
    Canvas (int width, int height) : width{width}, height{height} {
        int arraySize = width * height;
        Color* colorPointer{};
        pixelArray = new Color*[arraySize];
        for (int i = 0; i<arraySize; i++){
            colorPointer = new Color{0, 0, 0};
            pixelArray[i] = colorPointer;
        }

    }

    ~Canvas (){
        delete [] pixelArray;
    }

    int getWidth (){
        return width;
    }

    int getHeight (){
        return height;
    }

    Color* getPixelColor (int columnNumber, int rowNumber){
        Color* pixelColor = *(pixelArray + rowNumber * width + columnNumber);
        return pixelColor;
    }

    void setPixelColor (int columnNumber, int rowNumber, Color& color){
        *(pixelArray + rowNumber * width + columnNumber) = &color;
    }

    void saveToPPM(const std::string& filePath){
        std::ofstream ppmFile{filePath, std::ios::out};
        std::ostringstream outputStringStream;
        Color* pixelColor;
        outputStringStream << PPM_FORMAT_IDENTIFIER << width << " " << height << "\n" << MAX_COLOR_VALUE << "\n";

        ppmFile << outputStringStream.str();
        outputStringStream.str("");
        for (int i = 0; i < height; i++){
            for (int j = 0; j <width; j++){
                pixelColor = this->getPixelColor(j, i);
                std::vector<int> colorComponent = scaleThenClampColor(*pixelColor, MAX_COLOR_VALUE);

                std::string redString = std::to_string(colorComponent[0]);
                std::string greenString = std::to_string(colorComponent[1]);
                std::string blueString = std::to_string(colorComponent[2]);

               for (int k = 0; k < 3; k++){
                   outputStringStream << colorComponent[k];
                   if (outputStringStream.tellp() >= MAX_PPM_LINE_CHAR_WIDTH - 3){
                       outputStringStream << "\n";
                       ppmFile << outputStringStream.str();
                       outputStringStream.str("");
                   } else {
                       outputStringStream << " ";
                   }
               }
            }
            outputStringStream << "\n";
            ppmFile << outputStringStream.str();
            outputStringStream.str("");

        }
        ppmFile << std::endl;
    }

    std::vector<int> scaleThenClampColor(const Color& pixelColor, double scalar){
        std::vector<int> colorComponent(3);
        Color color = pixelColor * scalar;

        colorComponent[0] = (int) std::round(color.getRed());
        colorComponent[1] = (int) std::round(color.getGreen());
        colorComponent[2] = (int) std::round(color.getBlue());

        for (int k = 0; k < 3; k++){
            if (colorComponent[k] > 255) colorComponent[k] = 255;
            else if (colorComponent[k] < 0) colorComponent[k] = 0;
        }

        return colorComponent;
    }

    std::string readFromPPM(const std::string& filePath){
        std::ifstream ppmFile{filePath};
        std::stringstream inputStringStream;
        std::string fileContents;
        inputStringStream << ppmFile.rdbuf();
        fileContents = inputStringStream.str();
        std::cout << fileContents;
        return fileContents;
    }

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

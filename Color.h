#ifndef COLOR_H
#define COLOR_H

#include "Utilities.h"

class Color
{
public:
    Color(double red, double green, double blue) : red{red}, green{green}, blue{blue} {}

    double getRed (){
        return red;
    }

    double getGreen() {
        return green;
    }

    double getBlue() {
        return blue;
    }

    friend bool operator== (const Color& colorA, const Color& colorB){
        using namespace util;
        if (equals(colorA.red, colorB.red) && equals(colorA.green, colorB.green) && equals(colorA.blue, colorB.blue)) return true;
        else return false;
    }

    friend Color operator+ (const Color& colorA, const Color& colorB){
        double redSum = colorA.red + colorB.red;
        double greenSum = colorA.green + colorB.green;
        double blueSum = colorA.blue + colorB.blue;
        Color sum{redSum, greenSum, blueSum};
        return sum;
    }

    friend Color operator- (const Color& colorA, const Color& colorB){
        double redSum = colorA.red - colorB.red;
        double greenSum = colorA.green - colorB.green;
        double blueSum = colorA.blue - colorB.blue;
        Color sum{redSum, greenSum, blueSum};
        return sum;
    }

    friend Color operator* (const Color& color, const double factor){
        Color scaled{color.red * factor, color.green * factor, color.blue * factor};
        return scaled;
    }

    friend Color operator* (const Color& colorA, const Color& colorB){
        Color hadamardProduct{colorA.red * colorB.red, colorA.green * colorB.green, colorA.blue * colorB.blue};
        return hadamardProduct;
    }

private:
    double red{};
    double green{};
    double blue{};
};

#endif // COLOR_H

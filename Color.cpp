#include "Color.h"

Color::Color(double red, double green, double blue) : red{red}, green{green}, blue{blue} {}

double Color::getRed (){
    return red;
}

double Color::getGreen() {
    return green;
}

double Color::getBlue() {
    return blue;
}

bool operator== (const Color& colorA, const Color& colorB){
        using namespace util;
        if (equals(colorA.red, colorB.red) && equals(colorA.green, colorB.green) && equals(colorA.blue, colorB.blue)) return true;
        else return false;
}

Color operator+ (const Color& colorA, const Color& colorB){
        double redSum = colorA.red + colorB.red;
        double greenSum = colorA.green + colorB.green;
        double blueSum = colorA.blue + colorB.blue;
        Color sum{redSum, greenSum, blueSum};
        return sum;
}

Color operator- (const Color& colorA, const Color& colorB){
        double redSum = colorA.red - colorB.red;
        double greenSum = colorA.green - colorB.green;
        double blueSum = colorA.blue - colorB.blue;
        Color sum{redSum, greenSum, blueSum};
        return sum;
}

Color operator* (const Color& color, const double factor){
        Color scaled{color.red * factor, color.green * factor, color.blue * factor};
        return scaled;
}

Color operator* (const Color& colorA, const Color& colorB){
        Color hadamardProduct{colorA.red * colorB.red, colorA.green * colorB.green, colorA.blue * colorB.blue};
        return hadamardProduct;
}

#ifndef COLOR_H
#define COLOR_H

#include "Utilities.h"

class Color
{
public:
    Color(double red, double green, double blue);

    double getRed ();

    double getGreen();

    double getBlue();

    friend bool operator== (const Color& colorA, const Color& colorB);

    friend Color operator+ (const Color& colorA, const Color& colorB);

    friend Color operator- (const Color& colorA, const Color& colorB);

    friend Color operator* (const Color& color, const double factor);

    friend Color operator* (const Color& colorA, const Color& colorB);

private:
    double red{};
    double green{};
    double blue{};
};

#endif // COLOR_H

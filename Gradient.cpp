#include "Gradient.h"
#include "Tuple.h"

const Color Gradient::patternAt(const Tuple &patternPoint) const {
    Color distance = getColor(1) - getColor(0);
    double xValue = patternPoint.getXValue();
    double fraction = xValue - floor(xValue);
    return getColor(0) + distance*fraction;
}

#include "Rings.h"
#include "Tuple.h"
#include <cmath>

const Color Rings::patternAt(const Tuple &patternPoint) const {
    double parameter = std::pow(patternPoint.getXValue(),2) + std::pow(patternPoint.getZValue(),2);
    parameter = floor(std::sqrt(parameter));
    if (static_cast<int>(parameter) %2==0) {
        return getColor(0);
    }
    else {
        return getColor(1);
    }
}

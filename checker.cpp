#include "checker.h"
#include "Tuple.h"
#include <cmath>

const Color Checker::patternAt(const Tuple &patternPoint) const {
    double flooredX = std::floor(patternPoint.getXValue());
    double flooredY = std::floor(patternPoint.getYValue());
    double flooredZ = std::floor(patternPoint.getZValue());
    double sum = flooredX + flooredY + flooredZ;
    if (static_cast<int>(sum) %2 == 0) {
        return getColor(0);
    }
    else {
        return getColor(1);
    }
}

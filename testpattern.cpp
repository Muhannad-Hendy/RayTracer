#include "testpattern.h"
#include "Tuple.h"

const Color TestPattern::patternAt(const Tuple &patternPoint) const {
    return Color{patternPoint.getXValue(),patternPoint.getYValue(),patternPoint.getZValue()};
}


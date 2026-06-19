#include <cmath>
#include "Stripe.h"
#include "Tuple.h"

Stripe::Stripe() {}

const Color Stripe::patternAt(const Tuple &patternPoint) const {
    int parameter = static_cast<int>(std::floor(patternPoint.getXValue()));
    parameter = parameter % 2;
    if (parameter==0) return getColor(0);
    else return getColor(1);
}

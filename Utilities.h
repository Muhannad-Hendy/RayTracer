#ifndef UTILITIES_H
#define UTILITIES_H
// A namespace that includes utility functions.
#include <cmath>

namespace util {

static const double EPSILON{0.00001};

bool equals(double x, double y){
    auto absoluteDifference = std::abs(x - y);
    if (absoluteDifference < EPSILON) return true;
    else return false;
}

}
#endif // UTILITIES_H

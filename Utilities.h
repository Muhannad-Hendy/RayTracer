#ifndef UTILITIES_H
#define UTILITIES_H
// A namespace that includes utility functions.
#include <cmath>

namespace util {

static const double EPSILON{0.00001};

bool equals(double x, double y);

constexpr double PI = 3.14159265358979323846;

}
#endif // UTILITIES_H

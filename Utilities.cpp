#include "Utilities.h"

bool util::equals(double x, double y){
    auto absoluteDifference = std::abs(x - y);
    if (absoluteDifference < util::EPSILON) return true;
    else return false;
}

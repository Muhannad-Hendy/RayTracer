#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include "Utilities.h"

enum class TupleType{
    point,
    vector
};

class Tuple
{
public:
    Tuple(double xCoordinate, double yCoordinate, double zCoordinate, TupleType type);

    Tuple(double xCoordinate, double yCoordinate, double zCoordinate, double wCoordinate);

    double getXValue();

    double getYValue();

    double getZValue();

    double getWValue();

    friend bool operator== (Tuple& tuple1, Tuple& tuple2);

    friend Tuple operator+ (Tuple& tuple1, Tuple& tuple2);

    friend Tuple operator- (Tuple& tuple1, Tuple& tuple2);

    Tuple operator- ();

    friend Tuple operator* (const Tuple& tuple, const double& factor);

    double dot (const Tuple& bVector);

    Tuple cross (const Tuple& vector);

    friend Tuple operator/ (const Tuple& tuple, const double& factor);

    double magnitude ();

    Tuple normalize ();

private:
    const double x{};
    const double y{};
    const double z{};
    double w{};
};

#endif // TUPLE_H

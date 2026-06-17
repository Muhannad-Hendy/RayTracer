#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include "Utilities.h"
class Matrix;

enum class TupleType{
    point,
    vector
};

class Tuple
{
public:
    Tuple();

    Tuple(double xCoordinate, double yCoordinate, double zCoordinate, TupleType type);

    Tuple(double xCoordinate, double yCoordinate, double zCoordinate, double wCoordinate);

    Tuple(const Matrix& matrix);

    double getXValue() const;

    double getYValue() const;

    double getZValue() const;

    double getWValue() const;

    void setWValue(double value);

    friend bool operator== (const Tuple& tuple1, const Tuple& tuple2);

    friend Tuple operator+ (const Tuple& tuple1, const Tuple& tuple2);

    friend Tuple operator- (const Tuple& tuple1, const Tuple& tuple2);

    Tuple operator- ();

    friend Tuple operator* (const Tuple& tuple, const double& factor);

    double dot (const Tuple& bVector);

    Tuple cross (const Tuple& vector);

    friend Tuple operator/ (const Tuple& tuple, const double& factor);

    double magnitude ();

    Tuple normalize ();

    void initialize(double xCoordinate, double yCoordinate, double zCoordinate, TupleType type);

    Tuple& operator= (const Tuple& original);

    Tuple reflectAround(const Tuple& normalVector);
private:
    double x{};
    double y{};
    double z{};
    double w{};
};

#endif // TUPLE_H

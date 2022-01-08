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
    Tuple(double xCoordinate, double yCoordinate, double zCoordinate, TupleType type) : x{xCoordinate}, y{yCoordinate}, z{zCoordinate} {
        switch(type){
        case TupleType::point: {
            w = 1.0;
        } break;
        case TupleType::vector: {
            w = 0.0;
        } break;
        }
    }

    Tuple(double xCoordinate, double yCoordinate, double zCoordinate, double wCoordinate) : x{xCoordinate}, y{yCoordinate}, z{zCoordinate}, w{wCoordinate} {}

    double getXValue(){
        return x;
    }

    double getYValue(){
        return y;
    }

    double getZValue(){
        return z;
    }

    float getWValue(){
        return w;
    }

    friend bool operator== (Tuple& tuple1, Tuple& tuple2){
        using namespace util;
        if (equals(tuple1.x, tuple2.x) && equals(tuple1.y, tuple2.y) && equals(tuple1.z, tuple2.z) && equals(tuple1.w, tuple2.w)) return true;
        else return false;
    }

    friend Tuple operator+ (Tuple& tuple1, Tuple& tuple2){
        double xSum = tuple1.x + tuple2.x;
        double ySum = tuple1.y + tuple2.y;
        double zSum = tuple1.z + tuple2.z;
        double wSum = tuple1.w + tuple2.w;
        Tuple sum{xSum, ySum, zSum, wSum};
        return sum;
    }

    friend Tuple operator- (Tuple& tuple1, Tuple& tuple2){
        double xSum = tuple1.x - tuple2.x;
        double ySum = tuple1.y - tuple2.y;
        double zSum = tuple1.z - tuple2.z;
        double wSum = tuple1.w - tuple2.w;
        Tuple sum{xSum, ySum, zSum, wSum};
        return sum;
    }

    Tuple operator- (){
        Tuple negated{this->x * -1, this->y * -1, this->z * -1, this->w * -1};
        return negated;
    }

private:
    const double x{};
    const double y{};
    const double z{};
    double w{};
};

#endif // TUPLE_H

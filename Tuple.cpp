#include "Tuple.h"
#include "Matrix.h"

Tuple::Tuple(){}

Tuple::Tuple(double xCoordinate, double yCoordinate, double zCoordinate, TupleType type) : x{xCoordinate}, y{yCoordinate}, z{zCoordinate} {
    switch(type){
    case TupleType::point: {
        w = 1.0;
    } break;
    case TupleType::vector: {
        w = 0.0;
    } break;
    }
}

Tuple::Tuple(double xCoordinate, double yCoordinate, double zCoordinate, double wCoordinate) : x{xCoordinate}, y{yCoordinate}, z{zCoordinate}, w{wCoordinate} {}

Tuple::Tuple(const Matrix& matrix) : x{matrix.get(0,0)}, y{matrix.get(1,0)}, z{matrix.get(2,0)}, w{matrix.get(3,0)} {}

double Tuple::getXValue() const{
    return x;
}

double Tuple::getYValue() const{
    return y;
}

double Tuple::getZValue() const{
    return z;
}

double Tuple::getWValue() const{
    return w;
}

bool operator== (Tuple& tuple1, Tuple& tuple2){
    using namespace util;
    if (equals(tuple1.x, tuple2.x) && equals(tuple1.y, tuple2.y) && equals(tuple1.z, tuple2.z) && equals(tuple1.w, tuple2.w)) return true;
    else return false;
}

Tuple operator+ (Tuple& tuple1, Tuple& tuple2){
    double xSum = tuple1.x + tuple2.x;
    double ySum = tuple1.y + tuple2.y;
    double zSum = tuple1.z + tuple2.z;
    double wSum = tuple1.w + tuple2.w;
    Tuple sum{xSum, ySum, zSum, wSum};
    return sum;
}

Tuple operator- (Tuple& tuple1, Tuple& tuple2){
    double xSum = tuple1.x - tuple2.x;
    double ySum = tuple1.y - tuple2.y;
    double zSum = tuple1.z - tuple2.z;
    double wSum = tuple1.w - tuple2.w;
    Tuple sum{xSum, ySum, zSum, wSum};
    return sum;
}

Tuple Tuple::operator- (){
    Tuple negated{this->x * -1, this->y * -1, this->z * -1, this->w * -1};
    return negated;
}

Tuple operator* (const Tuple& tuple, const double& factor){
    Tuple scaledTuple{tuple.x * factor, tuple.y * factor, tuple.z * factor, tuple.w * factor};
    return scaledTuple;
}

double Tuple::dot (const Tuple& bVector){
    double dotProduct = this->x * bVector.x +
                        this->y * bVector.y +
                        this->z * bVector.z +
                        this->w * bVector.w;
    return dotProduct;
}

Tuple Tuple::cross (const Tuple& vector){
    double xComponent = this->y * vector.z - this->z * vector.y;
    double yComponent = this->z * vector.x - this->x * vector.z;
    double zComponent = this->x * vector.y - this->y * vector.x;
    Tuple crossProduct{xComponent, yComponent, zComponent, 0};
    return crossProduct;
}

Tuple operator/ (const Tuple& tuple, const double& factor){
    Tuple scaledTuple{tuple.x / factor, tuple.y / factor, tuple.z / factor, tuple.w / factor};
    return scaledTuple;
}

double Tuple::magnitude (){
    double x_squared = pow(x, 2.0);
    double y_squared = pow(y, 2.0);
    double z_squared = pow(z, 2.0);
    double magnitude = sqrt(x_squared + y_squared + z_squared);
    return magnitude;
}

Tuple Tuple::normalize (){
    double magnitude = this->magnitude();
    double x_normalized = this->x / magnitude;
    double y_normalized = this->y / magnitude;
    double z_normalized = this->z / magnitude;
    double w_normalized = this->w / magnitude;
    Tuple normalizedVector{x_normalized, y_normalized, z_normalized, w_normalized};
    return normalizedVector;
}

void Tuple::initialize(double xCoordinate, double yCoordinate, double zCoordinate, TupleType type){
    Tuple temporary{xCoordinate, yCoordinate, zCoordinate, type};
    *this = temporary;
}

Tuple& Tuple::operator=(const Tuple &original){
    if (this == &original) return *this;
    x = original.x;
    y = original.y;
    z = original.z;
    w = original.w;
    return *this;
}

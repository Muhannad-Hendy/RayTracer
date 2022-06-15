#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"

class Sphere
{
public:
    Sphere() {
        ID = spheresCounter;
        spheresCounter++;
        radius = 1.0;
        center.initialize(0,0,0,TupleType::point);
    }

    Tuple getCenter(){
        return center;
    }

    int getSphereID(){
        return ID;
    }

    friend bool operator== (Sphere& sphere1, Sphere& sphere2){
        if (sphere1.ID == sphere2.ID) return true;
        else return false;
    }

private:
    static int spheresCounter;
    int ID{};
    double radius{};
    Tuple center{};
};

int Sphere::spheresCounter=0;
#endif // SPHERE_H

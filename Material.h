#ifndef MATERIAL_H
#define MATERIAL_H
#include "Color.h"

class Material
{
public:
    Material();

    Color getColor() const;

    void setColor(const Color& newColor);

    double getAmbient() const;

    void setAmbient(const double newAmbient);

    double getDiffuse() const;

    void setDiffuse(const double newDiffuse);

    double getSpecular() const;

    void setSpecular(const double newSpecular);

    double getShininess() const;

    void setShininess(const double newShininess);

    friend bool operator== (Material& material1, Material& material2);

    Material& operator= (const Material& original);
private:
    Color color{};
    double ambient{};
    double diffuse{};
    double specular{};
    double shininess{};
};

#endif // MATERIAL_H

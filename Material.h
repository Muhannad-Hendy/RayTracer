#ifndef MATERIAL_H
#define MATERIAL_H
#include "Color.h"
#include "Pattern.h"
#include <memory>

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

    std::shared_ptr<Pattern> getPattern() const;

    void setPattern(std::shared_ptr<Pattern> pattern);

    void setReflectivity(const double reflectivity);

    double getReflectivity() const;

    void setTransparency(const double transparency);

    double getTransparency() const;

    void setRefractiveIndex(const double index);

    double getRefractiveIndex() const;

private:
    Color color{};
    double ambient{};
    double diffuse{};
    double specular{};
    double shininess{};
    std::shared_ptr<Pattern> pattern;
    double reflectivity{};
    double transparency{};
    double refractiveIndex{};
};

#endif // MATERIAL_H

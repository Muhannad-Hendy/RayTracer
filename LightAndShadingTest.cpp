#include "gmock/gmock.h"
#include "Sphere.h"
#include "Tuple.h"
#include "Color.h"
#include "Light.h"
#include "Material.h"
#define PI 3.14159265

using namespace testing;

class LightAndShadingFeature : public Test {
public:
    double coordinateValue{sqrt(3) / 3};
    // common values for lighting tests:
    Material material{};
    Tuple position{0,0,0,TupleType::point};
    Tuple normalVector{0,0,-1,TupleType::vector};
};

TEST_F(LightAndShadingFeature, NormalOnSphereAtPointOnXAxis){
    Sphere sphere{};
    Tuple point{1,0,0,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{1,0,0,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalOnSphereAtPointOnYAxis){
    Sphere sphere{};
    Tuple point{0,1,0,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{0,1,0,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalOnSphereAtPointOnZAxis){
    Sphere sphere{};
    Tuple point{0,0,1,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{0,0,1,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalOnSphereAtNonAxialPoint){
    Sphere sphere{};
    Tuple point{coordinateValue,coordinateValue,coordinateValue,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{coordinateValue,coordinateValue,coordinateValue,TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, NormalVectorIsNormalized){
    Sphere sphere{};
    Tuple point{coordinateValue,coordinateValue,coordinateValue,TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple normalizedVector = normalVector.normalize();

    ASSERT_THAT(normalVector == normalizedVector, true);
}

TEST_F(LightAndShadingFeature, ComputingNormalOnTranslatedSphere){
    Sphere sphere{};
    Transformer translation{Transformation::translation,0,1,0};
    sphere.setTransformation(translation);
    Tuple point{0, 1.70711, -0.70711, TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{0, 0.70711, -0.70711, TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, ComputingNormalOnTransformedSphere){
    Sphere sphere{};
    Transformer scaling{Transformation::scaling, 1, 0.5, 1};
    Transformer rotation{Transformation::zRotation, PI/5};
    Transformer combined = rotation > scaling;
    sphere.setTransformation(combined);
    double value{sqrt(2)/2};
    Tuple point{0, value, -value, TupleType::point};
    Tuple normalVector = sphere.normal(point);
    Tuple trueNormalVector{0, 0.97014, -0.24254, TupleType::vector};

    ASSERT_THAT(normalVector == trueNormalVector, true);
}

TEST_F(LightAndShadingFeature, ReflectingVectorApproachingAt45Deg){
    Tuple velocity{1,-1,0,TupleType::vector};
    Tuple normal{0,1,0,TupleType::vector};
    Tuple reflection = velocity.reflectAround(normal);
    Tuple trueReflection{1,1,0,TupleType::vector};

    ASSERT_THAT(reflection == trueReflection, true);
}

TEST_F(LightAndShadingFeature, ReflectingVectorOffSlantedSurface){
    Tuple velocity{0,-1,0,TupleType::vector};
    double value{sqrt(2)/2};
    Tuple normal{value,value,0,TupleType::vector};
    Tuple reflection = velocity.reflectAround(normal);
    Tuple trueReflection{1,0,0,TupleType::vector};

    ASSERT_THAT(reflection == trueReflection, true);
}

TEST_F(LightAndShadingFeature, PointLightHasPositionAndIntensity){
    Color intensity{1,1,1};
    Tuple position{0,0,0,TupleType::point};
    Light light{position, intensity};

    Tuple lightPosition = light.getPosition();
    Color lightIntensity = light.getIntensity();
    ASSERT_THAT(lightPosition== position, true);
    ASSERT_THAT(lightIntensity == intensity, true);
}

TEST_F(LightAndShadingFeature, DefaultMaterial){
    Material material{};
    Color materialColor = material.getColor();
    Color color{1,1,1};
    ASSERT_THAT(materialColor == color, true);
    ASSERT_THAT(material.getAmbient(), Eq(0.1));
    ASSERT_THAT(material.getDiffuse(), Eq(0.9));
    ASSERT_THAT(material.getSpecular(), Eq(0.9));
    ASSERT_THAT(material.getShininess(), Eq(200));
}

TEST_F(LightAndShadingFeature, SphereHasDefaultMaterial){
    Sphere sphere{};
    Material sphereMaterial = sphere.getMaterial();
    Material defaultMaterial{};

    ASSERT_THAT(sphereMaterial == defaultMaterial, true);
}

TEST_F(LightAndShadingFeature, SphereMayBeAssignedMaterial){
    Sphere sphere{};
    Material material{};
    material.setAmbient(1);
    sphere.setMaterial(material);
    Material sphereMaterial = sphere.getMaterial();

    ASSERT_THAT(sphereMaterial == material, true);
}

TEST_F(LightAndShadingFeature, LightingWithEyeBetweenLightAndSurface){
    Tuple eyeVector{0,0,-1,TupleType::vector};
    Tuple lightPosition{0,0,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition, lightColor};
    Color result = light.light(material, position, eyeVector, normalVector);
    Color trueResult{1.9, 1.9, 1.9};

    ASSERT_THAT(result == trueResult, true);
}

TEST_F(LightAndShadingFeature, LightingWithEyeBetweenLightAndSurfaceEyeOffset45){
    double coordinateValue{sqrt(2)/2};
    Tuple eyeVector{0,coordinateValue, -coordinateValue,TupleType::vector};
    Tuple lightPosition{0,0,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition, lightColor};
    Color result = light.light(material, position, eyeVector, normalVector);
    Color trueResult{1.0, 1.0, 1.0};

    ASSERT_THAT(result == trueResult, true);
}

TEST_F(LightAndShadingFeature, LightingWithEyeOppositeSurfaceLightOffset45){
    Tuple eyeVector{0,0,-1,TupleType::vector};
    Tuple lightPosition{0,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition, lightColor};
    Color result = light.light(material, position, eyeVector, normalVector);
    Color trueResult{0.7364, 0.7364, 0.7364};

    ASSERT_THAT(result == trueResult, true);
}

TEST_F(LightAndShadingFeature, LightingWithEyeInPathOfReflectionVector){
    double coordinateValue{sqrt(2)/2};
    Tuple eyeVector{0,-coordinateValue,-coordinateValue,TupleType::vector};
    Tuple lightPosition{0,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition, lightColor};
    Color result = light.light(material, position, eyeVector, normalVector);
    Color trueResult{1.6364, 1.6364, 1.6364};

    ASSERT_THAT(result == trueResult, true);
}

TEST_F(LightAndShadingFeature, LightingWithLightBehindSurface){
    Tuple eyeVector{0,0,-1,TupleType::vector};
    Tuple lightPosition{0,0,10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition, lightColor};
    Color result = light.light(material, position, eyeVector, normalVector);
    Color trueResult{0.1, 0.1, 0.1};

    ASSERT_THAT(result == trueResult, true);
}

TEST_F(LightAndShadingFeature, TwoLightsAreEqual){
    Tuple lightPosition{0,0,10, TupleType::point};
    Color lightColor{1,1,1};
    Light light1{lightPosition, lightColor};

    Light light2{lightPosition, lightColor};

    ASSERT_THAT(light1 == light2, true);
}

TEST_F(LightAndShadingFeature, TwoLightsAreNotEqual){
    Tuple lightPosition{0,0,10, TupleType::point};
    Color lightColor{1,1,1};
    Light light1{lightPosition, lightColor};

    Tuple light2Position{0,10,10, TupleType::point};
    Light light2{light2Position, lightColor};

    Color light3Color{0,1,1};
    Light light3{lightPosition, light3Color};

    ASSERT_THAT(light1 == light2, false);
    ASSERT_THAT(light1 == light3, false);
}



#include "gmock/gmock.h"
#include "Pattern.h"
#include "Stripe.h"
#include "Plane.h"
#include "Light.h"
#include "Sphere.h"
#include "Gradient.h"
#include "Rings.h"
#include "checker.h"

using namespace testing;

class PatternFeature : public Test {
public:
    Color black{0,0,0};
    Color white{1,1,1};
};

TEST_F(PatternFeature, CreatingStripePattern) {
    Stripe stripe{};
    Color colorA = stripe.getColor(0);
    Color colorB = stripe.getColor(1);

    ASSERT_THAT(colorA==white, true);
    ASSERT_THAT(colorB==black, true);
}

TEST_F(PatternFeature, StripePatternIsConstantInY) {
    Stripe stripe{};
    Plane plane{};

    Tuple point1{0,0,0,TupleType::point};
    Tuple point2{0,1,0,TupleType::point};
    Tuple point3{0,2,0,TupleType::point};
    Color color1 = stripe.patternAtShape(plane,point1);
    Color color2 = stripe.patternAtShape(plane,point2);
    Color color3 = stripe.patternAtShape(plane,point3);

    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==white,true);
    ASSERT_THAT(color3==white,true);
}

TEST_F(PatternFeature, StripePatternIsConstantInZ) {
    Stripe stripe{};
    Plane plane{};

    Tuple point1{0,0,0,TupleType::point};
    Tuple point2{0,0,1,TupleType::point};
    Tuple point3{0,0,2,TupleType::point};
    Color color1 = stripe.patternAtShape(plane,point1);
    Color color2 = stripe.patternAtShape(plane,point2);
    Color color3 = stripe.patternAtShape(plane,point3);

    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==white,true);
    ASSERT_THAT(color3==white,true);
}

TEST_F(PatternFeature, StripePatternAlternatesInX) {
    Stripe stripe{};
    Plane plane{};

    Tuple point1{0,0,0,TupleType::point};
    Tuple point2{0.9,0,0,TupleType::point};
    Tuple point3{1,0,0,TupleType::point};
    Tuple point4{-0.1,0,0,TupleType::point};
    Tuple point5{-1,0,0,TupleType::point};
    Tuple point6{-1.1,0,0,TupleType::point};
    Color color1 = stripe.patternAtShape(plane,point1);
    Color color2 = stripe.patternAtShape(plane,point2);
    Color color3 = stripe.patternAtShape(plane,point3);
    Color color4 = stripe.patternAtShape(plane,point4);
    Color color5 = stripe.patternAtShape(plane,point5);
    Color color6 = stripe.patternAtShape(plane,point6);

    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==white,true);
    ASSERT_THAT(color3==black,true);
    ASSERT_THAT(color4==black,true);
    ASSERT_THAT(color5==black,true);
    ASSERT_THAT(color6==white,true);
}

TEST_F(PatternFeature, LightingWithPatternApplied) {
    Stripe stripe{};
    Plane plane{};
    Material material{};
    material.setPattern(std::make_shared<Stripe>(stripe));
    material.setAmbient(1);
    material.setDiffuse(0);
    material.setSpecular(0);
    Tuple eyeVector{0,0,-1,TupleType::vector};
    Tuple normalVector{0,0,-1,TupleType::vector};
    Tuple lightPoint{0,0,-10,TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPoint,lightColor};
    Tuple point1{0.9,0,0,TupleType::point};
    Tuple point2{1.1,0,0,TupleType::point};
    Color color1 = light.light(material,plane,point1,eyeVector,normalVector);
    Color color2 = light.light(material,plane,point2,eyeVector,normalVector);
    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==black,true);
}

TEST_F(PatternFeature, StipesWithObjectTransformation) {
    Sphere sphere{};
    Transformer scaler{Transformation::scaling,2,2,2};
    sphere.setTransformation(scaler);
    Stripe stripe{};
    Tuple point{1.5,0,0,TupleType::point};
    Color color = stripe.patternAtShape(sphere,point);
    ASSERT_THAT(color==white,true);
}

TEST_F(PatternFeature, StipesWithPatternTransformation) {
    Sphere sphere{};
    Transformer scaler{Transformation::scaling,2,2,2};
    Stripe stripe{};
    stripe.setTransformation(scaler);
    Tuple point{1.5,0,0,TupleType::point};
    Color color = stripe.patternAtShape(sphere,point);
    ASSERT_THAT(color==white,true);
}

TEST_F(PatternFeature, StipesWithBothObjectAndPatternTransformation) {
    Sphere sphere{};
    Transformer scaler{Transformation::scaling,2,2,2};
    sphere.setTransformation(scaler);
    Stripe stripe{};
    Transformer translator{Transformation::translation,0.5,0,0};
    stripe.setTransformation(translator);
    Tuple point{2.5,0,0,TupleType::point};
    Color color = stripe.patternAtShape(sphere,point);
    ASSERT_THAT(color==white,true);
}

TEST_F(PatternFeature, GradientLinearlyInterpolatesBetweenColors) {
    Gradient gradient{};
    Plane plane{};
    Color color1 = gradient.patternAtShape(plane,Tuple{0,0,0,TupleType::point});
    Color color2 = gradient.patternAtShape(plane,Tuple{0.25,0,0,TupleType::point});
    Color color3 = gradient.patternAtShape(plane,Tuple{0.5,0,0,TupleType::point});
    Color color4 = gradient.patternAtShape(plane,Tuple{0.75,0,0,TupleType::point});
    ASSERT_THAT(color1==white, true);
    Color correctColor2{0.75,0.75,0.75};
    Color correctColor3{0.5,0.5,0.5};
    Color correctColor4{0.25,0.25,0.25};
    ASSERT_THAT(color2==correctColor2,true);
    ASSERT_THAT(color3==correctColor3,true);
    ASSERT_THAT(color4==correctColor4,true);
}

TEST_F(PatternFeature, RingShouldExtendInBothXAndZ) {
    Rings ring{};
    Plane plane{};
    Color color1 = ring.patternAtShape(plane,Tuple{0,0,0,TupleType::point});
    Color color2 = ring.patternAtShape(plane,Tuple{1,0,0,TupleType::point});
    Color color3 = ring.patternAtShape(plane,Tuple{0,0,1,TupleType::point});
    Color color4 = ring.patternAtShape(plane,Tuple{0.708,0,0.708,TupleType::point});
    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==black,true);
    ASSERT_THAT(color3==black,true);
    ASSERT_THAT(color4==black,true);
}

TEST_F(PatternFeature, CheckersShouldRepeatInX) {
    Checker checker{};
    Plane plane{};
    Color color1 = checker.patternAtShape(plane,Tuple{0,0,0,TupleType::point});
    Color color2 = checker.patternAtShape(plane,Tuple{0.99,0,0,TupleType::point});
    Color color3 = checker.patternAtShape(plane,Tuple{1.01,0,0,TupleType::point});
    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==white,true);
    ASSERT_THAT(color3==black,true);
}

TEST_F(PatternFeature, CheckersShouldRepeatInY) {
    Checker checker{};
    Plane plane{};
    Color color1 = checker.patternAtShape(plane,Tuple{0,0,0,TupleType::point});
    Color color2 = checker.patternAtShape(plane,Tuple{0,0.99,0,TupleType::point});
    Color color3 = checker.patternAtShape(plane,Tuple{0,1.01,0,TupleType::point});
    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==white,true);
    ASSERT_THAT(color3==black,true);
}

TEST_F(PatternFeature, CheckersShouldRepeatInZ) {
    Checker checker{};
    Plane plane{};
    Color color1 = checker.patternAtShape(plane,Tuple{0,0,0,TupleType::point});
    Color color2 = checker.patternAtShape(plane,Tuple{0,0,0.99,TupleType::point});
    Color color3 = checker.patternAtShape(plane,Tuple{0,0,1.01,TupleType::point});
    ASSERT_THAT(color1==white,true);
    ASSERT_THAT(color2==white,true);
    ASSERT_THAT(color3==black,true);
}

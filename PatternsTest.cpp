#include "gmock/gmock.h"
#include "Pattern.h"
#include "Stripe.h"
#include "Plane.h"

using namespace testing;

class PatternFeature : public Test {

};

TEST_F(PatternFeature, CreatingStripePattern) {
    Stripe stripe{};
    Color colorA = stripe.getColor(0);
    Color colorB = stripe.getColor(1);
    Color black{0,0,0};
    Color white{1,1,1};

    ASSERT_THAT(colorA==white, true);
    ASSERT_THAT(colorB==black, true);
}

TEST_F(PatternFeature, StripePatternIsConstantInY) {
    Stripe stripe{};
    Plane plane{};
    Color black{0,0,0};
    Color white{1,1,1};

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
    Color black{0,0,0};
    Color white{1,1,1};

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
    Color black{0,0,0};
    Color white{1,1,1};

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

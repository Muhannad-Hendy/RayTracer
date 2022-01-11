#include "gmock/gmock.h"
#include "Color.h"

using namespace testing;

class ColorFeature : public Test {
};

TEST_F(ColorFeature, ColorsAreRGBTuples){
    Color c{-0.5, 0.4, 1.7};
    ASSERT_THAT(c.getRed(), Eq(-0.5));
    ASSERT_THAT(c.getGreen(), Eq(0.4));
    ASSERT_THAT(c.getBlue(), Eq(1.7));
}

TEST_F(ColorFeature, AddingColors){
    Color c1{0.9, 0.6, 0.75};
    Color c2{0.7, 0.1, 0.25};
    Color correctValue{1.6, 0.7, 1.0};
    Color sum = c1 + c2;
    ASSERT_THAT(correctValue == sum, true);
}

TEST_F(ColorFeature, SubtractingColors){
    Color c1{0.9, 0.6, 0.75};
    Color c2{0.7, 0.1, 0.25};
    Color correctValue{0.2, 0.5, 0.5};
    Color sum = c1 - c2;
    ASSERT_THAT(correctValue == sum, true);
}

TEST_F(ColorFeature, MultiplyingColorByScalar){
    Color c{0.2, 0.3, 0.4};
    Color correctValue{0.4, 0.6, 0.8};
    Color cScaled = c * 2;
    ASSERT_THAT(correctValue == cScaled, true);
}

TEST_F(ColorFeature, MultiplyingColorByColor){
    Color c1{1, 0.2, 0.4};
    Color c2{0.9, 1, 0.1};
    Color correctValue{0.9, 0.2, 0.04};
    Color colorProduct = c1 * c2;
    ASSERT_THAT(correctValue == colorProduct, true);
}

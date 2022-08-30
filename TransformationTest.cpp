#include "gmock/gmock.h"
#include "Tuple.h"
#include "Transformer.h"
#include "Ray.h"
#include <cmath>
#define PI 3.14159265
using namespace testing;

class TransformationFeature : public Test {

};

TEST_F(TransformationFeature, MultiplyingByTranslationMatrix){
    Transformer translator{Transformation::translation,5,-3,2};
    Tuple point{-3,4,5,TupleType::point};

    Tuple translated = translator.transform(point);
    Tuple trueValue{2,1,7,TupleType::point};

    ASSERT_THAT(translated == trueValue, true);
}

TEST_F(TransformationFeature, MultiplyingByTheInverseOfTranslationMatrix){
    Transformer translator{Transformation::translation,5,-3,2};
    translator = translator.invert();
    Tuple point{-3,4,5,TupleType::point};

    Tuple translated = translator.transform(point);
    Tuple trueValue{-8,7,3,TupleType::point};

    ASSERT_THAT(translated == trueValue, true);
}

TEST_F(TransformationFeature, TranslationDoesNotAffectVectors){
    Transformer translator{Transformation::translation,5,-3,2};
    Tuple vector{-3,4,5,TupleType::vector};
    Tuple translated = translator.transform(vector);
    Tuple trueValue{-3,4,5,TupleType::vector};
    ASSERT_THAT(translated == trueValue, true);
}

TEST_F(TransformationFeature, ScalingMatrixAppliedToPoint){
    Transformer scalar{Transformation::scaling,2,3,4};
    Tuple point{-4,6,8,TupleType::point};
    Tuple scaled = scalar.transform(point);
    Tuple trueValue{-8, 18,32, TupleType::point};

    ASSERT_THAT(scaled == trueValue, true);
}

TEST_F(TransformationFeature, ScalingMatrixAppliedToVector){
    Transformer scalar{Transformation::scaling,2,3,4};
    Tuple vector{-4,6,8,TupleType::vector};
    Tuple scaled = scalar.transform(vector);
    Tuple trueValue{-8,18,32,TupleType::vector};

    ASSERT_THAT(scaled == trueValue, true);
}

TEST_F(TransformationFeature, MultiplyingByInverseOfScalingMatrix){
    Transformer scalar{Transformation::scaling,2,3,4};
    scalar = scalar.invert();
    Tuple vector{-4,6,8,TupleType::vector};
    Tuple scaled = scalar.transform(vector);
    Tuple trueValue{-2,2,2,TupleType::vector};

    ASSERT_THAT(scaled == trueValue, true);
}

TEST_F(TransformationFeature, ReflectionIsScalingByNegativeValue){
    Transformer scalar{Transformation::scaling,-1,1,1};
    Tuple point{2,3,4,TupleType::point};
    Tuple reflected = scalar.transform(point);
    Tuple trueValue{-2,3,4, TupleType::point};

    ASSERT_THAT(reflected == trueValue, true);
}

TEST_F(TransformationFeature, RotatingPointAroundXAxis){
    Tuple point{0,1,0,TupleType::point};
    Transformer halfQuarter{Transformation::xRotation, PI/4};
    Transformer fullQuarter{Transformation::xRotation, PI/2};

    Tuple halfQuarterRotated = halfQuarter.transform(point);
    Tuple trueValueHalfQuarter{0, 0.7071, 0.7071,TupleType::point};
    Tuple fullQuarterRotated = fullQuarter.transform(point);
    Tuple trueValueFullQuarter{0, 0, 1,TupleType::point};

    ASSERT_THAT(halfQuarterRotated == trueValueHalfQuarter, true);
    ASSERT_THAT(fullQuarterRotated == trueValueFullQuarter, true);
}

TEST_F(TransformationFeature, InverseOfXRotationRotatesTheOppositeDirection){
    Tuple point{0,1,0,TupleType::point};
    Transformer halfQuarter{Transformation::xRotation, PI/4};
    halfQuarter = halfQuarter.invert();
    Tuple rotated = halfQuarter.transform(point);
    Tuple trueValue{0, sqrt(2)/2, -sqrt(2)/2, TupleType::point};

    ASSERT_THAT(rotated == trueValue, true);
}

TEST_F(TransformationFeature, RotatingPointAroundYAxis){
    Tuple point{0,0,1,TupleType::point};
    Transformer halfQuarter{Transformation::yRotation, PI / 4};
    Transformer fullQuarter{Transformation::yRotation, PI / 2};

    Tuple halfQuarterRotated = halfQuarter.transform(point);
    Tuple fullQuarterRotated = fullQuarter.transform(point);

    Tuple trueValueHalfQuarter{sqrt(2)/2, 0, sqrt(2)/2, TupleType::point};
    Tuple trueValueFullQuarter{1,0,0,TupleType::point};

    ASSERT_THAT(halfQuarterRotated == trueValueHalfQuarter, true);
    ASSERT_THAT(fullQuarterRotated == trueValueFullQuarter, true);
}

TEST_F(TransformationFeature, RotatingPointAroundZAxis){
    Tuple point{0,1,0,TupleType::point};
    Transformer halfQuarter{Transformation::zRotation, PI / 4};
    Transformer fullQuarter{Transformation::zRotation, PI / 2};
    Tuple halfQuarterRotated = halfQuarter.transform(point);
    Tuple fullQuarterRotated = fullQuarter.transform(point);

    Tuple trueValueHalfQuarter{-sqrt(2)/2, sqrt(2)/2, 0, TupleType::point};
    Tuple trueValueFullQuarter{-1,0,0,TupleType::point};

    ASSERT_THAT(halfQuarterRotated == trueValueHalfQuarter, true);
    ASSERT_THAT(fullQuarterRotated == trueValueFullQuarter, true);
}

TEST_F(TransformationFeature,ShearingTransformationMovesXInProportionToY){
    Transformer shearing{1,0,0,0,0,0};
    Tuple point{2,3,4,TupleType::point};
    Tuple sheared = shearing.transform(point);
    Tuple trueValue{5,3,4, TupleType::point};

    ASSERT_THAT(sheared == trueValue, true);
}

TEST_F(TransformationFeature, IndividualTransformationsAreAppliedInSequence){
    Tuple point{1,0,1,TupleType::point};
    Transformer rotator{Transformation::xRotation, PI / 2};
    Transformer scalar{Transformation::scaling, 5,5,5};
    Transformer translator{Transformation::translation,10,5,7};

    Tuple point2 = rotator.transform(point);
    Tuple point3 = scalar.transform(point2);
    Tuple point4 = translator.transform(point3);

    Tuple trueValue{15,0,7,TupleType::point};
    ASSERT_THAT(point4 == trueValue, true);
}

TEST_F(TransformationFeature, ChainedTransformationsMustBeAppliedInReverseOrder){
    Tuple point{1,0,1,TupleType::point};
    Transformer rotator{Transformation::xRotation, PI / 2};
    Transformer scalar{Transformation::scaling, 5,5,5};
    Transformer translator{Transformation::translation,10,5,7};
    Transformer chain = rotator > scalar > translator; //reversal happens under the hood. The syntax is in natural order.

    Tuple transformed = chain.transform(point);
    Tuple trueValue{15,0,7,TupleType::point};
    ASSERT_THAT(transformed == trueValue, true);
}

TEST_F(TransformationFeature, TranslatingRay){
    Tuple point{1,2,3,TupleType::point};
    Tuple direction{0,1,0,TupleType::vector};
    Ray ray{point,direction};
    Transformer translator{Transformation::translation, 3,4,5};

    Ray rayTransformed = translator.transform(ray);
    Tuple truePointTransformed{4,6,8,TupleType::point};
    Tuple trueDirectionTransformed{0,1,0,TupleType::vector};

    Tuple pointTransformed = rayTransformed.getOrigin();
    ASSERT_THAT(pointTransformed == truePointTransformed, true);
    Tuple directionTransformed = rayTransformed.getDirection();
    ASSERT_THAT(directionTransformed == trueDirectionTransformed, true);
}

TEST_F(TransformationFeature, ScalingRay){
    Tuple point{1,2,3,TupleType::point};
    Tuple direction{0,1,0,TupleType::vector};
    Ray ray{point,direction};
    Transformer scalar{Transformation::scaling,2,3,4};

    Ray rayTransformed = scalar.transform(ray);
    Tuple truePointTransformed{2,6,12,TupleType::point};
    Tuple trueDirectionTransformed{0,3,0,TupleType::vector};

    Tuple pointTransformed = rayTransformed.getOrigin();
    ASSERT_THAT(pointTransformed == truePointTransformed, true);
    Tuple directionTransformed = rayTransformed.getDirection();
    ASSERT_THAT(directionTransformed == trueDirectionTransformed, true);
}

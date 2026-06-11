#include "gmock/gmock.h"
#include "Camera.h"
#include "Utilities.h"
#include "Tuple.h"
#include "Ray.h"

using namespace testing;

class CameraFeature : public Test {

};

TEST_F(CameraFeature, ConstructingCamera) {
    Camera camera{160, 120, util::PI/2};
    int correctHorizontal{160};
    int correctVertical{120};
    double correctField{util::PI/2};
    Matrix identity{4, MatrixType::identity};

    ASSERT_THAT(camera.getHorizontalSize() == correctHorizontal, true);
    ASSERT_THAT(camera.getVerticalSize() == correctVertical, true);
    ASSERT_THAT(camera.getFieldOfView() == correctField, true);
    ASSERT_THAT(camera.getTransformation().getTransformationMatrix() == identity, true);
}

TEST_F(CameraFeature, PixelSizeHorizontalCanvas) {
    Camera camera{200,125,util::PI/2};
    double correctSize{0.01};
    double cameraPixelSize = camera.getPixelSize();

    ASSERT_THAT(util::equals(cameraPixelSize,correctSize), true);
}

TEST_F(CameraFeature, PixelSizeVerticalCanvas) {
    Camera camera{125,200,util::PI/2};
    double correctSize{0.01};
    double cameraPixelSize = camera.getPixelSize();

    ASSERT_THAT(util::equals(cameraPixelSize,correctSize), true);
}

TEST_F(CameraFeature, ConstructingRayThroughCenterOfCanvas) {
    Camera camera{201,101,util::PI/2};
    Ray ray = camera.generateRayForPixel(100,50);
    Tuple rayOrigin = ray.getOrigin();
    Tuple rayDirection = ray.getDirection();

    Tuple correctOrigin{0,0,0,TupleType::point};
    Tuple correctDirection{0,0,-1,TupleType::vector};
    ASSERT_THAT(rayOrigin==correctOrigin, true);
    ASSERT_THAT(rayDirection==correctDirection, true);
}

TEST_F(CameraFeature, ConstructingRayThroughCornerOfCanvas) {
    Camera camera{201,101,util::PI/2};
    Ray ray = camera.generateRayForPixel(0,0);
    Tuple rayOrigin = ray.getOrigin();
    Tuple rayDirection = ray.getDirection();

    Tuple correctOrigin{0,0,0,TupleType::point};
    Tuple correctDirection{0.66519,0.33259,-0.66851,TupleType::vector};
    ASSERT_THAT(rayOrigin==correctOrigin, true);
    ASSERT_THAT(rayDirection==correctDirection, true);
}

TEST_F(CameraFeature, ConstructingRayWhenCameraIsTransformed) {
    Camera camera{201,101,util::PI/2};
    Transformer yRotation{Transformation::yRotation,util::PI/4};
    Transformer translation{Transformation::translation,0,-2,5};
    camera.setCameraTransformation(translation>yRotation);
    Ray ray = camera.generateRayForPixel(100,50);
    Tuple rayOrigin = ray.getOrigin();
    Tuple rayDirection = ray.getDirection();

    Tuple correctOrigin{0,2,-5,TupleType::point};
    Tuple correctDirection{std::sqrt(2)/2,0,-std::sqrt(2)/2,TupleType::vector};
    ASSERT_THAT(rayOrigin==correctOrigin, true);
    ASSERT_THAT(rayDirection==correctDirection, true);
}

TEST_F(CameraFeature, RenderingWorldWithCamera) {
    World world{};
    Camera camera{11,11,util::PI/2};
    Tuple from{0,0,-5,TupleType::point};
    Tuple to{0,0,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformation{from,to,up};
    camera.setCameraTransformation(viewTransformation);
    const Canvas& image=camera.render(world);
    Color* pixelColor = image.getPixelColor(5,5);
    Color correctColor{0.38066,0.47583,0.2855};
    ASSERT_THAT(*pixelColor==correctColor, true);
}

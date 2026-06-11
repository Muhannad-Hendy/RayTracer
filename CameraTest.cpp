#include "gmock/gmock.h"
#include "Camera.h"
#include "Utilities.h"

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

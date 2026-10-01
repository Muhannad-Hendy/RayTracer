#include "gmock/gmock.h"
#include "Camera.h"
#include "Utilities.h"
#include "Tuple.h"
#include "Ray.h"
#include "Light.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Stripe.h"
#include "Gradient.h"
#include "checker.h"
#include "cube.h"
#include "cylinder.h"
#include "group.h"

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

TEST_F(CameraFeature, DISABLED_RenderingWorldScene) {
    Sphere floor{};
    Transformer scaler{Transformation::scaling,10,0.01,10};
    floor.setTransformation(scaler);
    Material floorMaterial{};
    Color floorColor{1,0.9,0.9};
    floorMaterial.setColor(floorColor);
    floorMaterial.setSpecular(0);
    floor.setMaterial(floorMaterial);

    Sphere leftWall{};
    Transformer translation{Transformation::translation, 0,0,5};
    Transformer leftWallXRotation{Transformation::xRotation,util::PI/2};
    Transformer leftWallYRotation{Transformation::yRotation,util::PI/-4};
    leftWall.setTransformation(scaler>leftWallXRotation>leftWallYRotation>translation);
    leftWall.setMaterial(floorMaterial);

    Sphere rightWall{};
    Transformer rightWallYRotation{Transformation::yRotation,util::PI/4};
    rightWall.setTransformation(scaler>leftWallXRotation>rightWallYRotation>translation);
    rightWall.setMaterial(floorMaterial);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,-0.5,1,0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middleSphere.setMaterial(middleMaterial);

    Sphere rightSphere{};
    Transformer rightSphereTranslation{Transformation::translation,1.5,0.5,-0.5};
    Transformer rightSphereScaling{Transformation::scaling,0.5,0.5,0.5};
    rightSphere.setTransformation(rightSphereScaling>rightSphereTranslation);
    Material rightSphereMaterial{};
    Color rightSphereColor{0.5,1,0.1};
    rightSphereMaterial.setColor(rightSphereColor);
    rightSphereMaterial.setDiffuse(0.7);
    rightSphereMaterial.setSpecular(0.3);
    rightSphere.setMaterial(rightSphereMaterial);

    Sphere leftSphere{};
    Transformer leftSphereTranslation{Transformation::translation,-1.5,0.33,-0.75};
    Transformer leftSphereScaling{Transformation::scaling,0.33,0.33,0.33};
    leftSphere.setTransformation(leftSphereScaling>leftSphereTranslation);
    Material leftSphereMaterial{};
    Color leftSphereColor{1,0.8,0.1};
    leftSphereMaterial.setColor(leftSphereColor);
    leftSphereMaterial.setDiffuse(0.7);
    leftSphereMaterial.setSpecular(0.3);
    leftSphere.setMaterial(leftSphereMaterial);

    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Sphere>(floor), light);
    world.addShape(std::make_unique<Sphere>(leftWall));
    world.addShape(std::make_unique<Sphere>(rightWall));
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Sphere>(rightSphere));
    world.addShape(std::make_unique<Sphere>(leftSphere));

    Camera camera{500,250,util::PI/3};
    Tuple from{0,1.5,-5,TupleType::point};
    Tuple to{0,1,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingScene.ppm");
}

TEST_F(CameraFeature, DISABLED_Rendering3DSphere) {
    Sphere sphere{};
    Material sphereMaterial{};
    Color materialColor{0.25,0.88,0.82};
    sphereMaterial.setColor(materialColor);
    sphere.setMaterial(sphereMaterial);
    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    Camera camera{500,500,util::PI/3};
    Tuple from{0,0,-5,TupleType::point};
    Tuple to{0,0,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    World world{std::make_unique<Sphere>(sphere),light};
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/Sphere3D.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingWorldSceneWithShadow) {
    Sphere floor{};
    Transformer scaler{Transformation::scaling,10,0.01,10};
    floor.setTransformation(scaler);
    Material floorMaterial{};
    Color floorColor{1,0.9,0.9};
    floorMaterial.setColor(floorColor);
    floorMaterial.setSpecular(0);
    floor.setMaterial(floorMaterial);

    Sphere leftWall{};
    Transformer translation{Transformation::translation, 0,0,5};
    Transformer leftWallXRotation{Transformation::xRotation,util::PI/2};
    Transformer leftWallYRotation{Transformation::yRotation,util::PI/-4};
    leftWall.setTransformation(scaler>leftWallXRotation>leftWallYRotation>translation);
    leftWall.setMaterial(floorMaterial);

    Sphere rightWall{};
    Transformer rightWallYRotation{Transformation::yRotation,util::PI/4};
    rightWall.setTransformation(scaler>leftWallXRotation>rightWallYRotation>translation);
    rightWall.setMaterial(floorMaterial);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,-0.5,1,0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middleSphere.setMaterial(middleMaterial);

    Sphere rightSphere{};
    Transformer rightSphereTranslation{Transformation::translation,1.5,0.5,-0.5};
    Transformer rightSphereScaling{Transformation::scaling,0.5,0.5,0.5};
    rightSphere.setTransformation(rightSphereScaling>rightSphereTranslation);
    Material rightSphereMaterial{};
    Color rightSphereColor{0.5,1,0.1};
    rightSphereMaterial.setColor(rightSphereColor);
    rightSphereMaterial.setDiffuse(0.7);
    rightSphereMaterial.setSpecular(0.3);
    rightSphere.setMaterial(rightSphereMaterial);

    Sphere leftSphere{};
    Transformer leftSphereTranslation{Transformation::translation,-1.5,0.33,-0.75};
    Transformer leftSphereScaling{Transformation::scaling,0.33,0.33,0.33};
    leftSphere.setTransformation(leftSphereScaling>leftSphereTranslation);
    Material leftSphereMaterial{};
    Color leftSphereColor{1,0.8,0.1};
    leftSphereMaterial.setColor(leftSphereColor);
    leftSphereMaterial.setDiffuse(0.7);
    leftSphereMaterial.setSpecular(0.3);
    leftSphere.setMaterial(leftSphereMaterial);

    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Sphere>(floor), light);
    world.addShape(std::make_unique<Sphere>(leftWall));
    world.addShape(std::make_unique<Sphere>(rightWall));
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Sphere>(rightSphere));
    world.addShape(std::make_unique<Sphere>(leftSphere));

    Camera camera{1000,500,util::PI/3};
    Tuple from{0,1.5,-5,TupleType::point};
    Tuple to{0,1,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithShadow.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingWorldSceneWithShadowOnPlane) {
    Plane floor{};
    Material floorMaterial{};
    Color floorColor{0.87,0.29,0.17};
    floorMaterial.setColor(floorColor);
    floor.setMaterial(floorMaterial);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,-0.5,1,0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middleSphere.setMaterial(middleMaterial);

    Sphere rightSphere{};
    Transformer rightSphereTranslation{Transformation::translation,1.5,0.5,-0.5};
    Transformer rightSphereScaling{Transformation::scaling,0.5,0.5,0.5};
    rightSphere.setTransformation(rightSphereScaling>rightSphereTranslation);
    Material rightSphereMaterial{};
    Color rightSphereColor{0.5,1,0.1};
    rightSphereMaterial.setColor(rightSphereColor);
    rightSphereMaterial.setDiffuse(0.7);
    rightSphereMaterial.setSpecular(0.3);
    rightSphere.setMaterial(rightSphereMaterial);

    Sphere leftSphere{};
    Transformer leftSphereTranslation{Transformation::translation,-1.5,0.33,-0.75};
    Transformer leftSphereScaling{Transformation::scaling,0.33,0.33,0.33};
    leftSphere.setTransformation(leftSphereScaling>leftSphereTranslation);
    Material leftSphereMaterial{};
    Color leftSphereColor{1,0.8,0.1};
    leftSphereMaterial.setColor(leftSphereColor);
    leftSphereMaterial.setDiffuse(0.7);
    leftSphereMaterial.setSpecular(0.3);
    leftSphere.setMaterial(leftSphereMaterial);

    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Sphere>(rightSphere));
    world.addShape(std::make_unique<Sphere>(leftSphere));

    Camera camera{1000,500,util::PI/3};
    Tuple from{0,1.5,-5,TupleType::point};
    Tuple to{0,1,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithShadowOnPlane.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithStripes) {
    Plane floor{};
    Material floorMaterial{};
    Color floorColor{0.87,0.29,0.17};
    floorMaterial.setColor(floorColor);
    Stripe stripe{};
    floorMaterial.setPattern(std::make_shared<Stripe>(stripe));
    floor.setMaterial(floorMaterial);


    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,-0.5,1,0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middleMaterial.setPattern(std::make_shared<Stripe>(stripe));
    middleSphere.setMaterial(middleMaterial);

    Sphere rightSphere{};
    Transformer rightSphereTranslation{Transformation::translation,1.5,0.5,-0.5};
    Transformer rightSphereScaling{Transformation::scaling,0.5,0.5,0.5};
    rightSphere.setTransformation(rightSphereScaling>rightSphereTranslation);
    Material rightSphereMaterial{};
    Color rightSphereColor{0.5,1,0.1};
    rightSphereMaterial.setColor(rightSphereColor);
    rightSphereMaterial.setDiffuse(0.7);
    rightSphereMaterial.setSpecular(0.3);
    rightSphere.setMaterial(rightSphereMaterial);

    Sphere leftSphere{};
    Transformer leftSphereTranslation{Transformation::translation,-1.5,0.33,-0.75};
    Transformer leftSphereScaling{Transformation::scaling,0.33,0.33,0.33};
    leftSphere.setTransformation(leftSphereScaling>leftSphereTranslation);
    Material leftSphereMaterial{};
    Color leftSphereColor{1,0.8,0.1};
    leftSphereMaterial.setColor(leftSphereColor);
    leftSphereMaterial.setDiffuse(0.7);
    leftSphereMaterial.setSpecular(0.3);
    leftSphere.setMaterial(leftSphereMaterial);

    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Sphere>(rightSphere));
    world.addShape(std::make_unique<Sphere>(leftSphere));

    Camera camera{500,250,util::PI/3};
    Tuple from{0,1.5,-5,TupleType::point};
    Tuple to{0,1,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithStripes.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithGradient) {
    Plane floor{};
    Material floorMaterial{};
    floor.setMaterial(floorMaterial);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,-0.5,1,0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middleSphere.setMaterial(middleMaterial);

    Color blue{0,0.5,1};
    Color red{1,0.5,0};
    Gradient gradient{red,blue};

    Sphere rightSphere{};
    Transformer rightSphereTranslation{Transformation::translation,1.5,0.5,-0.5};
    Transformer rightSphereScaling{Transformation::scaling,0.5,0.5,0.5};
    rightSphere.setTransformation(rightSphereScaling>rightSphereTranslation);
    Material rightSphereMaterial{};
    Color rightSphereColor{0.5,1,0.1};
    rightSphereMaterial.setColor(rightSphereColor);
    rightSphereMaterial.setDiffuse(0.7);
    rightSphereMaterial.setSpecular(0.3);
    Transformer gradientTranslation{Transformation::translation,2,0,0};
    gradient.setTransformation(gradientTranslation);
    rightSphereMaterial.setPattern(std::make_shared<Gradient>(gradient));
    rightSphere.setMaterial(rightSphereMaterial);

    Sphere leftSphere{};
    Transformer leftSphereTranslation{Transformation::translation,-1.5,0.33,-0.75};
    Transformer leftSphereScaling{Transformation::scaling,0.33,0.33,0.33};
    leftSphere.setTransformation(leftSphereScaling>leftSphereTranslation);
    Material leftSphereMaterial{};
    Color leftSphereColor{1,0.8,0.1};
    leftSphereMaterial.setColor(leftSphereColor);
    leftSphereMaterial.setDiffuse(0.7);
    leftSphereMaterial.setSpecular(0.3);
    leftSphere.setMaterial(leftSphereMaterial);

    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Sphere>(rightSphere));
    world.addShape(std::make_unique<Sphere>(leftSphere));

    Camera camera{500,250,util::PI/3};
    Tuple from{0,1.5,-5,TupleType::point};
    Tuple to{0,1,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithGradient.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithChecker) {
    Checker checker{};
    Plane floor{};
    Material floorMaterial{};
    floorMaterial.setPattern(std::make_shared<Checker>(checker));
    floor.setMaterial(floorMaterial);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,-0.5,1,0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.3);
    middleSphere.setMaterial(middleMaterial);

    Sphere rightSphere{};
    Transformer rightSphereTranslation{Transformation::translation,1.5,0.5,-0.5};
    Transformer rightSphereScaling{Transformation::scaling,0.5,0.5,0.5};
    rightSphere.setTransformation(rightSphereScaling>rightSphereTranslation);
    Material rightSphereMaterial{};
    Color rightSphereColor{0.5,1,0.1};
    rightSphereMaterial.setColor(rightSphereColor);
    rightSphereMaterial.setDiffuse(0.7);
    rightSphereMaterial.setSpecular(0.3);
    rightSphere.setMaterial(rightSphereMaterial);

    Sphere leftSphere{};
    Transformer leftSphereTranslation{Transformation::translation,-1.5,0.33,-0.75};
    Transformer leftSphereScaling{Transformation::scaling,0.33,0.33,0.33};
    leftSphere.setTransformation(leftSphereScaling>leftSphereTranslation);
    Material leftSphereMaterial{};
    Color leftSphereColor{1,0.8,0.1};
    leftSphereMaterial.setColor(leftSphereColor);
    leftSphereMaterial.setDiffuse(0.7);
    leftSphereMaterial.setSpecular(0.3);
    leftSphere.setMaterial(leftSphereMaterial);

    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Sphere>(rightSphere));
    world.addShape(std::make_unique<Sphere>(leftSphere));

    Camera camera{1000,500,util::PI/3};
    Tuple from{0,1.5,-5,TupleType::point};
    Tuple to{0,1,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithChecker.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithReflections) {
    Checker checker{};
    Plane floor{};
    Material floorMaterial{};
    floorMaterial.setPattern(std::make_shared<Checker>(checker));
    floorMaterial.setReflectivity(0.1);
    floor.setMaterial(floorMaterial);

    Plane backWall{};
    Material wallMaterial{};
    wallMaterial.setReflectivity(0);
    wallMaterial.setColor(Color{0.86,0.08,0.24});
    backWall.setMaterial(wallMaterial);
    Transformer wallTranslation{Transformation::translation,0,0,3};
    Transformer wallRotation{Transformation::xRotation,-util::PI/2};
    backWall.setTransformation(wallRotation>wallTranslation);

    Plane leftWall{};
    Material leftWallMaterial{};
    leftWallMaterial.setReflectivity(1);
    leftWallMaterial.setSpecular(1);
    leftWallMaterial.setAmbient(0);
    leftWallMaterial.setDiffuse(0.1);
    leftWall.setMaterial(leftWallMaterial);
    Transformer leftWallTranslation{Transformation::translation,-3,0,0};
    Transformer leftWallRotation{Transformation::zRotation,-util::PI/2};
    leftWall.setTransformation(leftWallRotation>leftWallTranslation);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,0.7,1,-0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0.1,1,0.5};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.7);
    middleMaterial.setSpecular(0.7);
    middleSphere.setMaterial(middleMaterial);


    Tuple lightPosition{10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Plane>(backWall));
    world.addShape(std::make_unique<Plane>(leftWall));

    Camera camera{2000,1000,util::PI/3};
    Tuple from{5,3,-3,TupleType::point};
    Tuple to{0,0.5,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithReflections.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithTransparency) {
    Checker checker{};
    Plane floor{};
    Material floorMaterial{};
    floorMaterial.setPattern(std::make_shared<Checker>(checker));
    floorMaterial.setReflectivity(0.1);
    floor.setMaterial(floorMaterial);

    Plane backWall{};
    Material wallMaterial{};
    wallMaterial.setReflectivity(0);
    wallMaterial.setColor(Color{0.86,0.08,0.24});
    backWall.setMaterial(wallMaterial);
    Transformer wallTranslation{Transformation::translation,0,0,3};
    Transformer wallRotation{Transformation::xRotation,-util::PI/2};
    backWall.setTransformation(wallRotation>wallTranslation);

    Plane leftWall{};
    Material leftWallMaterial{};
    leftWallMaterial.setReflectivity(1);
    leftWallMaterial.setSpecular(1);
    leftWallMaterial.setAmbient(0);
    leftWallMaterial.setDiffuse(0.1);
    leftWall.setMaterial(leftWallMaterial);
    Transformer leftWallTranslation{Transformation::translation,-3,0,0};
    Transformer leftWallRotation{Transformation::zRotation,-util::PI/2};
    leftWall.setTransformation(leftWallRotation>leftWallTranslation);

    Sphere middleSphere{};
    Transformer middleTranslation{Transformation::translation,0.7,1,-0.5};
    middleSphere.setTransformation(middleTranslation);
    Material middleMaterial{};
    Color middleColor{0,0,0};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0.2);
    middleMaterial.setSpecular(1);
    middleMaterial.setTransparency(0.9);
    middleMaterial.setReflectivity(1);
    middleMaterial.setAmbient(0.2);
    middleMaterial.setShininess(300);
    middleSphere.setMaterial(middleMaterial);

    Sphere backSphere{};
    Transformer backTransform{Transformation::translation,-1,0.5,-1.5};
    Transformer backScaling{Transformation::scaling,0.5,0.5,0.5};
    backSphere.setTransformation(backScaling>backTransform);
    auto& backMaterial = backSphere.getMaterial();
    backMaterial.setColor(Color{0.25,0.88,0.82});
    backMaterial.setReflectivity(0.2);

    Sphere frontSphere{};
    Transformer frontTransform{Transformation::translation,2.2,0.5,-0.5};
    Transformer frontScaling{Transformation::scaling,0.5,0.5,0.5};
    frontSphere.setTransformation(frontScaling>frontTransform);
    auto& frontMaterial = frontSphere.getMaterial();
    frontMaterial.setColor(Color{0.99,0.99,0.59});
    frontMaterial.setReflectivity(0.2);


    Tuple lightPosition{10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Sphere>(middleSphere));
    world.addShape(std::make_unique<Plane>(backWall));
    world.addShape(std::make_unique<Plane>(leftWall));
    world.addShape(std::make_unique<Sphere>(backSphere));
    world.addShape(std::make_unique<Sphere>(frontSphere));

    Camera camera{2000,1000,util::PI/3};
    Tuple from{5,3,-3,TupleType::point};
    Tuple to{0,0.5,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithTransparency.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithCube) {
    Checker checker{};
    Plane floor{};
    Material floorMaterial{};
    floorMaterial.setPattern(std::make_shared<Checker>(checker));
    floorMaterial.setReflectivity(0.1);
    floor.setMaterial(floorMaterial);

    Plane backWall{};
    Material wallMaterial{};
    wallMaterial.setReflectivity(0);
    wallMaterial.setColor(Color{0.86,0.08,0.24});
    backWall.setMaterial(wallMaterial);
    Transformer wallTranslation{Transformation::translation,0,0,3};
    Transformer wallRotation{Transformation::xRotation,-util::PI/2};
    backWall.setTransformation(wallRotation>wallTranslation);

    Plane leftWall{};
    Material leftWallMaterial{};
    leftWallMaterial.setReflectivity(1);
    leftWallMaterial.setSpecular(1);
    leftWallMaterial.setAmbient(0);
    leftWallMaterial.setDiffuse(0.1);
    leftWall.setMaterial(leftWallMaterial);
    Transformer leftWallTranslation{Transformation::translation,-3,0,0};
    Transformer leftWallRotation{Transformation::zRotation,-util::PI/2};
    leftWall.setTransformation(leftWallRotation>leftWallTranslation);

    Cube middleSphere{};
    Transformer middleTranslation{Transformation::translation,0.7,0.501,-1.5};
    Transformer scaling{Transformation::scaling,0.5,0.5,0.5};
    middleSphere.setTransformation(scaling>middleTranslation);
    Material middleMaterial{};
    Color middleColor{0,0,0};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0);
    middleMaterial.setSpecular(1);
    middleMaterial.setTransparency(1);
    middleMaterial.setReflectivity(1);
    middleMaterial.setAmbient(0);
    middleMaterial.setShininess(300);
    middleMaterial.setRefractiveIndex(2.417);
    middleSphere.setMaterial(middleMaterial);

    Cube cube{};
    Transformer cubeTranslation{Transformation::translation,-1,0.251,1.3};
    Transformer cubeScaling{Transformation::scaling,0.25,0.25,0.25};
    Transformer cubeRotation{Transformation::yRotation,util::PI/4};
    cube.setTransformation(cubeRotation>cubeScaling>cubeTranslation);
    auto& cubeMaterial = cube.getMaterial();
    cubeMaterial.setColor(Color{0.294,0.325,0.125});
    cubeMaterial.setTransparency(1);
    cubeMaterial.setReflectivity(1);
    cubeMaterial.setRefractiveIndex(1.5);

    Sphere backSphere{};
    Transformer backTransform{Transformation::translation,-1,0.5,-1.5};
    Transformer backScaling{Transformation::scaling,0.5,0.5,0.5};
    backSphere.setTransformation(backScaling>backTransform);
    auto& backMaterial = backSphere.getMaterial();
    backMaterial.setColor(Color{0.25,0.88,0.82});
    backMaterial.setReflectivity(0.2);

    Sphere frontSphere{};
    Transformer frontTransform{Transformation::translation,2.2,0.5,-0.5};
    Transformer frontScaling{Transformation::scaling,0.5,0.5,0.5};
    frontSphere.setTransformation(frontScaling>frontTransform);
    auto& frontMaterial = frontSphere.getMaterial();
    frontMaterial.setColor(Color{0.99,0.99,0.59});
    frontMaterial.setReflectivity(0.2);


    Tuple lightPosition{10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Cube>(middleSphere));
    world.addShape(std::make_unique<Plane>(backWall));
    world.addShape(std::make_unique<Plane>(leftWall));
    world.addShape(std::make_unique<Sphere>(backSphere));
    world.addShape(std::make_unique<Sphere>(frontSphere));
    world.addShape(std::make_unique<Cube>(cube));

    Camera camera{2000,1000,util::PI/3};
    Tuple from{5,3,-3,TupleType::point};
//    Tuple from{0,10,0,TupleType::point};
    Tuple to{0,0.5,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithCube.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingSceneWithCylinders) {
    Checker checker{};
    Plane floor{};
    Material floorMaterial{};
    floorMaterial.setPattern(std::make_shared<Checker>(checker));
    floorMaterial.setReflectivity(0.1);
    floor.setMaterial(floorMaterial);

    Plane backWall{};
    Material wallMaterial{};
    wallMaterial.setReflectivity(0);
    wallMaterial.setColor(Color{0.86,0.08,0.24});
    backWall.setMaterial(wallMaterial);
    Transformer wallTranslation{Transformation::translation,0,0,3};
    Transformer wallRotation{Transformation::xRotation,-util::PI/2};
    backWall.setTransformation(wallRotation>wallTranslation);

    Plane leftWall{};
    Material leftWallMaterial{};
    leftWallMaterial.setReflectivity(1);
    leftWallMaterial.setSpecular(1);
    leftWallMaterial.setAmbient(0);
    leftWallMaterial.setDiffuse(0.1);
    leftWall.setMaterial(leftWallMaterial);
    Transformer leftWallTranslation{Transformation::translation,-3,0,0};
    Transformer leftWallRotation{Transformation::zRotation,-util::PI/2};
    leftWall.setTransformation(leftWallRotation>leftWallTranslation);

    Cube middleSphere{};
    Transformer middleTranslation{Transformation::translation,0.7,0.501,-1.5};
    Transformer scaling{Transformation::scaling,0.5,0.5,0.5};
    middleSphere.setTransformation(scaling>middleTranslation);
    Material middleMaterial{};
    Color middleColor{0,0,0};
    middleMaterial.setColor(middleColor);
    middleMaterial.setDiffuse(0);
    middleMaterial.setSpecular(1);
    middleMaterial.setTransparency(1);
    middleMaterial.setReflectivity(1);
    middleMaterial.setAmbient(0);
    middleMaterial.setShininess(300);
    middleMaterial.setRefractiveIndex(2.417);
    middleSphere.setMaterial(middleMaterial);

    Cylinder cylinder{};
    cylinder.setClosed(true);
    cylinder.setMaximum(2);
    cylinder.setMinimum(0);
    Transformer cylinderTranslation{Transformation::translation,-1,0.251,1.3};
    Transformer cylinderScaling{Transformation::scaling,0.5,0.5,0.5};
//    Transformer cylinderRotation{Transformation::yRotation,util::PI/4};
    cylinder.setTransformation(cylinderScaling>cylinderTranslation);
    auto& cylinderMaterial = cylinder.getMaterial();
    cylinderMaterial.setColor(Color{0.294,0.325,0.125});
    cylinderMaterial.setTransparency(1);
    cylinderMaterial.setReflectivity(1);
    cylinderMaterial.setRefractiveIndex(1.5);

    Sphere backSphere{};
    Transformer backTransform{Transformation::translation,-1,0.5,-1.5};
    Transformer backScaling{Transformation::scaling,0.5,0.5,0.5};
    backSphere.setTransformation(backScaling>backTransform);
    auto& backMaterial = backSphere.getMaterial();
    backMaterial.setColor(Color{0.25,0.88,0.82});
    backMaterial.setReflectivity(0.2);

    Sphere frontSphere{};
    Transformer frontTransform{Transformation::translation,2.2,0.5,-0.5};
    Transformer frontScaling{Transformation::scaling,0.5,0.5,0.5};
    frontSphere.setTransformation(frontScaling>frontTransform);
    auto& frontMaterial = frontSphere.getMaterial();
    frontMaterial.setColor(Color{0.99,0.99,0.59});
    frontMaterial.setReflectivity(0.2);


    Tuple lightPosition{10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world(std::make_unique<Plane>(floor), light);
    world.addShape(std::make_unique<Cube>(middleSphere));
    world.addShape(std::make_unique<Plane>(backWall));
    world.addShape(std::make_unique<Plane>(leftWall));
    world.addShape(std::make_unique<Sphere>(backSphere));
    world.addShape(std::make_unique<Sphere>(frontSphere));
    world.addShape(std::make_unique<Cylinder>(cylinder));

    Camera camera{2000,1000,util::PI/3};
    Tuple from{5,3,-3,TupleType::point};
//    Tuple from{0,10,0,TupleType::point};
    Tuple to{0,0.5,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingSceneWithCylinder.ppm");
}

TEST_F(CameraFeature, DISABLED_RenderingHexagonGroup) {
    Group hexagon{};
    for (int i = 0; i < 6; i++) {
        Sphere sphere{};
        Transformer sphereTranslator{Transformation::translation, 0, 0, -1};
        Transformer sphereScalar{Transformation::scaling, 0.25, 0.25, 0.25};
        sphere.setTransformation(sphereScalar > sphereTranslator);

        Cylinder edge{};
        edge.setMinimum(0);
        edge.setMaximum(1);
        Transformer edgeTranslator{Transformation::translation, 0, 0, -1};
        Transformer edgeYRotator{Transformation::yRotation, util::PI / -6};
        Transformer edgeZRotator{Transformation::zRotation, util::PI / -2};
        Transformer edgeScalar{Transformation::scaling, 0.25, 1, 0.25};
        edge.setTransformation(edgeScalar > edgeZRotator > edgeYRotator > edgeTranslator);

        auto hexagonSide = std::make_unique<Group>();
        Transformer rotator{Transformation::yRotation, util::PI / 3 * i};
        hexagonSide->setTransformation(rotator);
        hexagonSide->addChild(std::make_unique<Sphere>(sphere));
        hexagonSide->addChild(std::make_unique<Cylinder>(edge));

        hexagon.addChild(std::move(hexagonSide));
    }

    Tuple lightPosition{10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    World world{std::make_unique<Group>(std::move(hexagon)), light};
    Camera camera{2000,1000,util::PI/3};
    Tuple from{5,3,-3,TupleType::point};
//    Tuple from{0,10,0,TupleType::point};
    Tuple to{0,0.5,0,TupleType::point};
    Tuple up{0,1,0,TupleType::vector};
    Transformer viewTransformer{from,to,up};
    camera.setCameraTransformation(viewTransformer);
    const Canvas& image = camera.render(world);
    image.saveToPPM("../Output/renderingHexagonGroup.ppm");
}

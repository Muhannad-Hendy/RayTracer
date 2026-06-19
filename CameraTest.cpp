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

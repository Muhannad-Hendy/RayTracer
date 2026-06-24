#include "gmock/gmock.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "IntersectionTracker.h"
#include "Matrix.h"
#include "Canvas.h"
#include "Color.h"
#include "Light.h"
#include "Utilities.h"
#include "Plane.h"
#include "World.h"

using namespace testing;

class RaySphereIntersectionFeature : public Test {

};

TEST_F(RaySphereIntersectionFeature, DISABLED_SphereIDStartsAtZero){
    Sphere sphere1{};
    ASSERT_THAT(sphere1.getShapeID(), Eq(0));
}

TEST_F(RaySphereIntersectionFeature, DISABLED_SpheresHaveIdenticalIDs){
    Sphere sphere2{};
    Sphere sphere3{};

    ASSERT_THAT(sphere2.getShapeID(), Eq(1));
    ASSERT_THAT(sphere3.getShapeID(), Eq(2));
}

TEST_F(RaySphereIntersectionFeature, CreatingAndQueryingRay){
    Tuple origin{1,2,3,TupleType::point};
    Tuple direction{4,5,6,TupleType::vector};

    Ray ray{origin, direction};
    Tuple trueOrigin = ray.getOrigin();
    Tuple trueDirection = ray.getDirection();

    ASSERT_THAT(trueOrigin == origin, true);
    ASSERT_THAT(trueDirection== direction, true);
}

TEST_F(RaySphereIntersectionFeature, ComputingPointFromDistance){
    Tuple origin{2,3,4,TupleType::point};
    Tuple direction{1,0,0,TupleType::vector};
    Ray ray{origin,direction};
    Tuple position1 = ray.locate(0);
    Tuple truePosition1{2,3,4,TupleType::point};
    Tuple position2 = ray.locate(1);
    Tuple truePosition2{3,3,4,TupleType::point};
    Tuple position3 = ray.locate(-1);
    Tuple truePosition3{1,3,4,TupleType::point};
    Tuple position4 = ray.locate(2.5);
    Tuple truePosition4{4.5,3,4,TupleType::point};

    ASSERT_THAT(position1 == truePosition1, true);
    ASSERT_THAT(position2 == truePosition2, true);
    ASSERT_THAT(position3 == truePosition3, true);
    ASSERT_THAT(position4 == truePosition4, true);
}

TEST_F(RaySphereIntersectionFeature, RayIntersectsSphereAtTwoPoints){
    Tuple origin{0,0,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray, tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(tracker.getIntersectionTime(0), Eq(4));
    ASSERT_THAT(tracker.getIntersectionTime(1), Eq(6));
}

TEST_F(RaySphereIntersectionFeature, RayIntersectsSphereAtTangent){
    Tuple origin{0,1,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray, tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(tracker.getIntersectionTime(0), Eq(5));
    ASSERT_THAT(tracker.getIntersectionTime(1), Eq(5));
}

TEST_F(RaySphereIntersectionFeature, RayMissesSphere){
    Tuple origin{0,2,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray, tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(0));
}

TEST_F(RaySphereIntersectionFeature, RayOriginatesInsideSphere){
    Tuple origin{0,0,0,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(tracker.getIntersectionTime(0), Eq(-1));
    ASSERT_THAT(tracker.getIntersectionTime(1), Eq(1));
}

TEST_F(RaySphereIntersectionFeature, SphereIsBehindRay){
    Tuple origin{0,0,5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(tracker.getIntersectionTime(0), Eq(-6));
    ASSERT_THAT(tracker.getIntersectionTime(1), Eq(-4));
}

TEST_F(RaySphereIntersectionFeature, IntersectionEncapsulatesTimeAndObject){
    Sphere sphere{};
    Intersection intersection{3.5, sphere};

    ASSERT_THAT(intersection.getIntersectionTime(), Eq(3.5));
    ASSERT_THAT(intersection.getIntersectedShape()->getShapeID(), Eq(sphere.getShapeID()));
}

TEST_F(RaySphereIntersectionFeature, IntersectionsObjectAggregatesIntersections){
    Sphere sphere{};
    Intersection intersection1{1, sphere};
    Intersection intersection2{2, sphere};
    std::vector<Intersection> intersectionsVector{intersection1, intersection2};
    IntersectionTracker intersections{intersectionsVector};
    ASSERT_THAT(intersections.count(), Eq(2));
    ASSERT_THAT(intersections.getIntersection(0).getIntersectionTime(), Eq(1));
    ASSERT_THAT(intersections.getIntersection(1).getIntersectionTime(), Eq(2));
}

TEST_F(RaySphereIntersectionFeature, IntersectSetsIntersectedObjectOnTheIntersection){
    Tuple origin{0,0,-5,TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(tracker.getIntersectedObject(0) == sphere, true);
    ASSERT_THAT(tracker.getIntersectedObject(1) == sphere, true);
}

TEST_F(RaySphereIntersectionFeature, HitWhenAllIntersectionsHavePositiveTime){
    Sphere sphere{};
    IntersectionTracker intersections;
    intersections.addIntersection(2, sphere);
    Intersection intersection1{1, sphere};
    intersections.addIntersection(intersection1);
    Intersection* hit = intersections.hit();
    ASSERT_THAT(*hit == intersection1, true);
}

TEST_F(RaySphereIntersectionFeature, HitWhenSomeIntersectionsHaveNegativeTime){
    Sphere sphere{};
    Intersection intersection1{-1,sphere};
    Intersection intersection2{1,sphere};
    IntersectionTracker intersections{std::vector<Intersection> {intersection1,intersection2}};
    ASSERT_THAT(*intersections.hit() == intersection2, true);
}

TEST_F(RaySphereIntersectionFeature, HitWhenAllIntersectionsHaveNegativeTime){
    Sphere sphere{};
    Intersection intersection1{-1,sphere};
    Intersection intersection2{-2,sphere};
    IntersectionTracker intersections{std::vector<Intersection> {intersection1,intersection2}};
    ASSERT_THAT(intersections.hit() == nullptr, true);
}

TEST_F(RaySphereIntersectionFeature, HitIsAlwaysLowestNonnegativeIntersectionTime){
    Sphere sphere{};
    Intersection intersection1{5,sphere};
    Intersection intersection2{7,sphere};
    Intersection intersection3{-3,sphere};
    Intersection intersection4{2,sphere};
    IntersectionTracker intersections{std::vector<Intersection> {intersection1,intersection2,intersection3,intersection4}};
    ASSERT_THAT(*intersections.hit() == intersection4, true);
}

TEST_F(RaySphereIntersectionFeature, SphereHasDefaultTransformation){
    Sphere sphere{};
    Matrix identityMatrix{4, MatrixType::identity};
    Matrix sphereDefaultTransformation = sphere.getTransformation().getTransformationMatrix();

    ASSERT_THAT(sphereDefaultTransformation == identityMatrix, true);
}

TEST_F(RaySphereIntersectionFeature, ChangeSphereTransformation){
    Sphere sphere{};
    Transformer translation{Transformation::translation, 2,3,4};
    sphere.setTransformation(translation);

    Matrix translationMatrix = translation.getTransformationMatrix();
    Matrix sphereTransformation = sphere.getTransformation().getTransformationMatrix();

    ASSERT_THAT(translationMatrix == sphereTransformation, true);
}

TEST_F(RaySphereIntersectionFeature, IntersectingScaledSphereWithRay){
    Tuple origin{0,0,-5, TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    Transformer scaling{Transformation::scaling, 2,2,2};
    sphere.setTransformation(scaling);
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(2));
    ASSERT_THAT(tracker.getIntersectionTime(0), Eq(3));
    ASSERT_THAT(tracker.getIntersectionTime(1), Eq(7));
}

TEST_F(RaySphereIntersectionFeature, IntersectingTranslatedSphereWithRay){
    Tuple origin{0,0,-5, TupleType::point};
    Tuple direction{0,0,1,TupleType::vector};
    Ray ray{origin,direction};
    Sphere sphere{};
    Transformer translate(Transformation::translation,5,0,0);
    sphere.setTransformation(translate);
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    ASSERT_THAT(tracker.getNumberOfIntersections(), Eq(0));
}

TEST_F(RaySphereIntersectionFeature, DISABLED_ProjectingSphereOntoCanvas){

    Tuple rayOrigin{0,0,-5,TupleType::point};
    double wallSize{7};
    int canvasPixels{1000};
    double pixelSize = wallSize / canvasPixels;
    double halfCanvasLength = wallSize / 2;
    Canvas canvas{canvasPixels, canvasPixels};
    Color red{1,0,0};
    Sphere sphere{};
    double worldX{};
    double worldY{};
    double worldZ{10};

    for (int i=0; i<canvasPixels; i++){
        worldX = i * pixelSize - halfCanvasLength;
        for (int j=0; j<canvasPixels; j++){
            worldY = halfCanvasLength - j * pixelSize;
            Tuple targetPoint{worldX, worldY, worldZ, TupleType::point};
            Tuple directionVector = targetPoint - rayOrigin;
            directionVector = directionVector.normalize();
            Ray ray{rayOrigin, directionVector};
            IntersectionTracker tracker{};
            sphere.intersect(ray,tracker);
            if (tracker.hit()){
                canvas.setPixelColor(i, j, red);
            }
        }
    }
    canvas.saveToPPM("../Output/sphereProjection.ppm");
}

TEST_F(RaySphereIntersectionFeature, DISABLED_Projecting3DSphereOntoCanvas){

    Tuple rayOrigin{0,0,-5,TupleType::point};
    double wallSize{7};
    int canvasPixels{1000};
    double pixelSize = wallSize / canvasPixels;
    double halfCanvasLength = wallSize / 2;
    Canvas canvas{canvasPixels, canvasPixels};
    Sphere sphere{};
    Material sphereMaterial{};
    Color materialColor{0.25,0.88,0.82};
    sphereMaterial.setColor(materialColor);
    sphere.setMaterial(sphereMaterial);
    Tuple lightPosition{-10,10,-10, TupleType::point};
    Color lightColor{1,1,1};
    Light light{lightPosition,lightColor};
    double worldX{};
    double worldY{};
    double worldZ{10};

    for (int i=0; i<canvasPixels; i++){
        worldX = i * pixelSize - halfCanvasLength;
        for (int j=0; j<canvasPixels; j++){
            worldY = halfCanvasLength - j * pixelSize;
            Tuple targetPoint{worldX, worldY, worldZ, TupleType::point};
            Tuple directionVector = targetPoint - rayOrigin;
            directionVector = directionVector.normalize();
            Ray ray{rayOrigin, directionVector};
            IntersectionTracker tracker{};
            sphere.intersect(ray,tracker);
            if (tracker.hit()){
                double intersectionTime = tracker.hit()->getIntersectionTime();
                Tuple hitLocation = ray.locate(intersectionTime);
                Tuple normalAtHit = sphere.normalAt(hitLocation);
                Tuple eyeVector = -ray.getDirection();
                Color lightingColor  = light.light(sphereMaterial,hitLocation,eyeVector,normalAtHit);
                canvas.setPixelColor(i, j, lightingColor);
            }
        }
    }
    canvas.saveToPPM("../Output/sphere3DProjection.ppm");
}

TEST_F(RaySphereIntersectionFeature, PrecomputeStateOfIntersection){
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin, rayDirection};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection intersection = tracker.getIntersection(0);
    Shape* intersectedObject = intersection.getIntersectedShape();
    ASSERT_THAT(intersectedObject->getShapeID(), Eq(sphere.getShapeID()));
    Tuple correctIntersectionPoint{0,0,-1,TupleType::point};
    Tuple* intersectionPoint = intersection.getIntersectionPoint();
    ASSERT_THAT(*intersectionPoint == correctIntersectionPoint, true);
    Tuple correctEyeVector{0,0,-1,TupleType::vector};
    Tuple& eyeVector = intersection.getEyeVector();
    ASSERT_THAT(eyeVector == correctEyeVector, true);
    Tuple correctNormal{0,0,-1,TupleType::vector};
    Tuple& normalVector = intersection.getNormalVector();
    ASSERT_THAT(normalVector == correctNormal, true);

}

TEST_F(RaySphereIntersectionFeature, HitIntersectionOnOutside){
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin, rayDirection};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection* intersection = tracker.hit();
    ASSERT_THAT(intersection->isInside(), Eq(false));
}

TEST_F(RaySphereIntersectionFeature, HitIntersectionOnInside){
    Tuple rayOrigin{0,0,0,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin, rayDirection};
    Sphere sphere{};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection* intersection = tracker.hit();
    Tuple correctIntersectionPoint{0,0,1,TupleType::point};
    Tuple* intersectionPoint = intersection->getIntersectionPoint();
    ASSERT_THAT(*intersectionPoint == correctIntersectionPoint, true);
    Tuple correctEyeVector{0,0,-1,TupleType::vector};
    Tuple& eyeVector = intersection->getEyeVector();
    ASSERT_THAT(eyeVector == correctEyeVector, true);
    ASSERT_THAT(intersection->isInside(), Eq(true));
    Tuple correctNormal{0,0,-1,TupleType::vector};
    Tuple& normalVector = intersection->getNormalVector();
    ASSERT_THAT(normalVector == correctNormal, true);
}

TEST_F(RaySphereIntersectionFeature, HitShouldOffsetPoint) {
    Tuple rayOrigin{0,0,-5,TupleType::point};
    Tuple rayDirection{0,0,1,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    Sphere sphere{};
    Transformer translation{Transformation::translation, 0,0,1};
    sphere.setTransformation(translation);
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    Intersection* intersection = tracker.hit();
    Tuple& pointOverIntersection = intersection->getOverIntersectionPoint();
    double overIntersectionZValue = pointOverIntersection.getZValue();
    ASSERT_LT(overIntersectionZValue, util::EPSILON/-2);
    Tuple* intersectionPoint = intersection->getIntersectionPoint();
    double intersectionZValue = intersectionPoint->getZValue();
    ASSERT_GT(intersectionZValue,overIntersectionZValue);
}

TEST_F(RaySphereIntersectionFeature, PrecomputingReflectionVector) {
    Plane plane{};
    Tuple rayOrigin{0,1,-1,TupleType::point};
    Tuple rayDirection{0,-std::sqrt(2)/2,std::sqrt(2)/2,TupleType::vector};
    Ray ray{rayOrigin,rayDirection};
    Intersection intersection{std::sqrt(2),plane};
    IntersectionTracker tracker{};
    tracker.addIntersection(intersection);
    tracker.prepComputations(ray);
    Tuple correctReflection{0,std::sqrt(2)/2,std::sqrt(2)/2,TupleType::vector};
    ASSERT_THAT(tracker.hit()->getReflectionVector()==correctReflection,true);
}

TEST_F(RaySphereIntersectionFeature, SphereWithGlassyMaterial) {
    Sphere sphere{SphereType::glass};
    ASSERT_DOUBLE_EQ(sphere.getMaterial().getTransparency(),1);
    ASSERT_DOUBLE_EQ(sphere.getMaterial().getRefractiveIndex(),1.5);
}

TEST_F(RaySphereIntersectionFeature, FindingN1AndN2AtVariousIntersections) {
    Sphere sphereA{SphereType::glass};
    Transformer sphereAScaler{Transformation::scaling,2,2,2};
    sphereA.setTransformation(sphereAScaler);

    Sphere sphereB{SphereType::glass};
    Transformer sphereBTranslator{Transformation::translation,0,0,-0.25};
    sphereB.setTransformation(sphereBTranslator);
    Material& materialB = sphereB.getMaterial();
    materialB.setRefractiveIndex(2);

    Sphere sphereC{SphereType::glass};
    Transformer sphereCTranslator{Transformation::translation,0,0,0.25};
    sphereC.setTransformation(sphereCTranslator);
    Material& materialC = sphereC.getMaterial();
    materialC.setRefractiveIndex(2.5);

    Ray ray{Tuple{0,0,-4,TupleType::point},Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    tracker.addIntersection(Intersection{2,sphereA});
    tracker.addIntersection(Intersection{2.75,sphereB});
    tracker.addIntersection(Intersection{3.25,sphereC});
    tracker.addIntersection(Intersection{4.75,sphereB});
    tracker.addIntersection(Intersection{5.25,sphereC});
    tracker.addIntersection(Intersection{6,sphereA});
    tracker.prepComputations(ray);
    double n1 = tracker.getIntersection(3).getN1();
    double n2 = tracker.getIntersection(3).getN2();
//    ASSERT_DOUBLE_EQ(n1,1);
//    ASSERT_DOUBLE_EQ(n2,1.5);
//    ASSERT_DOUBLE_EQ(n1,1.5);
//    ASSERT_DOUBLE_EQ(n2,2);
//    ASSERT_DOUBLE_EQ(n1,2);
//    ASSERT_DOUBLE_EQ(n2,2.5);
    ASSERT_DOUBLE_EQ(n1,2.5);
    ASSERT_DOUBLE_EQ(n2,2.5);
//    ASSERT_DOUBLE_EQ(n1,2.5);
//    ASSERT_DOUBLE_EQ(n2,1.5);
//    ASSERT_DOUBLE_EQ(n1,1.5);
//    ASSERT_DOUBLE_EQ(n2,1);
}

TEST_F(RaySphereIntersectionFeature, PointIsOffsetBelowSurface) {
    Ray ray{Tuple{0,0,-5,TupleType::point}, Tuple{0,0,1,TupleType::vector}};
    Sphere sphere{};
    Transformer translator{Transformation::translation,0,0,1};
    sphere.setTransformation(translator);
    IntersectionTracker tracker{};
    tracker.addIntersection(Intersection{5,sphere});
    tracker.prepComputations(ray);
    Tuple* intersectionPoint = tracker.getIntersection(0).getIntersectionPoint();
    Tuple& underIntersection = tracker.getIntersection(0).getUnderIntersectionPOint();
    ASSERT_GT(underIntersection.getZValue(), util::EPSILON/2);
    ASSERT_LT(intersectionPoint->getZValue(), util::EPSILON/2);
}

TEST_F(RaySphereIntersectionFeature, SchlickApproximationUnderTotalInternalReflection) {
    Sphere sphere{SphereType::glass};
    Light light{Tuple{0,0,0,TupleType::point}, Color{1,1,1}};
    World world{std::make_unique<Sphere>(sphere),light};
    Ray ray{Tuple{0,0,std::sqrt(2)/2,TupleType::point},Tuple{0,1,0,TupleType::vector}};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    auto& intersection = tracker.getIntersection(1);
    double reflectance = world.calculateSchlickReflectance(intersection);
    double correctReflectance{1};
    ASSERT_DOUBLE_EQ(reflectance,correctReflectance);
}

TEST_F(RaySphereIntersectionFeature, SchlickApproximationWithPrependicularViewingAngle) {
    Sphere sphere{SphereType::glass};
    Light light{Tuple{0,0,0,TupleType::point}, Color{1,1,1}};
    World world{std::make_unique<Sphere>(sphere),light};
    Ray ray{Tuple{0,0,0,TupleType::point},Tuple{0,1,0,TupleType::vector}};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    auto& intersection = tracker.getIntersection(1);
    double reflectance = world.calculateSchlickReflectance(intersection);
    double correctReflectance{0.04};
    ASSERT_DOUBLE_EQ(reflectance,correctReflectance);
}

TEST_F(RaySphereIntersectionFeature, SchlickApproximationWithSmallAngleAndN2GreaterThanN1) {
    Sphere sphere{SphereType::glass};
    Light light{Tuple{0,0,0,TupleType::point}, Color{1,1,1}};
    World world{std::make_unique<Sphere>(sphere),light};
    Ray ray{Tuple{0,0.99,-2,TupleType::point},Tuple{0,0,1,TupleType::vector}};
    IntersectionTracker tracker{};
    sphere.intersect(ray,tracker);
    tracker.prepComputations(ray);
    auto& intersection = tracker.getIntersection(0);
    double reflectance = world.calculateSchlickReflectance(intersection);
    double correctReflectance{0.48881};
    ASSERT_THAT(util::equals(reflectance,correctReflectance), true);
}

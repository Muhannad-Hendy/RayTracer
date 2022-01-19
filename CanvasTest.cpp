#include "gmock/gmock.h"
#include <string>
#include "Canvas.h"
#include "Color.h"

using namespace testing;

class CanvasFeature : public Test
{

};

TEST_F(CanvasFeature, CreatingCanvas){
    Canvas canvas{10, 20};
    ASSERT_THAT(canvas.getWidth(), Eq(10));
    ASSERT_THAT(canvas.getHeight(), Eq(20));
}

TEST_F(CanvasFeature, CanvasInitializedToBlackColor){
    Canvas canvas{10, 20};
    auto width = canvas.getWidth();
    auto height = canvas.getHeight();
    Color black{0, 0, 0};
    Color* canvasColor{};
    for (int i = 0; i<width; i++){
        for (int j = 0; j<height; j++){
            canvasColor = canvas.getPixelColor(i, j);
            ASSERT_THAT(*canvasColor == black, true);
        }
    }
}

TEST_F(CanvasFeature, WritingPixelsToCanvas){
    Canvas canvas{10, 20};
    Color red{1, 0, 0};
    Color black{0, 0, 0};
    canvas.setPixelColor(2, 3, red);
    Color* pixelColor = canvas.getPixelColor(2, 3);
    ASSERT_THAT(red == *pixelColor, true);
    pixelColor = canvas.getPixelColor(2, 4);
    ASSERT_THAT(black == *pixelColor, true);
}

//TEST_F(CanvasFeature, WritingPPMHFileHeader){
//    Canvas canvas{5, 3};
//    std::string fileOutput = canvas.saveToPPM();
//    std::string correctValue = "P3\n5 3\n255\n";
//    ASSERT_THAT(fileOutput, Eq(correctValue));
//}

//TEST_F(CanvasFeature, ConstructingPPMPixelData){
//    Canvas canvas{5, 3};
//    Color c1{1.5, 0, 0};
//    Color c2{0, 0.5, 0};
//    Color c3{-0.5, 0, 1};
//    canvas.setPixelColor(0, 0, c1);
//    canvas.setPixelColor(2, 1, c2);
//    canvas.setPixelColor(4, 2, c3);
//    std::string fileOutput = canvas.saveToPPM();
//    canvas.saveToPPM("../Output/canvas.ppm");
//    std::string correctVale = "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
//    ASSERT_THAT(fileOutput, Eq(correctVale));
//}

//TEST_F(CanvasFeature, EnsuringNoPPMLineExceedsSeventyCharactersLong){
//    Canvas canvas{10, 2};
//    Color color{1, 0.8, 0.6};
//    for (int i = 0; i < 2; i++){
//        for (int j = 0; j < 10; j++){
//            canvas.setPixelColor(j, i, color);
//        }
//    }

//    canvas.saveToPPM("../Output/canvas.ppm");
//    std::string fileOutput = canvas.readFromPPM("../Output/canvas.ppm");
//    std::string correctValue = "P3\n5 3\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
//                               "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
//                               "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
//                               "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
//    ASSERT_THAT(fileOutput, Eq(correctValue));
//}

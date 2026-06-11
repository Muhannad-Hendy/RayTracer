#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include "Utilities.h"
#include "Transformer.h"
#include "Canvas.h"
#include "World.h"

class Camera
{
public:
    Camera();

    Camera(int horizontalPixelSize, int verticalPixelSize, double fieldOfView);

    int getHorizontalSize() const;

    int getVerticalSize() const;

    double getFieldOfView() const;

    void setCameraTransformation(const Transformer& transformation);

    Transformer& getTransformation();

    double getPixelSize() const;

    void setPixelSize();

    Ray generateRayForPixel(int pixelXCoordinate, int pixelYCoordinate);

    const Canvas& render(World& world);

private:
    int horizontalPixelSize{};
    int verticalPixelSize{};
    double fieldOfView{};
    Transformer cameraTransform{};
    double pixelSize{};
    double halfWidth{};
    double halfHeight{};
    Canvas canvas{horizontalPixelSize,verticalPixelSize};
};

#endif // CAMERA_H

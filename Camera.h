#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include "Utilities.h"
#include "Transformer.h"

class Camera
{
public:
    Camera();

    Camera(int horizontalPixelSize, int verticalPixelSize, double fieldOfView);

    int getHorizontalSize() const;

    int getVerticalSize() const;

    double getFieldOfView() const;

    Transformer& getTransformation();

    double getPixelSize() const;

    void setPixelSize();

private:
    int horizontalPixelSize{};
    int verticalPixelSize{};
    double fieldOfView{};
    Transformer cameraTransform{};
    double pixelSize{};
    double halfWidth{};
    double halfHeight{};
};

#endif // CAMERA_H

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

private:
    int horizontalPixelSize{};
    int verticalPixelSize{};
    double fieldOfView{};
    Transformer cameraTransform{};
};

#endif // CAMERA_H

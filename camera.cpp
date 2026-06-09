#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(int horizontal, int vertical, double field) : horizontalPixelSize{horizontal}, verticalPixelSize{vertical}, fieldOfView{field}{}


int Camera::getHorizontalSize() const {
    return horizontalPixelSize;
}

int Camera::getVerticalSize() const {
    return verticalPixelSize;
}

double Camera::getFieldOfView() const {
    return fieldOfView;
}

Transformer& Camera::getTransformation() {
    return cameraTransform;
}

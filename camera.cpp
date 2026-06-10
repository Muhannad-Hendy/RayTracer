#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(int horizontal, int vertical, double field) : horizontalPixelSize{horizontal}, verticalPixelSize{vertical}, fieldOfView{field} {
    setPixelSize();
}


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

double Camera::getPixelSize() const {
    return pixelSize;
}

void Camera::setPixelSize() {
    double halfView = std::tan(fieldOfView/2);
    double aspectRatio = static_cast<double>(horizontalPixelSize) / verticalPixelSize;
    if(aspectRatio>=1) {
        halfWidth = halfView;
        halfHeight = halfView / aspectRatio;
    }
    else {
        halfWidth = halfView * aspectRatio;
        halfHeight = halfView;
    }
    pixelSize = halfWidth * 2 / horizontalPixelSize;
}

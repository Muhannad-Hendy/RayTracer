#include "Camera.h"
#include "Tuple.h"
#include "Ray.h"

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

void Camera::setCameraTransformation(const Transformer &transformation) {
    cameraTransform = transformation;
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

Ray Camera::generateRayForPixel(int pixelXCoordinate, int pixelYCoordinate) {
    double xOffset = (pixelXCoordinate + 0.5) * pixelSize;
    double yOffset = (pixelYCoordinate + 0.5) * pixelSize;
    double worldX = halfWidth - xOffset;
    double worldY = halfHeight - yOffset;
    Tuple pixel{worldX,worldY,-1,TupleType::point};
    Tuple origin{0,0,0,TupleType::point};
    Tuple untransformedPixel = cameraTransform.invert().transform(pixel);
    Tuple untransformedOrigin = cameraTransform.invert().transform(origin);
    Tuple direction = (untransformedPixel-untransformedOrigin).normalize();
    Ray ray{untransformedOrigin, direction};
    return ray;
}

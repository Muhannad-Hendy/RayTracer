#include "Pattern.h"
#include "Shape.h"

Pattern::Pattern(const Color& color1, const Color& color2) : colors{color1,color2} {}

const Color Pattern::patternAtShape(const Shape &shape, const Tuple &worldPoint) const {
    Tuple objectPoint = shape.getTransformation().invert().transform(worldPoint);
    Tuple patternPoint = transformation.invert().transform(objectPoint);
    const Color& patternColor = patternAt(patternPoint);
    return patternColor;
}

Pattern::Pattern() {
    colors.emplace_back(1,1,1);
    colors.emplace_back(0,0,0);
}

const Color& Pattern::getColor(const int index) const {
    return colors.at(index);
}

void Pattern::setTransformation(const Transformer &transform) {
    transformation = transform;
}

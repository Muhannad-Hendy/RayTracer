#ifndef PATTERN_H
#define PATTERN_H

#include <vector>
#include "Color.h"
#include "Transformer.h"
#include "Shape.h"

class Pattern
{
public:
    Pattern(const Color& color1, const Color& color2);

    const Color& patternAtShape(const Shape& shape, const Tuple& worldPoint) const;

protected:
    virtual const Color& patternAt(const Tuple& patternPoint) const = 0;

private:
    std::vector<Color> colors{};
    Transformer transformation{};
};

#endif // PATTERN_H

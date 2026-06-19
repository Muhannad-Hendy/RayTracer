#ifndef GRADIENT_H
#define GRADIENT_H

#include "Pattern.h"

class Gradient : public Pattern
{
public:
    Gradient();

protected:
    const Color patternAt(const Tuple &patternPoint) const override;
};

#endif // GRADIENT_H

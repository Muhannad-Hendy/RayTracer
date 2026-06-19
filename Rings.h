#ifndef RINGS_H
#define RINGS_H

#include "Pattern.h"

class Rings : public Pattern
{
public:
    using Pattern::Pattern;

protected:
    const Color patternAt(const Tuple &patternPoint) const override;
};

#endif // RINGS_H
